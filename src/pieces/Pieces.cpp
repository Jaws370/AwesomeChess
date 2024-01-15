#include "Pieces.hpp"

/**
 * creates the boards for the pieces (bit-strings)
 * and sets all pieces for starting game (textures and such) accordingly
 */
Pieces::Pieces()
{
	// set the bit-set (i.e. boards) for the game
	bPiecesData[0] = std::bitset<64>("0000000000000000000000000000000000000000000000001111111100000000");  // black pawn
	bPiecesData[1] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000000100100");  // black bishop
	bPiecesData[2] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000001000010");  // black knight
	bPiecesData[3] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000010000001");  // black rook
	bPiecesData[4] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000000001000");  // black queen
	bPiecesData[5] = std::bitset<64>("0000000000000000000000000000000000000000000000000000000000010000");  // black king
	bPiecesData[6] = std::bitset<64>("0000000011111111000000000000000000000000000000000000000000000000");  // white pawn
	bPiecesData[7] = std::bitset<64>("0010010000000000000000000000000000000000000000000000000000000000");  // white bishop
	bPiecesData[8] = std::bitset<64>("0100001000000000000000000000000000000000000000000000000000000000");  // white knight
	bPiecesData[9] = std::bitset<64>("1000000100000000000000000000000000000000000000000000000000000000");  // white rook
	bPiecesData[10] = std::bitset<64>("0000100000000000000000000000000000000000000000000000000000000000"); // white queen
	bPiecesData[11] = std::bitset<64>("0001000000000000000000000000000000000000000000000000000000000000"); // white king
	bPiecesData[12] = std::bitset<64>("0000000000000000000000000000000000000000000000001111111111111111"); // all black pieces
	bPiecesData[13] = std::bitset<64>("1111111111111111000000000000000000000000000000000000000000000000"); // all white pieces

	updateBoard();
}

/**
 * takes the column and the row and returns an int (0-63)
 * of that position on the board
 * @param col the column
 * @param row the row
 * @returns an int (0-63) representing positioning on the board
 */
int Pieces::toInt(const int& col, const int& row)
{
	return (row * 8) + col;
}

std::pair<int, int> Pieces::toColRow(const int& pos)
{
	return { pos % 8, pos / 8 };
}

std::vector<std::pair<int, std::vector<int>>> Pieces::getPawnMoves(const int& pos)
{
	int col, row;
	std::tie(col, row) = toColRow(pos);

	const std::string color{ piecesArr[col][row].getColor() };
	std::vector<std::pair<int, std::vector<int>>> output{};

	// needs to move up the board if white (neg row)
	if (color == "white")
	{
		// check if it can move one space forward
		if ((bPiecesData[12] | bPiecesData[13])[toInt(col, row - 1)] == 0)
		{
			output.push_back({ toInt(col, row - 1), std::vector<int>{} });

			// check if it can move two spaces forward
			if ((bPiecesData[12] | bPiecesData[13])[toInt(col, row - 2)] == 0 && row == 6)
			{
				output.push_back({ toInt(col, row - 2), std::vector<int>{} });
			}
		}

		// check if it can capture diagonally
		if ((bPiecesData[12])[toInt(col - 1, row - 1)] == 1)
		{
			output.push_back({ toInt(col - 1, row - 1), std::vector<int>{} });
		}
		if (bPiecesData[12][toInt(col + 1, row - 1)] == 1)
		{
			output.push_back({ toInt(col + 1, row - 1), std::vector<int>{} });
		}
	}
	// needs to move down the board if black (pos row)
	else
	{
		// check if it can move one space forward
		if ((bPiecesData[12] | bPiecesData[13])[toInt(col, row + 1)] == 0)
		{
			output.push_back({ toInt(col, row + 1), std::vector<int>{} });

			// check if it can move two spaces forward
			if ((bPiecesData[12] | bPiecesData[13])[toInt(col, row + 2)] == 0 && row == 1)
			{
				output.push_back({ toInt(col, row + 2), std::vector<int>{} });
			}
		}

		// check if it can capture diagonally
		if (bPiecesData[13][toInt(col - 1, row + 1)] == 1)
		{
			output.push_back({ toInt(col - 1, row + 1), std::vector<int>{} });
		}
		if (bPiecesData[13][toInt(col + 1, row + 1)] == 1)
		{
			output.push_back({ toInt(col + 1, row + 1), std::vector<int>{} });
		}
	}

	//en passant
	if (!allLastMoves.empty())
	{
		int lastMove = allLastMoves.back();
		int secondToLastMove = allLastMoves[allLastMoves.size() - 2];

		int lastMoveCol = lastMove % 8;
		int lastMoveRow = lastMove / 8;

		if (color == "white")
		{
			bool wasDoubleMove = lastMove - secondToLastMove == 16;
			if (lastMoveRow == 3 && row == 3 && wasDoubleMove)
			{
				if (bPiecesData[0][toInt(col - 1, row)] == 1) {
					output.push_back({ toInt(lastMoveCol, 2), std::vector<int>{toInt(col - 1, row)} });
				}
				else if (bPiecesData[0][toInt(col + 1, row)] == 1)
				{
					output.push_back({ toInt(lastMoveCol, 2), std::vector<int>{toInt(col + 1, row)} });
				}
			}
		}
		// black pawn
		else
		{
			bool wasDoubleMove = lastMove - secondToLastMove == -16;
			if (lastMoveRow == 4 && row == 4 && wasDoubleMove)
			{
				if (bPiecesData[6][toInt(col - 1, row)] == 1) {
					output.push_back({ toInt(lastMoveCol, 5), std::vector<int>{toInt(col - 1, row)} });
				}
				else if (bPiecesData[6][toInt(col + 1, row)] == 1)
				{
					output.push_back({ toInt(lastMoveCol, 5), std::vector<int>{toInt(col + 1, row)} });
				}
			}
		}
	}

	return output;
}

