#ifndef QUEEN_HPP
#define QUEEN_HPP

#include <Piece.hpp>

class Queen : public Piece
{
public:
    void move() override = 0;      // TODO add move
    void getMoves() override = 0;  // TODO add getMoves

    Queen() = default;  // TODO add constructor to set texture, color, type, position
}

#endif
