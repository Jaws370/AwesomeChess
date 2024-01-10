#include "Pieces.hpp"

/**
 * creates the boards for the pieces (bit-strings)
 * and sets all pieces for starting game (textures and such) accordingly
 */
Pieces::Pieces()
{
	// creates a const pieceTypes
	std::string const pieceTypes[6]{ "pawn", "bishop", "knight", "rook", "queen", "king" };

	// set the bit-set (i.e. boards) for the game
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

	updateBoard();
}

/**
 * ! created for the getPossibleMoves method
 * takes the column and the row and returns an int (0-63)
 * of that position on the board
 * @param col the column
 * @param row the row
 * @returns an int (0-63) representing positioning on the board
 */
int Pieces::toInt(int const& col, int const& row)
{
	return (row * 8) + col;
}

/**
 * takes the position and finds all possible moves for it
 * @param pos1 move to check
 * @param checkingKing true if running while checking king (default value is false)
 * @returns an array of integers (0-63) representing possible moves
 */
std::vector<int> Pieces::getPossibleMoves(int const& pos, bool checkingKing)
{
	// get the column and the row from the current position
	int const col = pos % 8;
	int const row = pos / 8;

	// gets the type and color of the piece
	std::string const color{ piecesArr[col][row].getColor() };
	std::string const type{ piecesArr[col][row].getType() };

	// creates the output vector
	std::vector<int> output{};

	bool const hasMoved{ true };

	// gets pawn moves
	if (type == "pawn") // TODO need to add en passent
	{
		// needs to move up the board if white (neg row)
		if (color == "white")
		{
			if ((bPiecesData[12] | bPiecesData[13])[toInt(col, row - 1)] == 0)
			{
				output.push_back(toInt(col, row - 1));

				if ((bPiecesData[12] | bPiecesData[13])[toInt(col, row - 2)] == 0 && row == 6)
				{
					output.push_back(toInt(col, row - 2));
				}
			}

			// can capture diagonally
			if ((bPiecesData[12])[toInt(col - 1, row - 1)] == 1)
			{
				output.push_back(toInt(col - 1, row - 1));
			}
			if (bPiecesData[12][toInt(col + 1, row - 1)] == 1)
			{
				output.push_back(toInt(col + 1, row - 1));
			}
		}
		// needs to move down the board if black (pos row)
		else
		{
			if ((bPiecesData[12] | bPiecesData[13])[toInt(col, row + 1)] == 0)
			{
				output.push_back(toInt(col, row + 1));

				if ((bPiecesData[12] | bPiecesData[13])[toInt(col, row + 2)] == 0 && row == 1)
				{
					output.push_back(toInt(col, row + 2));
				}
			}

			// can capture diagonally
			if (bPiecesData[12][toInt(col - 1, row + 1)] == 1)
			{
				output.push_back(toInt(col - 1, row + 1));
			}
			if (bPiecesData[12][toInt(col + 1, row + 1)] == 1)
			{
				output.push_back(toInt(col + 1, row + 1));
			}
		}
	}
	// gets knight moves
	else if (type == "knight")
	{
		// creates a vector containing all possible knight moves
		std::vector<std::pair<int, int>> directions{ {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2} };

		// checks each direction
		for (auto& direction : directions)
		{
			// creates new col and row
			int newCol{ col + direction.first };
			int newRow{ row + direction.second };

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
		std::vector<std::pair<int, int>> directions{ {1, 1}, {-1, 1}, {-1, -1}, {1, -1} };

		// checks each direction
		for (auto& direction : directions)
		{
			// keeps track of the columns and the rows
			int newCol{ col + direction.first };
			int newRow{ row + direction.second };

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

				// checks if opponent's piece is there (if so can go there)
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
		std::vector<std::pair<int, int>> directions{ {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

		// checks each direction
		for (auto& direction : directions)
		{
			// keeps track of the columns and the rows
			int newCol{ col + direction.first };
			int newRow{ row + direction.second };

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

				// checks if opponent's piece is there (if so can go there)
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
		std::vector<std::pair<int, int>> directions{ {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1} };

		// checks each direction
		for (auto& direction : directions)
		{
			// keeps track of the columns and the rows
			int newCol{ col + direction.first };
			int newRow{ row + direction.second };

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

				// checks if opponent's piece is there (if so can go there)
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
	else if (type == "king") // TODO need to add castling
	{
		std::vector<int> tempOutput{};

		// creates a vector containing all possible knight moves
		std::vector<std::pair<int, int>> directions{ {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1} };

		// checks each direction
		for (auto& direction : directions)
		{
			// creates new col and row
			int newCol{ col + direction.first };
			int newRow{ row + direction.second };

			// checks if is in range of board
			if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
			{
				// checks if own piece is there (if so then it cannot go there)
				if (bPiecesData[color == "white" ? 13 : 12][toInt(newCol, newRow)] == 1)
				{
					continue;
				}
				tempOutput.push_back(toInt(newCol, newRow));
			}
		}

		/*
		if (bPiecesData[3][toInt(col - 4, row)] == 1 && (bPiecesData[5][toInt(4, 7)]) && hasMoved == false) {
		}
		else if ((bPiecesData[3][toInt(col + 3, row)] == 1 && (bPiecesData[5][toInt(4, 7)]) && hasMoved == false)) {
		}
		*/

		// gets all of the possible moves for the other color
		if (!checkingKing)
		{
			std::vector<int> checkSpaces{ getAllMoves(color == "white" ? "black" : "white") };

			// removes all moves that are in check
			for (int i{ 0 }; i < tempOutput.size(); i++)
			{
				// if not in check
				if (std::find(checkSpaces.begin(), checkSpaces.end(), tempOutput[i]) == checkSpaces.end())
				{
					output.push_back(tempOutput[i]);
				}
			}
		}
	}

	std::cout << type << " " << color << std::endl;
	std::cout << col << " " << row << std::endl;

	if (!output.empty())
	{
		for (int i{ 0 }; i < output.size(); i++)
		{
			std::cout << output[i] << std::endl;
		}
	}

	return output;
}

/**
 * changes the bit-sets that represent the board
 * @param pos1 takes in the old position
 * @param pos2 takes in new position
 */
void Pieces::movePiece(int& pos1, int& pos2)
{
	// create vector with types of moves (helps with choosing from bPiecesData)
	std::vector<std::string> const boardTypeArr{ "pawn", "bishop", "knight", "rook", "queen", "king" };

	// create a bit value representing each of the pieces we are moving
	std::bitset<64> bPos1{ "0000000000000000000000000000000000000000000000000000000000000001" };
	bPos1 = bPos1 << pos1;

	std::bitset<64> bPos2{ "0000000000000000000000000000000000000000000000000000000000000001" };
	bPos2 = bPos2 << pos2;

	// move its own piece
	std::string color{ piecesArr[pos1 % 8][pos1 / 8].getColor() };
	std::string type{ piecesArr[pos1 % 8][pos1 / 8].getType() };

	int board{ int(find(boardTypeArr.begin(), boardTypeArr.end(), type) - boardTypeArr.begin()) };
	board += color == "white" ? 6 : 0;

	bPiecesData[board] = bPiecesData[board] ^ bPos1;
	bPiecesData[board] = bPiecesData[board] | bPos2;

	// update the piecesData for its own color
	bPiecesData[color == "white" ? 13 : 12] = bPiecesData[color == "white" ? 13 : 12] ^ bPos1;
	bPiecesData[color == "white" ? 13 : 12] = bPiecesData[color == "white" ? 13 : 12] | bPos2;

	// take out piece if it is taking a piece
	color = piecesArr[pos2 % 8][pos2 / 8].getColor();
	type = piecesArr[pos2 % 8][pos2 / 8].getType();

	if (type == "")
	{
		updateBoard();
		return;
	}

	board = find(boardTypeArr.begin(), boardTypeArr.end(), type) - boardTypeArr.begin();
	board += color == "white" ? 6 : 0;

	// remove taken piece
	bPiecesData[board] = bPiecesData[board] ^ bPos2;

	bPiecesData[color == "white" ? 13 : 12] = bPiecesData[color == "white" ? 13 : 12] ^ bPos2;

	// update board
	updateBoard();
}

/**
 * re-uploads data to the piecesArr
 */
void Pieces::updateBoard()
{
	// outlines the types of pieces for easy sorting
	std::string const pieceTypes[6]{ "pawn", "bishop", "knight", "rook", "queen", "king" };

	// resets them all
	for (int i{ 0 }; i < 8; i++)
	{
		for (int j{ 0 }; j < 8; j++)
		{
			piecesArr[i][j].reset();
		}
	}

	// looping through all the bit-sets
	for (int i{ 0 }; i < 12; i++)
	{
		// looping through all of the individual bits
		for (int j{ 0 }; j < 64; j++)
		{
			// constants for column and row
			int const col = j % 8;
			int const row = j / 8;

			// if there is a piece there (else there should be no type)
			if (bPiecesData[i][j] == 1)
			{
				// sets the type of the Piece based on whether the array its going through is < 6
				// and sets pieceTypes based off of which array it is going through
				piecesArr[col][row].setType(i < 6 ? "black" : "white", pieceTypes[i % 6]);
				// sets position based on row and column the piece is in
				piecesArr[col][row].setPosition(col * 64, row * 64);
			}
		}
	}
}

/*
* gets all of the possible moves of the color provided
*/
std::vector<int> Pieces::getAllMoves(std::string color)
{
	// creates the output vector
	std::vector<int> output{};

	// loops through the board
	for (int i{ 0 }; i < 64; i++)
	{
		// if there is a piece there
		std::cout << i << " " << bPiecesData[color == "white" ? 13 : 12][i] << std::endl;
		if (bPiecesData[color == "white" ? 13 : 12][i] == 1)
		{
			// gets the possible moves and add them to the output
			std::vector<int> possibleMoves = getPossibleMoves(i, true);
			output.insert(output.end(), possibleMoves.begin(), possibleMoves.end());
		}
	}

	// returns the output
	return output;
}

/**
 * draws the pieces using window.draw
 * @param window takes in the window as a reference to use in the display process
 */
void Pieces::displayPieces(sf::RenderWindow& window)
{
	// loops through the columns
	for (int i{ 0 }; i < 8; i++)
	{
		// loops through the rows
		for (int j{ 0 }; j < 8; j++)
		{
			// draws the sprite
			window.draw(piecesArr[i][j].getSprite());
		}
	}
}
