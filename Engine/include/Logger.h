//
// Created by madahin on 17/02/23.
//

#ifndef CHESSENGINE_LOGGER_H
#define CHESSENGINE_LOGGER_H

#include <iostream>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class Logger
{
private:
    Logger() = default;
    ~Logger() = default;
public:
    Logger(const Logger&) = delete;
    Logger& operator = (const Logger&) = delete;

    inline static std::shared_ptr<spdlog::logger>& getInstance(){
        static bool s_bFirstTime{true};
        if (s_bFirstTime)
        {
            std::vector<spdlog::sink_ptr> sinks;

            // stderr sink
            {
                auto stderrSink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
                stderrSink->set_level(spdlog::level::trace);
                sinks.push_back(stderrSink);
            }

            // File sink for log retention.
            // It's not a big deal if we fail to instantiate it.
            try
            {
                auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("ChessEngine.log");
                fileSink->set_level(spdlog::level::debug);
                sinks.push_back(fileSink);
            }
            catch (const spdlog::spdlog_ex &ex)
            {
                std::cerr << "Log init failed: " << ex.what() << std::endl;
            }
            s_Logger = std::make_shared<spdlog::logger>("ChessEngine", begin(sinks), end(sinks));
            s_Logger->set_level(spdlog::level::trace);
            s_bFirstTime = false;
        }
        return s_Logger;
    }

private:
    static std::shared_ptr<spdlog::logger> s_Logger;
};

namespace Log
{
    template <typename... Args>
    auto Trace(spdlog::format_string_t<Args...> format, Args &&... args) -> void
    {
        ::Logger::getInstance()->trace(format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto Debug(spdlog::format_string_t<Args...> format, Args &&... args) -> void
    {
        ::Logger::getInstance()->debug(format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto Info(spdlog::format_string_t<Args...> format, Args &&... args) -> void
    {
        ::Logger::getInstance()->info(format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto Warn(spdlog::format_string_t<Args...> format, Args &&... args) -> void
    {
        ::Logger::getInstance()->warn(format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto Error(spdlog::format_string_t<Args...> format, Args &&... args) -> void
    {
        ::Logger::getInstance()->error(format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto Critical(spdlog::format_string_t<Args...> format, Args &&... args) -> void
    {
        ::Logger::getInstance()->critical(format, std::forward<Args>(args)...);
    }
};

#endif //CHESSENGINE_LOGGER_H
