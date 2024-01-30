#ifndef ROOK_HPP
#define ROOK_HPP

#include <Piece.hpp>

class Rook : public Piece
{
public:
    void move() override = 0;      // TODO add move
    void getMoves() override = 0;  // TODO add getMoves

    Rook() = default;  // TODO add constructor to set texture, color, type, position
}

#endif
