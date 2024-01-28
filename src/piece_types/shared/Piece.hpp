#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Piece
{
public:
    const enum PieceType { PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING };
    const enum PieceColor { WHITE, BLACK };

    virtual void move() = 0;
    virtual std::vector<int> getMoves() = 0;

    sf::Sprite getSprite() const { return sprite; }

    Piece() = default;

protected:
    int getPosition() const { return position; }
    std::pair<int, int> getColumnRow() const { return {position % 8, position / 8}; }
    PieceColor getColor() const { return color; }

private:
    int position{};
    PieceColor color{};
    PieceType type{};
    sf::Sprite sprite{};
    sf::Texture texture{};
};

#endif
