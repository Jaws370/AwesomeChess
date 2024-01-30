#ifndef PAWN_HPP
#define PAWN_HPP

#include <Piece.hpp>

class Pawn : public Piece
{
public:
    void move() override = 0;      // TODO add move
    void getMoves() override = 0;  // TODO add getMoves

    void getEnPassant() = 0;
    // need to re-add promoting (maybe with display this time)

    Pawn() = default;  // TODO add constructor to set texture, color, type, position
}

#endif
