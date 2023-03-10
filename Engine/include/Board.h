//
// Created by madahin on 03/01/23.
//

#ifndef CHESSENGINE_BOARD_H
#define CHESSENGINE_BOARD_H

#include <array>
#include <cassert>
#include <cstdint>
#include <map>
#include <stack>
#include <string>
#include <sstream>
#include <string_view>
#include <tuple>
#include <vector>

#include "MoveStruct.h"
#include "Piece.h"

/**
 * @brief Chessboard representation
 *
 * This class implement a chess board with this
 * coordinate system :
 *
 *     a   b   c   d   e   f   g   h
 *   ┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓
 * 8 ┃56 ┃57 ┃58 ┃59 ┃60 ┃61 ┃62 ┃63 ┃ 8
 *   ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
 * 7 ┃48 ┃49 ┃50 ┃51 ┃52 ┃53 ┃54 ┃55 ┃ 7
 *   ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
 * 6 ┃40 ┃41 ┃42 ┃43 ┃44 ┃45 ┃46 ┃47 ┃ 6
 *   ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
 * 5 ┃32 ┃33 ┃34 ┃35 ┃36 ┃37 ┃38 ┃39 ┃ 5
 *   ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
 * 4 ┃24 ┃25 ┃26 ┃27 ┃28 ┃29 ┃30 ┃31 ┃ 4
 *   ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
 * 3 ┃16 ┃17 ┃18 ┃19 ┃20 ┃21 ┃22 ┃23 ┃ 3
 *   ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
 * 2 ┃ 8 ┃ 9 ┃10 ┃11 ┃12 ┃13 ┃14 ┃15 ┃ 2
 *   ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
 * 1 ┃ 0 ┃ 1 ┃ 2 ┃ 3 ┃ 4 ┃ 5 ┃ 6 ┃ 7 ┃ 1
 *   ┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛
 *     a   b   c   d   e   f   g   h
 *
 * The white side being the bottom side (rank 1 and 2)
 */

class Board
{
    struct RockPossibility
    {
        bool kingSide;
        bool queenSide;
    };

    static constexpr uint8_t NO_EN_PASSANT_SQUARE = 0xff;

public:
    explicit Board(std::string_view strFenString="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    auto ApplyMove(const Move_t& move) -> void;
    auto UnmakeMove() -> void;

    auto LoadFenString(std::string_view strFenString) -> bool;

    /**
     * @Brief Retrieve the list of piece on the current board
     * @return A vector of piece
     */
    [[nodiscard]]
    inline auto GetPieces() const -> const std::vector<Piece_t>&
    {
        return m_pieces;
    }

    /**
     * @Brief Retrieve the content of a square at a given coordinate
     * @param coordinate
     * @return A chess Piece or an empty Piece
     */
    [[nodiscard]]
    inline auto GetSquareContent(const uint8_t coordinate) const -> Piece_t
    {
        assert((coordinate >= 0) && (coordinate < (NUM_CASE)));
        return m_boardData[coordinate];
    }

    [[nodiscard]]
    constexpr auto GetColorToMove() const -> Piece_t
    {
        return (m_whiteToPlay ? Piece::White : Piece::Black);
    }

    /**
     * @Brief Generate a FEN string from the current board
     * @return The FEN string
     */
    [[nodiscard]]
    auto GenerateFenString() const -> std::string;

    /**
     * @brief Print the current chessboard to stdout or stderr
     * @param[in] buffered If true, print to stdout, else print to stderr
     */
    auto PrintBoard(bool buffered=true) const -> void;

    /**
     * @brief Compute a board index from xy coordinate
     *
     * @param[in] x The column number
     * @param[in] y The line number
     * @return The board coordinate, in [0, 64)
     */
    static constexpr auto BoardIndexFromCoordinate(const uint8_t x, const uint8_t y) -> uint8_t
    {
        return x + BOARD_SIZE * y;
    }

    /**
     * @brief Compute coordinate from a board index
     *
     * @param[in] boardIndex The index of a case
     * @param[out] x A column number
     * @param[out] y A line number
     */
    static constexpr auto CoordinateFromBoardIndex(const uint8_t boardIndex, uint8_t& x, uint8_t& y) -> void
    {
        y = boardIndex / BOARD_SIZE;
        x = boardIndex % BOARD_SIZE;
    }

    static inline auto CoordinateToChessNotation(const uint8_t x, const uint8_t y) -> std::string
    {
        std::stringstream ss;

        ss << static_cast<char>('a' + x) << static_cast<char>('1' + y);

        return ss.str();
    }

    static inline auto BoardIndexToChessNotation(const uint8_t boardIndex) -> std::string
    {
        uint8_t x{0};
        uint8_t y{0};

        CoordinateFromBoardIndex(boardIndex, x, y);
        return CoordinateToChessNotation(x, y);
    }

private:
    [[nodiscard]]
    static auto ValidateFENString(std::string_view strFenString) -> bool;

public:
    static constexpr uint8_t BOARD_SIZE = 8;
    static constexpr uint8_t NUM_CASE   = BOARD_SIZE * BOARD_SIZE;

private:
    std::array<Piece_t, NUM_CASE> m_boardData{};
    std::vector<Piece_t> m_pieces{};
    std::stack<Move_t> m_appliedMoves{};
    bool m_whiteToPlay{true};
    RockPossibility m_whiteRockPossibility{true, true};
    RockPossibility m_blackRockPossibility{true, true};
    uint8_t m_enPassantSquare{NO_EN_PASSANT_SQUARE};
    uint32_t m_halfMoveClock{0};
    uint32_t m_fullMoveNumber{1};
};

#endif //CHESSENGINE_BOARD_H
