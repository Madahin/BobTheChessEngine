//
// Created by madahin on 03/01/23.
//
#include <cstdio>
#include <iostream>

#include "Board.h"

Board::Board(const std::string_view strFenString)
{
    LoadFenString(strFenString);
}

auto Board::LoadFenString(std::string_view strFenString) -> bool
{
    if (!ValidateFENString(strFenString))
    {
        return false;
    }

    uint8_t bFenStringIndex{0}, bCurrentX{0}, bCurrentY{0};

    m_pieces.clear();

    // We save each pieces location into a map
    while (strFenString[bFenStringIndex] != ' ')
    {
        const char bCurrent = strFenString[bFenStringIndex];
        Piece_t bPiece = Piece::FromFenToInt(bCurrent);

        if (bPiece != Piece::None)
        {
            Piece::SetCoordinate(bPiece, Board::BoardIndexFromCoordinate(bCurrentX, bCurrentY));
            m_pieces.push_back(bPiece);
            bCurrentX += 1;
        }
        else if (bCurrent >= '0' && bCurrent <= '9')
        {
            bCurrentX += bCurrent - '0';
        }

        if (bCurrent == '/')
        {
            bCurrentY += 1;
            bCurrentX = 0;
        }

        bFenStringIndex += 1;
    }

    // Skip the ' '
    bFenStringIndex += 1;

    m_whiteToPlay = strFenString[bFenStringIndex] == 'w';

    // Skip the ' '
    bFenStringIndex += 2;

    m_whiteRockPossibility = {false, false};
    m_blackRockPossibility = {false, false};
    if (strFenString[bFenStringIndex] == '-')
    {
        bFenStringIndex += 1;
    }
    else
    {
        while (strFenString[bFenStringIndex] != ' ')
        {
            Piece_t piece = Piece::FromFenToInt(strFenString[bFenStringIndex]);
            RockPossibility& rockPossibility = (Piece::CompareColor(piece, Piece::White)) ? m_whiteRockPossibility : m_blackRockPossibility;
            if (Piece::CompareKind(piece, Piece::King))
            {
                rockPossibility.kingSide = true;
            }
            else if (Piece::CompareKind(piece, Piece::Queen))
            {
                rockPossibility.queenSide = true;
            }
            bFenStringIndex += 1;
        }
    }

    // Skip the ' '
    bFenStringIndex += 1;

    if (strFenString[bFenStringIndex] == '-')
    {
        m_enPassantSquare = NO_EN_PASSANT_SQUARE;
        bFenStringIndex += 1;
    }
    else
    {
        const uint8_t column = strFenString[bFenStringIndex] - 'a';
        const uint8_t line = strFenString[bFenStringIndex+1] - '0';

        m_enPassantSquare = BoardIndexFromCoordinate(column, line);
        bFenStringIndex += 2;
    }

    // Skip the ' '
    bFenStringIndex += 1;

    const int scanfResult = sscanf(strFenString.data() + bFenStringIndex, "%u %u", &m_halfMoveClock, &m_fullMoveNumber);
    return scanfResult == 2;
}

