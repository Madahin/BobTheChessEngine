//
// Created by madahin on 03/01/23.
//
#include "gtest/gtest.h"
#include "Piece.h"

TEST(TestPiece, FenPieceToInt_black)
{
    ASSERT_EQ(Piece::FromFenToInt('p'), Piece::Pawn   | Piece::Black);
    ASSERT_EQ(Piece::FromFenToInt('r'), Piece::Rook   | Piece::Black);
    ASSERT_EQ(Piece::FromFenToInt('n'), Piece::Knight | Piece::Black);
    ASSERT_EQ(Piece::FromFenToInt('b'), Piece::Bishop | Piece::Black);
    ASSERT_EQ(Piece::FromFenToInt('q'), Piece::Queen  | Piece::Black);
    ASSERT_EQ(Piece::FromFenToInt('k'), Piece::King   | Piece::Black);
}

TEST(TestPiece, FenPieceToInt_white)
{
    ASSERT_EQ(Piece::FromFenToInt('P'), Piece::Pawn   | Piece::White);
    ASSERT_EQ(Piece::FromFenToInt('R'), Piece::Rook   | Piece::White);
    ASSERT_EQ(Piece::FromFenToInt('N'), Piece::Knight | Piece::White);
    ASSERT_EQ(Piece::FromFenToInt('B'), Piece::Bishop | Piece::White);
    ASSERT_EQ(Piece::FromFenToInt('Q'), Piece::Queen  | Piece::White);
    ASSERT_EQ(Piece::FromFenToInt('K'), Piece::King   | Piece::White);
}

TEST(TestPiece, FromIntToFen_black)
{
    ASSERT_EQ(Piece::FromIntToFen(Piece::Pawn   | Piece::Black), 'p');
    ASSERT_EQ(Piece::FromIntToFen(Piece::Rook   | Piece::Black), 'r');
    ASSERT_EQ(Piece::FromIntToFen(Piece::Knight | Piece::Black), 'n');
    ASSERT_EQ(Piece::FromIntToFen(Piece::Bishop | Piece::Black), 'b');
    ASSERT_EQ(Piece::FromIntToFen(Piece::Queen  | Piece::Black), 'q');
    ASSERT_EQ(Piece::FromIntToFen(Piece::King   | Piece::Black), 'k');
}

TEST(TestPiece, FromIntToFen_white)
{
    ASSERT_EQ(Piece::FromIntToFen(Piece::Pawn   | Piece::White), 'P');
    ASSERT_EQ(Piece::FromIntToFen(Piece::Rook   | Piece::White), 'R');
    ASSERT_EQ(Piece::FromIntToFen(Piece::Knight | Piece::White), 'N');
    ASSERT_EQ(Piece::FromIntToFen(Piece::Bishop | Piece::White), 'B');
    ASSERT_EQ(Piece::FromIntToFen(Piece::Queen  | Piece::White), 'Q');
    ASSERT_EQ(Piece::FromIntToFen(Piece::King   | Piece::White), 'K');
}
