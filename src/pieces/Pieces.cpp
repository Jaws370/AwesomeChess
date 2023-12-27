#include "Pieces.hpp"

/**
 * creates the boards for the pieces (bitstrings)
 * and sets all pieces for starting game (textures and such) accordingly
 */
Pieces::Pieces()
{
	// creates a const pieceTypes
	std::string const pieceTypes[6]{"pawn", "bishop", "knight", "rook", "queen", "king"};

	// set the bitset (i.e. boards) for the game
	bPiecesData[0] = std::bitset<64>("0000000000000000000000000000000000000000000000001111111100000000");  // black pawn
	bPiecesData[1] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000000100100");  // black bishop
	bPiecesData[2] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000001000010");  // black knight
	bPiecesData[3] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000010000001");  // black rook
	bPiecesData[4] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000000010000");  // black queen
	bPiecesData[5] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000000001000");  // black king
	bPiecesData[6] = std::bitset<64>("0000000011111111000000000000000000000000000000000000000000000000");  // white pawn
	bPiecesData[7] = std::bitset<64>("0010010000000000000000000000000000000000000000000000000000000000");  // white bishop
	bPiecesData[8] = std::bitset<64>("0100001000000000000000000000000000000000000000000000000000000000");  // white knight
	bPiecesData[9] = std::bitset<64>("1000000100000000000000000000000000000000000000000000000000000000");  // white rook
	bPiecesData[10] = std::bitset<64>("0001000000000000000000000000000000000000000000000000000000000000"); // white queen
	bPiecesData[11] = std::bitset<64>("0000100000000000000000000000000000000000000000000000000000000000"); // white king

	// looping through all the bitsets
	for (int i{0}; i < 12; i++)
	{
		// looping through all of the individual bits
		for (int j{0}; j < 64; j++)
		{
			// if there is a piece there (else there should be no type)
			if (bPiecesData[i][j] == 1)
			{
				// constants for column and row
				int const column = j % 8;
				int const row = j / 8;

				// sets the type of the Piece based on whether the array its going through is < 6
				// and sets pieceTypes based off of which array it is going through
				piecesArr[column][row].setType(i < 6 ? "black" : "white", pieceTypes[i % 6]);
				// sets position based on row and column the piece is in
				piecesArr[column][row].setPosition(column * 64, row * 64);
			}
		}
	}
}

/**
 * takes the position and finds all possible moves for it
 * @param pos1 move to check
 * @returns an array of ints (0-63) representing possible moves
 */
int (*Pieces::getPossibleMoves(int const &pos1))[]
{
	return 0;
}

/**
 * draws the pieces using window.draw
 * @param window takes in the window as a reference to use in the display process
 */
void Pieces::displayPieces(sf::RenderWindow &window)
{
	// loops through the columns and rows
	for (int i{0}; i < 8; i++)
	{
		for (int j{0}; j < 8; j++)
		{
			window.draw(piecesArr[i][j].getSprite());
		}
	}
}

/**
 * returns the piecesArr
 * @returns len: 8 | type: Piece
 */
Piece (*Pieces::getPieces())[8]
{
	return piecesArr;
}
