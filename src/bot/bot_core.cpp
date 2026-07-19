#include "bot_core.hpp"
#include "web_controller.hpp"
#include "../packet/packet_helper.hpp"
#include "../utils/text_parse.hpp"
#include "../utils/byte_stream.hpp"
#include "../packet/packet_variant.hpp"

#include <spdlog/spdlog.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <httplib.h>

namespace bot {

struct RawState : packet::GamePacket<packet::PacketId::Unknown, packet::PACKET_STATE> {
    float vec_x;
    float vec_y;
    bool rotate_left;
    bool read(const packet::Payload&) override { return false; }
    packet::Payload write() override {
        packet::GameUpdatePacket pkt{};
        pkt.type = packet::PACKET_STATE;
        pkt.flags.rotate_left = rotate_left;
        // Basic cast to pad_4 for vec_x and vec_y (offsets 0 and 4 in pad_4 typically)
        *reinterpret_cast<float*>(&pkt.pad_4[0]) = vec_x;
        *reinterpret_cast<float*>(&pkt.pad_4[4]) = vec_y;
        return packet::GamePayload{ pkt, {} };
    }
};

struct RawGenericText : packet::TextPacket<packet::PacketId::Unknown, packet::NET_MESSAGE_GENERIC_TEXT> {
    std::string data;
    bool read(const packet::Payload&) override { return false; }
    packet::Payload write() override {
        return packet::TextPayload{ MESSAGE_TYPE, TextParse{data} };
    }
};

BotCore::BotCore() : client_(std::make_unique<network::Client>(config_, dispatcher_)), web_controller_(std::make_unique<WebController>(*this))
{
    setup_event_listeners();
    load_login_payload();
    web_controller_->start(8080);
}

BotCore::~BotCore() = default;

void BotCore::run()
{
    running_ = true;
    
    std::string server_address = config_.get_server_config().address;
    spdlog::info("Fetching server_data.php from {}", server_address);

    httplib::Client cli{ "http://" + server_address };
    cli.set_connection_timeout(5, 0); // 5 seconds
    httplib::Headers headers{
        { "User-Agent", "UbiServices_SDK_2022.Release.9_PC64_unicode_static" },
        { "Host", server_address }
    };
    httplib::Params params{
        { "version", config_.get_client_config().game_version },
        { "platform", "0" },
        { "protocol", std::to_string(config_.get_client_config().protocol) }
    };

    httplib::Result response{ cli.Post("/growtopia/server_data.php", headers, params) };
    
    if (!response || response->status != 200) {
        spdlog::warn("HTTP /growtopia/server_data.php failed on {}. Trying HTTPS...", server_address);
        httplib::Client https_cli{ "https://" + server_address };
        https_cli.enable_server_certificate_verification(false);
        https_cli.set_connection_timeout(5, 0);
        response = https_cli.Post("/growtopia/server_data.php", headers, params);
    }

    if (!response || response->status != 200) {
        spdlog::error("Failed to fetch server_data.php from {}. Please check your config.json address.", server_address);
        return;
    }

    TextParse text_parse{ response->body };
    std::string ip = text_parse.get("server", 0);
    std::string port_str = text_parse.get("port", 0);
    
    if (ip.empty() || port_str.empty()) {
        spdlog::error("Invalid server_data.php response. Missing server or port data.");
        return;
    }

    uint16_t port = static_cast<uint16_t>(std::stoul(port_str));
    spdlog::info("Fetched target login server: {}:{}", ip, port);

    connect_to_server(ip, port);

    while (running_) {
        client_->process();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void BotCore::stop()
{
    running_ = false;
}

void BotCore::load_login_payload()
{
    std::ifstream file("login.txt");
    if (!file.is_open()) {
        spdlog::warn("login.txt not found! The bot will not be able to log in.");
        return;
    }
    std::getline(file, login_payload_);
    spdlog::info("Loaded login payload ({} bytes)", login_payload_.size());
}

void BotCore::connect_to_server(const std::string& ip, uint16_t port)
{
    spdlog::info("Connecting to {}:{}...", ip, port);
    if (!client_->connect(ip, port)) {
        spdlog::error("Failed to connect to {}:{}", ip, port);
    }
}

void BotCore::send_login()
{
    if (login_payload_.empty()) return;

    RawGenericText pkt{};
    pkt.data = login_payload_;
    packet::PacketHelper::write(pkt, *client_);
    spdlog::info("Sent initial login payload");
}

void BotCore::send_sub_login(const std::string& user, const std::string& token, const std::string& uuidToken, int doorID)
{
    TextParse parse{login_payload_};
    parse.set("user", user);
    parse.set("token", token);
    parse.set("UUIDToken", uuidToken);
    parse.set("doorID", std::to_string(doorID));
    parse.set("lmode", "1"); // Sub-server transition

    RawGenericText pkt{};
    pkt.data = parse.get_raw();
    packet::PacketHelper::write(pkt, *client_);
    spdlog::info("Sent sub-server login payload");
}

void BotCore::setup_event_listeners()
{
    dispatcher_.appendListener(event::Type::ClientConnect, [this](const event::Event&) {
        spdlog::info("Connected! Awaiting Server Hello...");
    });

    dispatcher_.appendListener(event::Type::ClientBoundPacket, [this](const event::Event& event) {
        const auto* raw_packet = dynamic_cast<const event::RawPacketEvent*>(&event);
        if (!raw_packet) return;

        ByteStream stream{ raw_packet->data };
        packet::NetMessageType msg_type{};
        if (!stream.read(msg_type)) return;

        if (msg_type == packet::NET_MESSAGE_SERVER_HELLO) {
            spdlog::info("Received Server Hello. Sending enter_game...");
            RawGenericText enter{};
            enter.data = "action|enter_game\n";
            packet::PacketHelper::write(enter, *client_);
        }
        else if (msg_type == packet::NET_MESSAGE_GAME_PACKET) {
            packet::GameUpdatePacket game_pkt{};
            stream.read(game_pkt);

            if (game_pkt.type == packet::PACKET_CALL_FUNCTION) {
                std::vector<std::byte> extra{};
                stream.read_vector(extra, static_cast<uint16_t>(
                     game_pkt.data_size > 0 ? game_pkt.data_size : stream.get_size() - stream.get_read_offset()
                ));

                stream.backtrack(extra.size() + sizeof(packet::GameUpdatePacket));
                stream.skip(sizeof(packet::GameUpdatePacket));

                packet::PacketVariant variant{};
                if (!variant.deserialize(extra)) return;

                const auto& fn = variant.get<std::string>(0);
                if (fn == "OnSendToServer") {
                    int port = variant.get<int32_t>(1);
                    int token = variant.get<int32_t>(2);
                    int user = variant.get<int32_t>(3);
                    std::string raw_text = variant.get<std::string>(4);
                    
                    std::string key = raw_text.substr(0, raw_text.find_first_of('|'));
                    TextParse text_parse{};
                    text_parse.parse(raw_text);
                    
                    std::string ip = key;
                    int doorID = 0;
                    try { doorID = std::stoi(text_parse.get(key, 0)); } catch (...) {}
                    std::string uuid = text_parse.get(key, 1);

                    spdlog::info("Bouncing to {}:{} (User: {}, Token: {})", ip, port, user, token);
                    client_->disconnect();
                    connect_to_server(ip, port);
                    send_sub_login(std::to_string(user), std::to_string(token), uuid, doorID);
                }
                else if (fn == "OnConsoleMessage") {
                    spdlog::info("Chat: {}", variant.get<std::string>(1));
                }
            }
        }
    });
}

void BotCore::join_world(const std::string& world_name)
{
    RawGenericText pkt{};
    pkt.data = "action|join_request\nname|" + world_name + "\ninvitedWorld|0";
    packet::PacketHelper::write(pkt, *client_);
    spdlog::info("Joining world: {}", world_name);
}

void BotCore::move(float x, float y, bool left)
{
    RawState state{};
    state.vec_x = x;
    state.vec_y = y;
    state.rotate_left = left;
    packet::PacketHelper::write(state, *client_);
}

void BotCore::send_text(const std::string& text)
{
    RawGenericText pkt{};
    pkt.data = "action|input\n|text|" + text;
    packet::PacketHelper::write(pkt, *client_);
}

} // namespace bot
