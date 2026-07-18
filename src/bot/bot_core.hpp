#pragma once
#include <string>
#include <memory>
#include "../network/client.hpp"
#include "../event/event.hpp"

namespace bot {
class WebController;

class BotCore {
public:
    BotCore();
    ~BotCore();

    void run();
    void stop();

    void connect_to_server(const std::string& ip, uint16_t port);
    void send_login();
    void send_sub_login(const std::string& user, const std::string& token, const std::string& uuidToken, int doorID);

    // Bot actions
    void move(float x, float y, bool left);
    void join_world(const std::string& world_name);
    void send_text(const std::string& text);

private:
    void setup_event_listeners();
    void load_login_payload();
    void parse_server_bounce(const std::string& message);

    bool running_{false};
    std::string login_payload_{};
    
    event::Dispatcher dispatcher_;
    std::unique_ptr<network::Client> client_;
    std::unique_ptr<WebController> web_controller_;
    
    // Position tracking
    float pos_x_{0.0f};
    float pos_y_{0.0f};
    uint32_t net_id_{0};
};
}