std::vector<std::pair<int, std::vector<int>>> Pieces::getBishopMoves(const int& pos)
{
	int col, row;
	std::tie(col, row) = toColRow(pos);

	const std::string color{ piecesArr[col][row].getColor() };
	std::vector<std::pair<int, std::vector<int>>> output{};

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
			output.push_back({ toInt(newCol, newRow), std::vector<int>{} });

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

	return output;
}

std::vector<std::pair<int, std::vector<int>>> Pieces::getKnightMoves(const int& pos)
{
	int col, row;
	std::tie(col, row) = toColRow(pos);

	const std::string color{ piecesArr[col][row].getColor() };
	std::vector<std::pair<int, std::vector<int>>> output{};

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
			output.push_back({ toInt(newCol, newRow), std::vector<int>{} });
		}
	}

	return output;
}

std::vector<std::pair<int, std::vector<int>>> Pieces::getRookMoves(const int& pos)
{
	int col, row;
	std::tie(col, row) = toColRow(pos);

	const std::string color{ piecesArr[col][row].getColor() };
	std::vector<std::pair<int, std::vector<int>>> output{};

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
			output.push_back({ toInt(newCol, newRow), std::vector<int>{} });

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

	return output;
}

std::vector<std::pair<int, std::vector<int>>> Pieces::getQueenMoves(const int& pos)
{
	int col, row;
	std::tie(col, row) = toColRow(pos);

	const std::string color{ piecesArr[col][row].getColor() };
	std::vector<std::pair<int, std::vector<int>>> output{};

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
			output.push_back({ toInt(newCol, newRow), std::vector<int>{} });

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

	return output;
}

