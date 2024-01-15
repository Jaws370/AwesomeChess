#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class Piece
{
public:
	enum PieceType
	{
		PAWN,
		BISHOP,
		KNIGHT,
		ROOK,
		QUEEN,
		KING,
		NO_PIECE
	};
	Piece() = default;
	void setType(std::string const& color, PieceType const& type);
	sf::Sprite getSprite();
	PieceType getType();
	std::string getColor();
	void setPosition(int const& x, int const& y);
	void setScale(float const& x, float const& y);
	void reset();
private:
	sf::Texture image{};
	std::string color{};
	PieceType type{};
	sf::Sprite displayPiece{};
};

#endif
