//
// Created by madahin on 03/01/23.
//

#include "Piece.h"
#include "Logger.h"

const std::map<char, Piece_t> Piece::m_MapFenToInt = {
        { 'p', Piece::Pawn },
        { 'r', Piece::Rook },
        { 'n', Piece::Knight },
        { 'b', Piece::Bishop },
        { 'q', Piece::Queen },
        { 'k', Piece::King }
};

auto Piece::FromFenToInt(const char bFENChar) -> Piece_t
{
    const char bLowerFenChar = static_cast<char>(std::tolower(bFENChar));

    if (m_MapFenToInt.find(bLowerFenChar) == m_MapFenToInt.end())
    {
        return Piece::None;
    }

    return m_MapFenToInt.at(bLowerFenChar) | ((std::islower(bFENChar)) ? Piece::Black : Piece::White);
}

auto Piece::FromIntToFen(const Piece_t bPiece) -> char
{
    char bFenChar = '\0';
    const Piece_t bPieceKind = Piece::GetKind(bPiece);
    const bool bIsWhite = bPiece & Piece::White;

    for (const auto& kv : m_MapFenToInt)
    {
        if (kv.second == bPieceKind)
        {
            bFenChar = kv.first;
            if (bIsWhite)
            {
                bFenChar = static_cast<char>(std::toupper(bFenChar));
            }
            break;
        }
    }

    return bFenChar;
}