auto Board::GenerateFenString() const -> std::string
{
    std::stringstream ss;

    for (uint8_t y=0; y < BOARD_SIZE; ++y)
    {
        uint16_t emptyCases = 0;
        for (uint8_t x=0; x < BOARD_SIZE; ++x)
        {
            const uint8_t bCaseIndex = BoardIndexFromCoordinate(x, y);
            Piece_t bCurrentPiece = Piece::None;
            for (const auto& p : m_pieces)
            {
                if (Piece::GetCoordinate(p) == bCaseIndex)
                {
                    bCurrentPiece = p;
                    break;
                }
            }
            if (bCurrentPiece == Piece::None)
            {
                emptyCases += 1;
            }
            else
            {
                if (emptyCases)
                {
                    ss << emptyCases;
                    emptyCases = 0;
                }
                ss << Piece::FromIntToFen(bCurrentPiece);
            }
        }
        if (emptyCases)
        {
            ss << emptyCases;
        }
        if (y < (BOARD_SIZE-1))
        {
            ss << '/';
        }
    }

    ss << ' ';
    ss << ((m_whiteToPlay) ? 'w' : 'b');
    ss << ' ';
    if (!(m_whiteRockPossibility.kingSide  ||
          m_whiteRockPossibility.queenSide ||
          m_blackRockPossibility.kingSide  ||
          m_blackRockPossibility.queenSide))
    {
        ss << '-';
    }
    else
    {
        ss << ((m_whiteRockPossibility.kingSide) ? "K" : "")
           << ((m_whiteRockPossibility.queenSide) ? "Q" : "")
           << ((m_blackRockPossibility.kingSide) ? "k" : "")
           << ((m_blackRockPossibility.queenSide) ? "q" : "");
    }
    ss << ' ';
    if (m_enPassantSquare == NO_EN_PASSANT_SQUARE)
    {
        ss << '-';
    }
    else
    {
        uint8_t line{0}, column{0};

        CoordinateFromBoardIndex(m_enPassantSquare, column, line);

        ss << static_cast<char>('a' + column) << static_cast<char>('0' + line);
    }
    ss << ' ';
    ss << m_halfMoveClock;
    ss << ' ';
    ss << m_fullMoveNumber;

    return ss.str();
}

auto Board::ValidateFENString(std::string_view strFenString) -> bool
{
    uint8_t bIndex = 0;
    uint8_t bDataPerLine = 0;
    uint8_t bLineNumber = 1;

    // We only check the board part
    while (strFenString[bIndex] != ' ' && bIndex < strFenString.size())
    {
        const char bCurrent = strFenString[bIndex];

        // if it's a number (no piece)
        if (bCurrent >= '0' && bCurrent <= '9')
        {
            bDataPerLine += bCurrent - '0';
        }
        // If it's a piece
        else if (Piece::FromFenToInt(bCurrent) != Piece::None)
        {
            bDataPerLine += 1;
        }

        // New line
        if (bCurrent == '/')
        {
            bLineNumber += 1;
            if (bDataPerLine != BOARD_SIZE)
            {
                return false;
            }
            else
            {
                bDataPerLine = 0;
            }
        }
        bIndex += 1;
    }

    // If we are here, it means all the lines of the board have the right size,
    // we just need to check if we have the right number of line
    return bLineNumber == BOARD_SIZE;
}

auto Board::PrintBoard() const -> void
{
    static constexpr std::string RESET  = "\x1b[49;0m";
    static constexpr std::string PIECE_DARK  = "\x1b[38;5;232;1m";
    static constexpr std::string PIECE_LIGHT  = "\x1b[38;5;231;1m";
    static constexpr std::string BACKGROUND_DARK  = "\x1b[48;5;172;1m";
    static constexpr std::string BACKGROUND_LIGHT  = "\x1b[48;5;215;1m";
    static constexpr std::string GREY  = "\x1b[38;5;242m";
    static const std::map<Piece_t, std::string> s_piece_ascii = {
            {Piece::King  , "♚ "},
            {Piece::Queen , "♛ "},
            {Piece::Bishop, "♝ "},
            {Piece::Knight, "♞ "},
            {Piece::Rook  , "♜ "},
            {Piece::Pawn  , "♝ "},
            {Piece::None  , "  "},

    };
    for (uint8_t y=0; y < BOARD_SIZE; ++y)
    {
        std::cout << GREY << BOARD_SIZE - y << ' ';
        for (uint8_t x=0; x < BOARD_SIZE; ++x)
        {
            const uint8_t bCaseIndex = BoardIndexFromCoordinate(x, y);
            Piece_t bCurrentPiece = Piece::None;
            for (const auto& p : m_pieces)
            {
                if (Piece::GetCoordinate(p) == bCaseIndex)
                {
                    bCurrentPiece = p;
                    break;
                }
            }

            std::cout << (((x+y) % 2) ? BACKGROUND_DARK : BACKGROUND_LIGHT)
                      << (Piece::CompareColor(bCurrentPiece, Piece::White) ? PIECE_LIGHT : PIECE_DARK)
                      << s_piece_ascii.at(Piece::GetKind(bCurrentPiece))
                      << RESET;
        }
        std::cout << std::endl;
    }
    std::cout << GREY << "  a b c d e f g h" << RESET << std::endl;
}
