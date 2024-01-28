#ifndef BISHOP_HPP
#define BISHOP_HPP

#include <Piece.hpp>

class Bishop : public Piece
{
public:
    void move() override = 0;      // TODO add move
    void getMoves() override = 0;  // TODO add getMoves

    Bishop() = default;  // TODO add constructor to set texture, color, type, position
}

#endif