std::vector<std::pair<int, std::vector<int>>> Pieces::getKingMoves(const int& pos, const bool& checkingKing)
{
	int col, row;
	std::tie(col, row) = toColRow(pos);

	const std::string color{ piecesArr[col][row].getColor() };
	std::vector<std::pair<int, std::vector<int>>> output{};

	std::vector<std::pair<int, std::vector<int>>> tempOutput{};

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
			tempOutput.push_back({ toInt(newCol, newRow), std::vector<int>{} });
		}
	}

	// if not checking for all the possible opponents moves
	if (!checkingKing)
	{
		bool hasMoved{ false };

		// castling
		std::vector<int> opponentsMoves{ getAllMoves(color == "white" ? "black" : "white") };

		// make something to store spaces that need to be checked and move that will result
		std::vector<std::tuple<std::vector<int>, int, std::vector<int>>> instructions{};
		if (color == "white")
		{
			instructions.push_back({ {61, 62}, 62 , {63, 61} });
			instructions.push_back({ { 57, 58, 59 }, 58, {56, 59} });
		}
		else
		{
			instructions.push_back({ { 5, 6 } , 6, {7, 5} });
			instructions.push_back({ { 1, 2, 3 }, 2, {0, 3} });
		}

		for (auto& instruction : instructions)
		{
			if (!hasMoved
				&& !((bPiecesData[12] | bPiecesData[13])[toInt(col + 1, row)])
				&& !((bPiecesData[12] | bPiecesData[13])[toInt(col + 2, row)])
				&& std::get<0>(instruction).size() == 2)
			{
				// vector for duplicate checking
				std::vector<int> duplicates{};

				// sort them for set_intersection
				std::sort(opponentsMoves.begin(), opponentsMoves.end());

				// make sure opponentsMoves is not empty
				if (!opponentsMoves.empty())
				{
					// find any duplicates
					std::set_intersection(std::get<0>(instruction).begin(), std::get<0>(instruction).end(), opponentsMoves.begin(), opponentsMoves.end(), std::back_inserter(duplicates));
				}

				// if there are no duplicates
				if (duplicates.empty())
				{
					tempOutput.push_back({ std::get<1>(instruction), std::get<2>(instruction) });
				}
			}
			else if (!hasMoved
				&& !((bPiecesData[12] | bPiecesData[13])[toInt(col - 1, row)])
				&& !((bPiecesData[12] | bPiecesData[13])[toInt(col - 2, row)])
				&& !((bPiecesData[12] | bPiecesData[13])[toInt(col - 3, row)])
				&& std::get<0>(instruction).size() == 3)
			{
				// vector for duplicate checking
				std::vector<int> duplicates{};

				// sort them for set_intersection
				std::sort(opponentsMoves.begin(), opponentsMoves.end());

				// make sure opponentsMoves is not empty
				if (!opponentsMoves.empty())
				{
					// find any duplicates
					std::set_intersection(std::get<0>(instruction).begin(), std::get<0>(instruction).end(), opponentsMoves.begin(), opponentsMoves.end(), std::back_inserter(duplicates));
				}

				// if there are no duplicates
				if (duplicates.empty())
				{
					tempOutput.push_back({ std::get<1>(instruction), std::get<2>(instruction) });
				}
			}
		}

		// finds out if a space would be under check
		std::vector<int> checkSpaces1{ getAllMoves(color == "white" ? "black" : "white") };

		// removes all moves that are in check
		for (int i{ 0 }; i < tempOutput.size(); i++)
		{
			// if not in check
			if (std::find(checkSpaces1.begin(), checkSpaces1.end(), tempOutput[i].first) == checkSpaces1.end())
			{
				output.push_back(tempOutput[i]);
			}
		}
	}

	return output;
}

/**
 * takes the position and finds all possible moves for it
 * @param pos1 move to check
 * @param checkingKing true if running while checking king (default value is false)
 * @returns an array of integers (0-63) representing possible moves
 */
std::vector<std::pair<int, std::vector<int>>> Pieces::getPossibleMoves(const int& pos, bool checkingKing)
{
	int col, row;
	std::tie(col, row) = toColRow(pos);

	// gets the type and color of the piece
	Piece::PieceType type{ piecesArr[col][row].getType() };

	// creates the output vector
	std::vector<std::pair<int, std::vector<int>>> output{};

	switch (type)
	{
	case Piece::PAWN:
		output = getPawnMoves(pos);
		break;
	case Piece::BISHOP:
		output = getBishopMoves(pos);
		break;
	case Piece::KNIGHT:
		output = getKnightMoves(pos);
		break;
	case Piece::ROOK:
		output = getRookMoves(pos);
		break;
	case Piece::QUEEN:
		output = getQueenMoves(pos);
		break;
	case Piece::KING:
		output = getKingMoves(pos, checkingKing);
		break;
	default:
		break;
	}

	for (auto& move : output)
	{
		std::cout << move.first << std::endl;
	}

	return output;
}

/**
 * changes the bit-sets that represent the board
 * @param pos1 takes in the old position
 * @param pos2 takes in new position
 */
