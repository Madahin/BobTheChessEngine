//
// Created by madahin on 17/02/2023.
//

#ifndef CHESSENGINE_MOVE_H
#define CHESSENGINE_MOVE_H

#include <memory>
#include <vector>

#include "Board.h"
#include "Piece.h"

typedef std::shared_ptr<std::vector<uint8_t>> MoveList_t;

class Move
{
public:
    Move() = delete;

    static MoveList_t GenerateMoveFromBoardForDepth(const Board& board, const uint64_t depth);
};

#endif//CHESSENGINE_MOVE_H