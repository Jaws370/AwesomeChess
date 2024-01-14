#ifndef PIECES_HPP
#define PIECES_HPP

#include "../piece/Piece.hpp"
#include <bitset>
#include <iostream>
#include <SFML/Graphics.hpp>

class Pieces
{
private:
	Piece piecesArr[8][8]{};
	float spaceSize{ 64.f };
	float spaceScale{ 1.f };
	std::bitset<64> bPiecesData[14]{};
	std::vector<int> allLastMoves{};

public:
	Pieces();
	std::vector<std::pair<int, std::vector<int>>> getPossibleMoves(const int& pos, const bool checkingKing = false);
	void movePiece(int& pos1, int& pos2);																			// normal movement
	void movePiece(int& pos1, int& pos2, int& remove);																// en passant
	void movePiece(int& pos1, int& pos2, int& pos3, int& pos4);														// castling
	void displayPieces(sf::RenderWindow& window);
	static int toInt(const int& col, const int& row);
	std::vector<int> getAllMoves(std::string color);
	void resize(const float& spaceSize);
	void updateBoard();
};

#endif
