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
	bPiecesData[12] = std::bitset<64>("0000000000000000000000000000000000000000000000001111111111111111"); // all black pieces
	bPiecesData[13] = std::bitset<64>("1111111111111111000000000000000000000000000000000000000000000000"); // all white pieces

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
 * ! created for the getPossibleMoves method
 * takes the column and the row and returns an int (0-63)
 * of that position on the board
 * @param col the column
 * @param row the row
 * @returns an int (0-63) representing positioning on the board
 */
int Pieces::toInt(int const &col, int const &row)
{
	return (row * 8) + col;
}

/**
 * takes the position and finds all possible moves for it
 * @param pos1 move to check
 * @returns an array of ints (0-63) representing possible moves
 */
std::vector<int> Pieces::getPossibleMoves(int const &pos)
{
	// get the column and the row from the current position
	int const col = pos % 8;
	int const row = pos / 8;

	// gets the type and color of the piece
	std::string const color{piecesArr[col][row].getColor()};
	std::string const type{piecesArr[col][row].getType()};

	// creates the output vector
	std::vector<int> output{};

	// gets pawn moves
	if (type == "pawn") // TODO need to add not moved checking and en passent
	{
		// needs to move up the board if white
		if (color == "white")
		{
			if ((bPiecesData[12] | bPiecesData[13])[toInt(col, row - 1)] == 0)
			{
				output.push_back(toInt(col, row - 1));

				if ((bPiecesData[12] | bPiecesData[13])[toInt(col, row - 2)] == 0)
				{
					output.push_back(toInt(col, row - 2)); // TODO need to make it so it only added when not moved
				}
			}
		}
		// needs to move down the board if black
		else
		{
			if ((bPiecesData[12] | bPiecesData[13])[toInt(col, row + 1)] == 0)
			{
				output.push_back(toInt(col, row + 1));
				if ((bPiecesData[12] | bPiecesData[13])[toInt(col, row + 2)] == 0)
				{
					output.push_back(toInt(col, row + 2)); // TODO need to make it so it only added when not moved
				}
			}
		}
	}
	// gets knight moves
	else if (type == "knight")
	{
		// creates a vector containing all possible knight moves
		std::vector<std::pair<int, int>> directions{{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

		// checks each direction
		for (auto &direction : directions)
		{
			// creates new col and row
			int newCol{col + direction.first};
			int newRow{row + direction.second};

			// checks if is in range of board
			if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
			{
				// checks if own piece is there (if so then it cannot go there)
				if (bPiecesData[color == "white" ? 13 : 12][toInt(newCol, newRow)] == 1)
				{
					continue;
				}
				output.push_back(toInt(newCol, newRow));
			}
		}
	}
	// gets bishop moves
	else if (type == "bishop")
	{
		// each direction the piece can go
		std::vector<std::pair<int, int>> directions{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};

		// checks each direction
		for (auto &direction : directions)
		{
			// keeps track of the columns and the rows
			int newCol{col + direction.first};
			int newRow{row + direction.second};

			// iterates as long as they are inside of the range of the board
			while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
			{
				// checks if own piece is there (if so then it cannot go there)
				if (bPiecesData[color == "white" ? 13 : 12][toInt(newCol, newRow)] == 1)
				{
					// stops checking this direction
					break;
				}

				// add current check as possible move
				output.push_back(toInt(newCol, newRow));

				// checks if opponsent's piece is there (if so can go there)
				if (bPiecesData[color == "black" ? 13 : 12][toInt(newCol, newRow)] == 1)
				{
					// stops checking this direction
					break;
				}

				// checking next space
				newCol += direction.first;
				newRow += direction.second;
			}
		}
	}
	// gets rook moves
	else if (type == "rook")
	{
		// the directions this piece can move
		std::vector<std::pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

		// checks each direction
		for (auto &direction : directions)
		{
			// keeps track of the columns and the rows
			int newCol{col + direction.first};
			int newRow{row + direction.second};

			// iterates as long as they are inside of the range of the board
			while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
			{
				// checks if own piece is there (if so then it cannot go there)
				if (bPiecesData[color == "white" ? 13 : 12][toInt(newCol, newRow)] == 1)
				{
					// stops checking this direction
					break;
				}

				// add current check as possible move
				output.push_back(toInt(newCol, newRow));

				// checks if opponsent's piece is there (if so can go there)
				if (bPiecesData[color == "black" ? 13 : 12][toInt(newCol, newRow)] == 1)
				{
					// stops checking this direction
					break;
				}

				// checking next space
				newCol += direction.first;
				newRow += direction.second;
			}
		}
	}
	// gets queen moves
	else if (type == "queen")
	{
		// the directions this piece can move
		std::vector<std::pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1}};

		// checks each direction
		for (auto &direction : directions)
		{
			// keeps track of the columns and the rows
			int newCol{col + direction.first};
			int newRow{row + direction.second};

			// iterates as long as they are inside of the range of the board
			while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
			{
				// checks if own piece is there (if so then it cannot go there)
				if (bPiecesData[color == "white" ? 13 : 12][toInt(newCol, newRow)] == 1)
				{
					// stops checking this direction
					break;
				}

				// add current check as possible move
				output.push_back(toInt(newCol, newRow));

				// checks if opponsent's piece is there (if so can go there)
				if (bPiecesData[color == "black" ? 13 : 12][toInt(newCol, newRow)] == 1)
				{
					// stops checking this direction
					break;
				}

				// checking next space
				newCol += direction.first;
				newRow += direction.second;
			}
		}
	}
	// gets king moves
	else if (type == "king") // TODO need to add checks checking and castling
	{
		// creates a vector containing all possible knight moves
		std::vector<std::pair<int, int>> directions{{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

		// checks each direction
		for (auto &direction : directions)
		{
			// creates new col and row
			int newCol{col + direction.first};
			int newRow{row + direction.second};

			// checks if is in range of board
			if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
			{
				// checks if own piece is there (if so then it cannot go there)
				if (bPiecesData[color == "white" ? 13 : 12][toInt(newCol, newRow)] == 1)
				{
					continue;
				}
				output.push_back(toInt(newCol, newRow));
			}
		}
	}

	std::cout << type << " " << color << std::endl;
	std::cout << col << " " << row << std::endl;

	if (!output.empty())
	{
		for (int i{0}; i < output.size(); i++)
		{
			std::cout << output[i] << std::endl;
		}
	}

	return output;
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
