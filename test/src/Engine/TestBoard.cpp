//
// Created by madahin on 03/01/23.
//

#include <vector>

#include "gtest/gtest.h"
#include "Board.h"

TEST(TestBoard, ValidateFenString_valid)
{


    static const std::vector<std::string> vecFenStrings = {
            // From https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation#Examples
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
            "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1",
            "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2",
            "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2",
            // From https://www.chess.com/terms/fen-chess
            "8/5k2/3p4/1p1Pp2p/pP2Pp1P/P4P1K/8/8 b - - 99 50",
            "4k2r/6r1/8/8/8/8/3R4/R3K3 w Qk - 0 1",
            "8/8/8/4p1K1/2k1P3/8/8/8 b - - 0 1",
            // From https://www.chessprogramming.org/Perft_Results
            "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1",
            "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1",
            "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1",
            "r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1",
            "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8",
            "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10",
    };


    for (const auto& fenString : vecFenStrings)
    {
        Board board;

        std::cout << "----- " << fenString << " -----\n";
        ASSERT_TRUE(board.LoadFenString(fenString));
        board.PrintBoard();
        ASSERT_EQ(fenString, board.GenerateFenString());
    }
}

TEST(TestBoard, LoadFenString_invalid)
{
    Board b;

    ASSERT_FALSE(b.LoadFenString("rnbqkbnr"));
    ASSERT_FALSE(b.LoadFenString(" 0 1"));
    ASSERT_FALSE(b.LoadFenString("hgyuidfhjsukhjfvilusdhli"));
    ASSERT_FALSE(b.LoadFenString(""));
    ASSERT_FALSE(b.LoadFenString("Vnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"));
}