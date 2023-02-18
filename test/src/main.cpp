//
// Created by madahin on 03/01/23.
//

#include "gtest/gtest.h"

#include "Logger.h"

auto main(int argc, char **argv) -> int
{
    Log::SetLevel(spdlog::level::off);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
