#ifndef PIECES_HPP
#define PIECES_HPP

#include <iostream>
#include <bitset>
#include <SFML/Graphics.hpp>
#include "../piece/Piece.hpp"
#include "Pieces.hpp"

class Pieces
{
private:
	Piece piecesArr[8][8]{};
	std::bitset<64> bPiecesData[14]{};

public:
	Pieces();
	void displayPieces(sf::RenderWindow &window);
	Piece (*getPieces())[8];
};

#endif
