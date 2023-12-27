#include "Pieces.hpp"

Pieces::Pieces()
{
	// set the bitset
	bPiecesData[0] = std::bitset<64>("0000000000000000000000000000000000000000000000001111111100000000");  // black pawn
	bPiecesData[1] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000000100100");  // black bishop
	bPiecesData[2] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000001000010");  // black knight
	bPiecesData[3] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000010000001");  // black rook
	bPiecesData[4] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000000010000");  // black queen
	bPiecesData[5] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000000001000");  // black king
	bPiecesData[6] = std::bitset<64>("0000000000000000000000000000000000000000000000001111111111111111");  // black all pieces
	bPiecesData[7] = std::bitset<64>("0000000011111111000000000000000000000000000000000000000000000000");  // white pawn
	bPiecesData[8] = std::bitset<64>("0010010000000000000000000000000000000000000000000000000000000000");  // white bishop
	bPiecesData[9] = std::bitset<64>("0100001000000000000000000000000000000000000000000000000000000000");  // white knight
	bPiecesData[10] = std::bitset<64>("1000000100000000000000000000000000000000000000000000000000000000"); // white rook
	bPiecesData[11] = std::bitset<64>("0001000000000000000000000000000000000000000000000000000000000000"); // white queen
	bPiecesData[12] = std::bitset<64>("0000100000000000000000000000000000000000000000000000000000000000"); // white king
	bPiecesData[13] = std::bitset<64>("1111111111111111000000000000000000000000000000000000000000000000"); // white all pieces

	// set the sprites of the Piece class
	for (int i{0}; i < 14; i++)
	{
		for (int j{0}; j < 64; j++)
		{
			if (bPiecesData[i][j] == 1)
			{
				switch (i)
				{
				case 0:
					piecesArr[int(j % 8)][int(j / 8)].setTexture("black", "pawn");
					piecesArr[int(j % 8)][int(j / 8)].setPosition(j % 8 * 64, j / 8 * 64);
					break;
				case 1:
					piecesArr[int(j % 8)][int(j / 8)].setTexture("black", "bishop");
					piecesArr[int(j % 8)][int(j / 8)].setPosition(j % 8 * 64, j / 8 * 64);
					break;
				case 2:
					piecesArr[int(j % 8)][int(j / 8)].setTexture("black", "knight");
					piecesArr[int(j % 8)][int(j / 8)].setPosition(j % 8 * 64, j / 8 * 64);
					break;
				case 3:
					piecesArr[int(j % 8)][int(j / 8)].setTexture("black", "rook");
					piecesArr[int(j % 8)][int(j / 8)].setPosition(j % 8 * 64, j / 8 * 64);
					break;
				case 4:
					piecesArr[int(j % 8)][int(j / 8)].setTexture("black", "queen");
					piecesArr[int(j % 8)][int(j / 8)].setPosition(j % 8 * 64, j / 8 * 64);
					break;
				case 5:
					piecesArr[int(j % 8)][int(j / 8)].setTexture("black", "king");
					piecesArr[int(j % 8)][int(j / 8)].setPosition(j % 8 * 64, j / 8 * 64);
					break;
				case 7:
					piecesArr[int(j % 8)][int(j / 8)].setTexture("white", "pawn");
					piecesArr[int(j % 8)][int(j / 8)].setPosition(j % 8 * 64, j / 8 * 64);
					break;
				case 8:
					piecesArr[int(j % 8)][int(j / 8)].setTexture("white", "bishop");
					piecesArr[int(j % 8)][int(j / 8)].setPosition(j % 8 * 64, j / 8 * 64);
					break;
				case 9:
					piecesArr[int(j % 8)][int(j / 8)].setTexture("white", "knight");
					piecesArr[int(j % 8)][int(j / 8)].setPosition(j % 8 * 64, j / 8 * 64);
					break;
				case 10:
					piecesArr[int(j % 8)][int(j / 8)].setTexture("white", "rook");
					piecesArr[int(j % 8)][int(j / 8)].setPosition(j % 8 * 64, j / 8 * 64);
					break;
				case 11:
					piecesArr[int(j % 8)][int(j / 8)].setTexture("white", "queen");
					piecesArr[int(j % 8)][int(j / 8)].setPosition(j % 8 * 64, j / 8 * 64);
					break;
				case 12:
					piecesArr[int(j % 8)][int(j / 8)].setTexture("white", "king");
					piecesArr[int(j % 8)][int(j / 8)].setPosition(j % 8 * 64, j / 8 * 64);
					break;
				default:
					break;
				}
			}
		}
	}
}

/**
 * draws the pieces using window.draw
 * @param window takes in the window as a reference to use in the display process
 */
void Pieces::displayPieces(sf::RenderWindow &window)
{
	for (int i{0}; i < 8; i++)
	{
		for (int j{0}; j < 8; j++)
		{
			window.draw(piecesArr[i][j].getSprite());
		}
	}
}

Piece (*Pieces::getPieces())[8]
{
	return piecesArr;
}
