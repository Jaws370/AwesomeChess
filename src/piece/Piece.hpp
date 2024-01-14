#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class Piece
{
private:
	sf::Texture image{};
	std::string color{};
	std::string type{};
	sf::Sprite displayPiece{};

public:
	Piece() = default;
	void setType(std::string const& color, std::string const& type);
	sf::Sprite getSprite();
	std::string getType();
	std::string getColor();
	void setPosition(int const& x, int const& y);
	void setScale(float const& x, float const& y);
	void reset();
};

#endif
