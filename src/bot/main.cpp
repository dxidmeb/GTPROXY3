#include <csignal>
#include <spdlog/spdlog.h>

#include "bot_core.hpp"
#include "../core/logger.hpp"

std::unique_ptr<bot::BotCore> g_bot{ nullptr };

void signal_handler(int signal)
{
    if (!g_bot) {
        return;
    }

    spdlog::info("Interrupted by signal {}, stopping...", signal);
    g_bot->stop();
}

int main()
{
    try {
        core::Logger logger{};

        std::vector<spdlog::sink_ptr> sinks{
            core::Logger::create_console_sink(),
            core::Logger::create_file_sink()
        };

        logger.set_logger(std::make_shared<spdlog::logger>("GTBot", sinks.begin(), sinks.end()));
        logger.get_logger()->set_level(spdlog::level::trace);

        spdlog::register_logger(logger.get_logger());
        spdlog::set_default_logger(logger.get_logger());
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%^%l%$] %v");
    }
    catch (const spdlog::spdlog_ex& ex) {
        spdlog::error("Log initialization failed: {}", ex.what());
        return 1;
    }

    try {
        spdlog::info("Starting GTBot...");

        g_bot = std::make_unique<bot::BotCore>();

        std::signal(SIGINT, signal_handler);
        std::signal(SIGTERM, signal_handler);

        g_bot->run();
    }
    catch (const std::runtime_error& e) {
        spdlog::error("Runtime error: {}", e.what());
        return 1;
    }
    catch (const std::exception& ex) {
        spdlog::error("Exception: {}", ex.what());
        return 1;
    }

    spdlog::info("GTBot stopped");
    spdlog::shutdown();
    return 0;
}
