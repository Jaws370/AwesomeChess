#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class PieceBase
{
public:
    // enumerations
    const enum PieceType { PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING };
    const enum PieceColor { WHITE, BLACK };

    // constructor
    PieceBase() = default;

    // movement methods
    virtual void move() = 0;
    virtual std::vector<int> getMoves() = 0;

    // accessor for displaying
    sf::Sprite getSprite() const { return sprite; }

protected:
    // accessors
    int getPosition() const { return position; }
    std::pair<int, int> getColumnRow() const { return {position % 8, position / 8}; }
    PieceColor getColor() const { return color; }

    // mutators
    void setTexture(const std::string &path) { texture.loadFromFile(path); }
    void setType(PieceType type) { this->type = type; }
    void setPosition(int position) { sprite.setPosition(position % 8 * 64, position / 8 * 64); }
    void setSprite() { sprite.setTexture(this->texture); }

private:
    // private instance variables
    int position{};
    PieceColor color{};
    PieceType type{};
    sf::Sprite sprite{};
    sf::Texture texture{};
};

#endif
