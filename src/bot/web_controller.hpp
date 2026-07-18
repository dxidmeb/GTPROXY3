#pragma once
#include <memory>
#include <thread>
#include <httplib.h>
#include "bot_core.hpp"

namespace bot {
class WebController {
public:
    WebController(BotCore& bot);
    ~WebController();

    void start(int port);
    void stop();

private:
    void setup_routes();
    void listen_internal(int port);

    BotCore& bot_;
    httplib::Server server_;
    std::thread server_thread_;
    bool running_{false};
};
}
