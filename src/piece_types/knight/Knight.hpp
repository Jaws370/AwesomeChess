#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <Piece.hpp>

class Knight : public Piece
{
public:
    void move() override = 0;      // TODO add move
    void getMoves() override = 0;  // TODO add getMoves

    Knight() = default;  // TODO add constructor to set texture, color, type, position
}

#endif