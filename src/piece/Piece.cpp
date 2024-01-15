#include "Piece.hpp"

void Piece::setType(std::string const& color, PieceType const& type)
{
	this->color = color;
	this->type = type;

	std::string typeStr;
	switch (type)
	{
	case PAWN:
		typeStr = "pawn";
		break;
	case BISHOP:
		typeStr = "bishop";
		break;
	case KNIGHT:
		typeStr = "knight";
		break;
	case ROOK:
		typeStr = "rook";
		break;
	case QUEEN:
		typeStr = "queen";
		break;
	case KING:
		typeStr = "king";
		break;
	}

	if (!image.loadFromFile("assets/image/" + color + "_" + typeStr + ".png"))
		std::cerr << std::endl;

	displayPiece.setTexture(image);
}

void Piece::reset()
{
	this->color = "";
	this->type = NO_PIECE;

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

Piece::PieceType Piece::getType()
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
