#ifndef PIECES_HPP
#define PIECES_HPP

#include "../piece/Piece.hpp"
#include "Pieces.hpp"
#include <iostream>
#include <bitset>
#include <SFML/Graphics.hpp>

class Pieces
{
private:
	Piece piecesArr[8][8]{};
	std::bitset<64> bPiecesData[14]{};

public:
	Pieces();
	std::vector<int> getPossibleMoves(int const& pos, bool checkingKing = false);
	void movePiece(int& pos1, int& pos2);
	void displayPieces(sf::RenderWindow& window);
	static int toInt(int const& col, int const& row);
	std::vector<int> getAllMoves(std::string color);
	void updateBoard();
};

#endif
