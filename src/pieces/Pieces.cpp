#include "Pieces.hpp"

Pieces::Pieces(std::string color, std::string type)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			piecesArr[i][j].setTexture(color, type);
			piecesArr[i][j].setPosition(i * 64, j * 64);
		}
	}
}

Piece (*Pieces::getPieces())[8]
{
	return piecesArr;
}
