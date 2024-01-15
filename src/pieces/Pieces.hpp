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
	std::vector<std::pair<int, std::vector<int>>> getPawnMoves(const int& pos);
	std::vector<std::pair<int, std::vector<int>>> getBishopMoves(const int& pos);
	std::vector<std::pair<int, std::vector<int>>> getKnightMoves(const int& pos);
	std::vector<std::pair<int, std::vector<int>>> getRookMoves(const int& pos);
	std::vector<std::pair<int, std::vector<int>>> getQueenMoves(const int& pos);
	std::vector<std::pair<int, std::vector<int>>> getKingMoves(const int& pos, const bool& checkingKing);

public:
	Pieces();
	std::vector<std::pair<int, std::vector<int>>> getPossibleMoves(const int& pos, const bool checkingKing = false);
	void movePiece(int& pos1, int& pos2, std::vector<int>& additonalMoves);
	void displayPieces(sf::RenderWindow& window);
	static int toInt(const int& col, const int& row);
	static std::pair<int, int> toColRow(const int& pos);
	std::vector<int> getAllMoves(std::string color);
	void resize(const float& spaceSize);
	void updateBoard();
};

#endif
