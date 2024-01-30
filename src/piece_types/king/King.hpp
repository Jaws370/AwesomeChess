#ifndef KING_HPP
#define KING_HPP

#include <Piece.hpp>

class King : public Piece
{
public:
    void move() override = 0;      // TODO add move
    void getMoves() override = 0;  // TODO add getMoves

    // TODO need to decide if get all opponents moves is here or not
    void getCastling() = 0; // TODO add getCastling

    King() = default;  // TODO add constructor to set texture, color, type, position
}

#endif
