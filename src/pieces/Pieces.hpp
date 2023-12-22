#ifndef PIECES_HPP
#define PIECES_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../piece/Piece.hpp"
#include "Pieces.hpp"

class Pieces
{
private:
	Piece piecesArr[8][8];

public:
	Pieces(std::string color, std::string type);
	Piece (*getPieces())[8];
};

#endif