void Pieces::movePiece(int& pos1, int& pos2, std::vector<int>& additionalMoves)
{
	// create a bit value representing each of the pieces we are moving
	std::bitset<64> bPos1{ "0000000000000000000000000000000000000000000000000000000000000001" };
	bPos1 = bPos1 << pos1;

	std::bitset<64> bPos2{ "0000000000000000000000000000000000000000000000000000000000000001" };
	bPos2 = bPos2 << pos2;

	// move its own piece
	std::string color{ piecesArr[pos1 % 8][pos1 / 8].getColor() };
	Piece::PieceType type{ piecesArr[pos1 % 8][pos1 / 8].getType() };

	int board{ static_cast<int>(type) };
	board += color == "white" ? 6 : 0;

	bPiecesData[board] = bPiecesData[board] ^ bPos1;
	bPiecesData[board] = bPiecesData[board] | bPos2;

	// update the piecesData for its own color
	bPiecesData[color == "white" ? 13 : 12] = bPiecesData[color == "white" ? 13 : 12] ^ bPos1;
	bPiecesData[color == "white" ? 13 : 12] = bPiecesData[color == "white" ? 13 : 12] | bPos2;

	// adds previous moves to allLastMoves
	allLastMoves.push_back(pos1);
	allLastMoves.push_back(pos2);

	std::bitset<64> bPos3;
	std::bitset<64> bPos4;

	switch (additionalMoves.size())
	{
	case 1:
		// en passant
		color = piecesArr[additionalMoves[0] % 8][additionalMoves[0] / 8].getColor();
		type = piecesArr[additionalMoves[0] % 8][additionalMoves[0] / 8].getType();

		bPos3 = std::bitset<64>("0000000000000000000000000000000000000000000000000000000000000001");
		bPos3 = bPos3 << additionalMoves[0];

		board = static_cast<int>(type);
		board += color == "white" ? 6 : 0;

		bPiecesData[board] = bPiecesData[board] ^ bPos3;

		bPiecesData[color == "white" ? 13 : 12] = bPiecesData[color == "white" ? 13 : 12] ^ bPos3;
		break;
	case 2:
		// castling
		color = piecesArr[additionalMoves[0] % 8][additionalMoves[0] / 8].getColor();
		type = piecesArr[additionalMoves[0] % 8][additionalMoves[0] / 8].getType();

		bPos3 = std::bitset<64>("0000000000000000000000000000000000000000000000000000000000000001");
		bPos3 = bPos3 << additionalMoves[0];

		bPos4 = std::bitset<64>("0000000000000000000000000000000000000000000000000000000000000001");
		bPos4 = bPos4 << additionalMoves[1];

		board = static_cast<int>(type);
		board += color == "white" ? 6 : 0;

		bPiecesData[board] = bPiecesData[board] ^ bPos3;
		bPiecesData[board] = bPiecesData[board] | bPos4;

		bPiecesData[color == "white" ? 13 : 12] = bPiecesData[color == "white" ? 13 : 12] ^ bPos3;
		bPiecesData[color == "white" ? 13 : 12] = bPiecesData[color == "white" ? 13 : 12] | bPos4;
		break;
	default:
		// take out piece if it is taking a piece
		color = piecesArr[pos2 % 8][pos2 / 8].getColor();
		type = piecesArr[pos2 % 8][pos2 / 8].getType();

		if (type == Piece::NO_PIECE)
		{
			updateBoard();
			return;
		}

		board = static_cast<int>(type);
		board += color == "white" ? 6 : 0;

		bPiecesData[board] = bPiecesData[board] ^ bPos2;

		bPiecesData[color == "white" ? 13 : 12] = bPiecesData[color == "white" ? 13 : 12] ^ bPos2;
		break;
	}

	// update board
	updateBoard();
}

/**
 * re-uploads data to the piecesArr
 */
void Pieces::updateBoard()
{
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
			const int col = j % 8;
			const int row = j / 8;

			// if there is a piece there (else there should be no type)
			if (bPiecesData[i][j] == 1)
			{
				// sets the type of the Piece based on whether the array its going through is < 6
				// and sets pieceTypes based off of which array it is going through
				Piece::PieceType type{ static_cast<Piece::PieceType>(i % 6) };
				piecesArr[col][row].setType(i < 6 ? "black" : "white", type);
				// sets position based on row and column the piece is in
				piecesArr[col][row].setPosition((col * spaceSize) - 1, (row * spaceSize) - 1);
				// updates the scale
				piecesArr[col][row].setScale(spaceScale, spaceScale);
			}
		}
	}
}

/*
* gets all of the possible moves of the color provided
* @param color takes in color of the pieces you want the moves for
*/
std::vector<int> Pieces::getAllMoves(std::string color)
{
	// creates the output vector
	std::vector<int> output{};

	// loops through the board
	for (int i{ 0 }; i < 64; i++)
	{
		// if there is a piece there
		if (bPiecesData[color == "white" ? 13 : 12][i] == 1)
		{
			// gets the possible moves and add them to the output
			std::vector<int> possibleMoves{};
			std::vector<std::pair<int, std::vector<int>>> moves = getPossibleMoves(i, true);
			for (const auto& move : moves) {
				possibleMoves.push_back(move.first);
			}
			output.insert(output.end(), possibleMoves.begin(), possibleMoves.end());
		}
	}

	// returns the output
	return output;
}

/**
* @param spaceSize
* resizes the pieces and sets scale
*/
void Pieces::resize(const float& spaceSize)
{
	this->spaceSize = spaceSize;
	this->spaceScale = spaceSize / 64.f;
	updateBoard();
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
