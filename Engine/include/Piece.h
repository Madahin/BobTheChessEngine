//
// Created by madahin on 03/01/23.
//

#ifndef CHESSENGINE_PIECE_H
#define CHESSENGINE_PIECE_H

#include <cctype>
#include <cstdint>
#include <map>

typedef uint16_t Piece_t;

class Piece
{
public:
    Piece() = delete;

    /**
     * @brief convert a piece from a <a href="https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation">FEN string</a> into an integer
     *
     * The first 3 least significant bits represent the piece type
     * and the next 2 bit represent the color of the piece.
     *
     * Examples:
     *  - 'Q' -> 0b10101
     *  - 'b' -> 0b01100
     *  - invalide -> 0
     *
     * @param bFENChar a chess piece from a <a href="https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation">FEN string</a>
     * @return An internal representation of a chess piece
     *
     */
    [[nodiscard]]
    static auto FromFenToInt(char bFENChar) -> Piece_t;

    /**
     * @brief convert an integer into a valid piece <a href="https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation">FEN string</a> chess piece
     *
     * @param bPiece An integer representation of a chess piece
     * @return A <a href="https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation">FEN string</a> representation of a chess piece
     */
    [[nodiscard]]
    static auto FromIntToFen(Piece_t bPiece) -> char;

    /**
     * @param[in,out] piece The piece we want to move
     * @param[in] boardIndex The new coordinate
     * @return A reference to the moved piece
     */
    static constexpr inline auto SetCoordinate(Piece_t& piece, const uint8_t boardIndex) -> Piece_t&
    {
        piece &= 0x1f; // Clean the coordinate
        piece |= boardIndex << 5; // Set the new coordinate
        return piece;
    }

    /**
     * @brief Retrieve the coordinate of a piece
     * @param piece The piece to retrieve coordinate from
     * @return A board index
     */
    [[nodiscard]]
    static constexpr inline auto GetCoordinate(const Piece_t piece) -> uint8_t
    {
        return piece >> 5;
    }

    /**
     * @brief Retreive the kind of piece from a Piece_t
     *
     * @param piece An internal representation of a chess piece to process
     * @return The kind of piece (without the color part)
     */
    [[nodiscard]]
    static constexpr inline auto GetKind(Piece_t piece) -> Piece_t
    {
        return piece & Piece::KIND;
    }

    /**
     * @brief Retreive the color of piece from a Piece_t
     *
     * @param piece An internal representation of a chess piece to process
     * @return The color of piece (without the kind part)
     */
    [[nodiscard]]
    static constexpr inline auto GetColor(Piece_t piece) -> Piece_t
    {
        return piece & Piece::COLOR;
    }

    /**
     * @brief Compare the kind of two chess piece
     * @param piece1 An internal representation of a chess piece
     * @param piece2 An internal representation of a chess piece
     * @return True if the piece are of the same kind. False otherwise
     */
    [[nodiscard]]
    static inline auto CompareKind(Piece_t piece1, Piece_t piece2) -> bool
    {
        return Piece::GetKind(piece1) == Piece::GetKind(piece2);
    }

    /**
     * @brief Compare the color of two chess piece
     * @param piece1 An internal representation of a chess piece
     * @param piece2 An internal representation of a chess piece
     * @return True if the piece are of the same color. False otherwise
     */
    [[nodiscard]]
    static inline auto CompareColor(Piece_t piece1, Piece_t piece2) -> bool
    {
        return Piece::GetColor(piece1) == Piece::GetColor(piece2);
    }

    /**
    * @brief Compare the two chess piece
    * @param piece1 An internal representation of a chess piece
    * @param piece2 An internal representation of a chess piece
    * @return True if the piece are the same. False otherwise
    */
    [[nodiscard]]
    static inline auto Compare(Piece_t piece1, Piece_t piece2) -> bool
    {
        return CompareKind(piece1, piece2) && CompareColor(piece1, piece2);
    }

    // Mask
    static constexpr Piece_t COLOR  = 0x18;
    static constexpr Piece_t KIND   = 0x07;

    // Type
    static constexpr Piece_t None   = 0;
    static constexpr Piece_t Pawn   = 1;
    static constexpr Piece_t Rook   = 2;
    static constexpr Piece_t Knight = 3;
    static constexpr Piece_t Bishop = 4;
    static constexpr Piece_t Queen  = 5;
    static constexpr Piece_t King   = 6;

    // Color
    static constexpr Piece_t White  = 8;
    static constexpr Piece_t Black  = 16;

private:
    static const std::map<char, Piece_t> m_MapFenToInt;
};


#endif //CHESSENGINE_PIECE_H
