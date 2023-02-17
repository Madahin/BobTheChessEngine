//
// Created by madahin on 17/02/23.
//

#include <array>

#include "gtest/gtest.h"
#include "Board.h"
#include "Move.h"

// https://www.chessprogramming.org/Perft_Results#Initial_Position
TEST(TestMove, Perft_Position_1)
{
    Board board;
    board.LoadFenString("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    std::array<uint64_t, 9> perftResult = {
            20,
            400,
            8902,
            197281,
            4865609,
            119060324,
            3195901860,
            84998978956,
            2439530234167
    };

    for (uint32_t depth = 0; depth < perftResult.size(); ++depth)
    {
        ASSERT_EQ(perftResult[depth], Move::GenerateMoveFromBoardForDepth(board, depth+1)->size());
    }
}

// https://www.chessprogramming.org/Perft_Results#Position_2
TEST(TestMove, Perft_Position_2)
{
    Board board;
    board.LoadFenString("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");

    std::array<uint64_t, 6> perftResult = {
            48,
            2039,
            97862,
            4085603,
            193690690,
            8031647685
    };

    for (uint32_t depth = 0; depth < perftResult.size(); ++depth)
    {
        ASSERT_EQ(perftResult[depth], Move::GenerateMoveFromBoardForDepth(board, depth+1)->size());
    }
}

// https://www.chessprogramming.org/Perft_Results#Position_3
TEST(TestMove, Perft_Position_3)
{
    Board board;
    board.LoadFenString("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");

    std::array<uint64_t, 8> perftResult = {
            14,
            191,
            2812,
            43238,
            674624,
            11030083,
            178633661,
            3009794393
    };

    for (uint32_t depth = 0; depth < perftResult.size(); ++depth)
    {
        ASSERT_EQ(perftResult[depth], Move::GenerateMoveFromBoardForDepth(board, depth+1)->size());
    }
}

// https://www.chessprogramming.org/Perft_Results#Position_4
TEST(TestMove, Perft_Position_4)
{
    Board board;
    board.LoadFenString("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");

    std::array<uint64_t, 6> perftResult = {
            6,
            264,
            9467,
            422333,
            15833292,
            706045033
    };

    for (uint32_t depth = 0; depth < perftResult.size(); ++depth)
    {
        ASSERT_EQ(perftResult[depth], Move::GenerateMoveFromBoardForDepth(board, depth+1)->size());
    }
}

// https://www.chessprogramming.org/Perft_Results#Position_4
TEST(TestMove, Perft_Position_4_mirrored)
{
    Board board;
    board.LoadFenString("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1");

    std::array<uint64_t, 6> perftResult = {
            6,
            264,
            9467,
            422333,
            15833292,
            706045033
    };

    for (uint32_t depth = 0; depth < perftResult.size(); ++depth)
    {
        ASSERT_EQ(perftResult[depth], Move::GenerateMoveFromBoardForDepth(board, depth+1)->size());
    }
}

// https://www.chessprogramming.org/Perft_Results#Position_5
TEST(TestMove, Perft_Position_5)
{
    Board board;
    board.LoadFenString("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");

    std::array<uint64_t, 5> perftResult = {
            44,
            1486,
            62379,
            2103487,
            89941194
    };

    for (uint32_t depth = 0; depth < perftResult.size(); ++depth)
    {
        ASSERT_EQ(perftResult[depth], Move::GenerateMoveFromBoardForDepth(board, depth+1)->size());
    }
}

// https://www.chessprogramming.org/Perft_Results#Position_6
TEST(TestMove, Perft_Position_6)
{
    Board board;
    board.LoadFenString("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");

    std::array<uint64_t, 9> perftResult = {
            46,
            2079,
            89890,
            3894594,
            164075551,
            6923051137,
            287188994746,
            11923589843526,
            490154852788714
    };

    for (uint32_t depth = 0; depth < perftResult.size(); ++depth)
    {
        ASSERT_EQ(perftResult[depth], Move::GenerateMoveFromBoardForDepth(board, depth+1)->size());
    }
}