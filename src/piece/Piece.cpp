#include "Piece.hpp"

void Piece::setType(std::string const& color, std::string const& type)
{
	this->color = color;
	this->type = type;

	if (!image.loadFromFile("assets/image/" + color + "_" + type + ".png"))
		std::cerr << std::endl;

	displayPiece.setTexture(image);
}

void Piece::reset()
{
	this->color = "";
	this->type = "";

	if (!image.loadFromFile("assets/image/blank.png"))
		std::cerr << std::endl;

	displayPiece.setTexture(image);
}

sf::Sprite Piece::getSprite()
{
	return displayPiece;
}

void Piece::setPosition(int const& x, int const& y)
{
	displayPiece.setPosition(x, y);
}

std::string Piece::getType()
{
	return type;
}

std::string Piece::getColor()
{
	return color;
}

void Piece::setScale(float const& x, float const& y)
{
	displayPiece.setScale(x, y);
}
