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
	std::vector<int> getPossibleMoves(int const &pos1);
    void movePiece(int &pos1, int &pos2);
    void displayPieces(sf::RenderWindow &window);
    Piece (*getPieces())[8];
	static int toInt(int const &col, int const &row);
	void updateBoard();
};

#endif
