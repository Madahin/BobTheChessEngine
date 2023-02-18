//
// Created by madahin on 17/02/23.
//
#include "Logger.h"

std::shared_ptr<spdlog::logger> Logger::s_Logger{nullptr};

auto Log::SetLevel(spdlog::level::level_enum level) -> void
{
    ::Logger::getInstance()->set_level(level);
}