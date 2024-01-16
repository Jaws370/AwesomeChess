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
	float pieceScale{ 1.f };
	std::bitset<64> bPiecesData[14]{};
	std::vector<int> allLastMoves{};
	std::vector<std::pair<int, std::vector<int>>> getPawnMoves(const int& pos);
	std::vector<std::pair<int, std::vector<int>>> getBRQMoves(const int& pos, const vector<int>& directions);
	std::vector<std::pair<int, std::vector<int>>> getKnKMoves(const int& pos, const vector<int>& directions);
	std::vector<std::pair<int, std::vector<int>>> getKingCastling(const int& pos);
	std::vector<std::pair<int, std::vector<int>>> removeChecks(const vector<int>& tempOutput);

public:
	Pieces();
	std::vector<std::pair<int, std::vector<int>>> getPossibleMoves(const int& pos, const bool checkingKing = false);
	void movePiece(int& pos1, int& pos2, std::vector<int>& additonalMoves);
	void displayPieces(sf::RenderWindow& window);
	static int toInt(const int& col, const int& row);
	static std::pair<int, int> toColRow(const int& pos);
	static std::vector<auto> combineVectors(vector<auto>& v1, vector<auto>& v2);
	std::vector<int> getAllMoves(std::string color);
	void resize(const float& spaceSize);
	void updateBoard();
};

#endif
