#pragma once
#include <string>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>

#include "../event/event.hpp"
#include "../packet/payload.hpp"
#include "../packet/packet_helper.hpp"
#include "../utils/text_parse.hpp"
#include "../utils/byte_stream.hpp"
#include "../world/item_database.hpp"
#include "spoofer.hpp"

namespace player {
class DialogHandler {
public:
    DialogHandler(event::Dispatcher& dispatcher, network::Client& client)
        : dispatcher_{ dispatcher }
        , client_{ client }
    {
        listener_handle_ = dispatcher_.prependListener(
            event::Type::ServerBoundPacket,
            [this](const event::Event& e) { on_packet(e); }
        );
    }

    ~DialogHandler()
    {
        dispatcher_.removeListener(event::Type::ServerBoundPacket, listener_handle_);
    }

private:
    void on_packet(const event::Event& e)
    {
        const auto* raw = dynamic_cast<const event::RawPacketEvent*>(&e);
        if (raw) {
            ByteStream stream{ raw->data };
            packet::NetMessageType msg_type{};
            if (!stream.read(msg_type)) return;

            if (msg_type == packet::NET_MESSAGE_GENERIC_TEXT) {
                std::string message{};
                stream.read(message, static_cast<uint16_t>(stream.get_size() - sizeof(packet::NetMessageType) - 1));

                TextParse parser{ message };
                if (parser.get("action") == "dialog_return") {
                    std::string dialog_name = parser.get("dialog_name");
                    if (dialog_name == "find_item_dialog") {
                        e.cancel();
                        std::string query = parser.get("item_query");
                        handle_find_search(query);
                    }
                    else if (dialog_name == "find_item_results") {
                        e.cancel();
                        std::string button = parser.get("buttonClicked");
                        if (button.starts_with("item_")) {
                            uint32_t item_id = std::stoul(button.substr(5));
                            handle_item_select(item_id);
                        }
                    }
                }
            }
        }
    }

    void handle_find_search(const std::string& query)
    {
        auto results = world::ItemDatabase::instance().search(query, 10);
        
        packet::PacketVariant dialog_req{};
        dialog_req.add("OnDialogRequest");
        
        std::string dialog = "set_default_color|`o\nadd_label_with_icon|big|`wSearch Results``|left|6016|\n";
        
        if (results.empty()) {
            dialog += "add_textbox|No items found matching your query.|\n";
        } else {
            for (const auto& [name, id] : results) {
                dialog += fmt::format("add_button|item_{}|{}|\n", id, name);
            }
        }
        dialog += "end_dialog|find_item_results|Close||\n";
        
        dialog_req.add(dialog);
        
        packet::VariantPayload payload{ dialog_req };
        auto raw_data = packet::PacketHelper::serialize(payload);
        raw_data.push_back(static_cast<std::byte>(0x00));
        
        (void)client_.write(raw_data, 0);
    }

    void handle_item_select(uint32_t item_id)
    {
        Spoofer::instance().set_spoofed_item(item_id);
        
        // Log to console that it was spoofed
        packet::PacketVariant console_msg{};
        console_msg.add("OnConsoleMessage");
        console_msg.add(fmt::format("`2[GTProxy] ``Successfully equipped item {} visually! Move to see changes.", item_id));
        
        packet::VariantPayload payload{ console_msg };
        auto raw_data = packet::PacketHelper::serialize(payload);
        raw_data.push_back(static_cast<std::byte>(0x00));
        
        (void)client_.write(raw_data, 0);

        // Visual spoof logic: Send OnSetClothing to the client
        packet::PacketVariant spoof_pkt{};
        spoof_pkt.add("OnSetClothing");
        spoof_pkt.add(glm::vec3(item_id, item_id, item_id));
        spoof_pkt.add(glm::vec3(item_id, item_id, item_id));
        spoof_pkt.add(glm::vec3(item_id, item_id, item_id));

        packet::VariantPayload spoof_payload{ spoof_pkt };
        auto spoof_data = packet::PacketHelper::serialize(spoof_payload);
        spoof_data.push_back(static_cast<std::byte>(0x00));

        (void)client_.write(spoof_data, 0);
    }

    event::Dispatcher& dispatcher_;
    network::Client& client_;
    event::Dispatcher::Handle listener_handle_;
};
}
