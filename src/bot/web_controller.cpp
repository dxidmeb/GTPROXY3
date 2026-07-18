#include "web_controller.hpp"
#include <spdlog/spdlog.h>

namespace bot {

WebController::WebController(BotCore& bot) : bot_(bot)
{
    setup_routes();
}

WebController::~WebController()
{
    stop();
}

void WebController::start(int port)
{
    if (running_) return;
    running_ = true;
    server_thread_ = std::thread(&WebController::listen_internal, this, port);
    spdlog::info("WebController started on http://localhost:{}", port);
}

void WebController::stop()
{
    if (!running_) return;
    server_.stop();
    if (server_thread_.joinable()) {
        server_thread_.join();
    }
    running_ = false;
}

void WebController::listen_internal(int port)
{
    server_.listen("127.0.0.1", port);
}

void WebController::setup_routes()
{
    server_.Get("/", [](const httplib::Request&, httplib::Response& res) {
        std::string html = R"(
            <html>
            <head>
                <title>GTBot Controller</title>
                <style>
                    body { font-family: Arial; padding: 20px; background-color: #f4f4f9; }
                    .card { background: white; padding: 20px; border-radius: 8px; box-shadow: 0 4px 6px rgba(0,0,0,0.1); margin-bottom: 20px; }
                    button { padding: 10px 15px; background-color: #007bff; color: white; border: none; border-radius: 4px; cursor: pointer; }
                    button:hover { background-color: #0056b3; }
                    input[type=text], input[type=number] { padding: 8px; width: 200px; border: 1px solid #ccc; border-radius: 4px; margin-right: 10px; }
                </style>
            </head>
            <body>
                <h1>GTBot Web Controller</h1>
                
                <div class="card">
                    <h3>World Navigation</h3>
                    <form action="/join" method="POST">
                        <input type="text" name="world" value="START" placeholder="World Name">
                        <button type="submit">Join World</button>
                    </form>
                </div>

                <div class="card">
                    <h3>Movement</h3>
                    <form action="/move" method="POST">
                        X: <input type="number" name="x" value="0" style="width:80px;">
                        Y: <input type="number" name="y" value="0" style="width:80px;">
                        <label><input type="checkbox" name="left" value="1"> Face Left</label>
                        <button type="submit">Move Coordinates</button>
                    </form>
                </div>

                <div class="card">
                    <h3>Chat & Actions</h3>
                    <form action="/chat" method="POST">
                        <input type="text" name="text" value="Hello from GTBot!" placeholder="Chat Message">
                        <button type="submit">Send Message</button>
                    </form>
                </div>
            </body>
            </html>
        )";
        res.set_content(html, "text/html");
    });

    server_.Post("/join", [this](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("world")) {
            bot_.join_world(req.get_param_value("world"));
        }
        res.set_redirect("/");
    });

    server_.Post("/move", [this](const httplib::Request& req, httplib::Response& res) {
        float x = 0.0f;
        float y = 0.0f;
        if (req.has_param("x")) x = std::stof(req.get_param_value("x"));
        if (req.has_param("y")) y = std::stof(req.get_param_value("y"));
        bool left = req.has_param("left");
        bot_.move(x, y, left);
        res.set_redirect("/");
    });

    server_.Post("/chat", [this](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("text")) {
            bot_.send_text(req.get_param_value("text"));
        }
        res.set_redirect("/");
    });
}

} // namespace bot
