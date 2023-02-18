//
// Created by madahin on 17/02/23.
//

#ifndef BOBTHECHESSENGINE_MOVESTRUCT_H
#define BOBTHECHESSENGINE_MOVESTRUCT_H

enum class MoveType {
    MOVE,
    CAPTURE,
    EN_PASSANT,
    ROOK
};

struct Move_t
{
    uint8_t originalSquare;
    uint8_t targetSquare;
    MoveType type;
};

#endif //BOBTHECHESSENGINE_MOVESTRUCT_H
