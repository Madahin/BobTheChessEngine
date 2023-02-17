//
// Created by madahin on 17/02/2023.
//

#ifndef CHESSENGINE_MOVE_H
#define CHESSENGINE_MOVE_H

#include <array>
#include <memory>
#include <stack>
#include <vector>

#include "Board.h"
#include "Logger.h"
#include "MoveStruct.h"
#include "Piece.h"
#include "Utils.h"

class Board;

typedef std::shared_ptr<std::vector<Move_t>> MoveList_t;

enum Direction {
    NORTH      =  -1,
    SOUTH      =   1,
    EAST       =  8,
    WEST       = -8,
    NORTH_WEST = -9,
    SOUTH_EAST = -9,
    NORTH_EAST =  7,
    SOUTH_WEST = -7
};

class Move
{
public:
    Move() = delete;

    static MoveList_t GenerateMoveFromBoardForDepth(const Board& board, uint64_t depth);
    static MoveList_t GenerateMoveFromBoard(const Board& board);

    static auto MoveToAlgebraicNotation(const Board &board, Move_t move) -> std::string;

private:
    static constexpr auto GenerateMoveData() -> std::array<std::array<uint8_t, 8>, Board::NUM_CASE>;
    static auto GenerateSlidingMoves(const Board &board, Piece_t piece, uint8_t square) -> MoveList_t;
    static auto GenerateKnightMoves(const Board &board, Piece_t piece, uint8_t square) -> MoveList_t;
    static auto GeneratePawnMoves(const Board &board, Piece_t piece, uint8_t square) -> MoveList_t;
    static auto GenerateKingMoves(const Board &board, Piece_t piece, uint8_t square) -> MoveList_t;

private:
    static constexpr std::array<Direction, 8> sm_directionOffset = {
            Direction::NORTH,
            Direction::SOUTH,
            Direction::EAST,
            Direction::WEST,
            Direction::NORTH_WEST,
            Direction::SOUTH_EAST,
            Direction::NORTH_EAST,
            Direction::SOUTH_WEST,
    };

};

#endif//CHESSENGINE_MOVE_H