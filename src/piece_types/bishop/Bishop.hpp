#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "../piece_base/PieceBase.hpp"

class Bishop : public PieceBase
{
public:
    void move() override { return; };                     // TODO add move
    std::vector<int> getMoves() override { return {}; };  // TODO add getMoves

    Bishop(int position);  // TODO add constructor to set color, position
};

#endif
