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

/**
* converts an int (0-63) into a corresponding pair of { col, row }
*/
std::pair<int, int> Pieces::toColRow(const int& pos)
{
	return { pos % 8, pos / 8 };
}

/**
* takes two vectors and combines them into one (will give error if they are two different types)
*/
template<typename T>
std::vector<T> Pieces::combineVectors(const std::vector<T>& v1, const std::vector<T>& v2)
{
	if (std::is_same<typename std::vector<T>::value_type, typename std::vector<T>::value_type>::value)
	{
		std::vector<T> result;
		result.insert(result.end(), v1.begin(), v1.end());
		result.insert(result.end(), v2.begin(), v2.end());
		return result;
	}
	else
	{
		std::cerr << "incompatible types for combination" << std::endl;
		// You might want to handle the error case here
	}
	return v1;
}


/**
* gets all the moves for a pawn at pos
*/
std::vector<std::pair<int, std::vector<int>>> Pieces::getPawnMoves(const int& col, const int& row, const std::string& color)
{
    constexpr WHITE_MOVES = 13;
    constexpr BLACK_MOVES = 12;

	std::vector<std::pair<int, std::vector<int>>> output{};

	// needs to move up the board if white (neg row)
	if (color == "white")
	{
		// check if it can move one space forward
		if (!(bPiecesData[WHITE_MOVES] | bPiecesData[BLACK_MOVES])[toInt(col, row - 1)])
		{
			output.push_back({ toInt(col, row - 1), std::vector<int>{} });

			// check if it can move two spaces forward
			if (!(bPiecesData[WHITE_MOVES] | bPiecesData[BLACK_MOVES])[toInt(col, row - 2)] && row == 6)
			{
				output.push_back({ toInt(col, row - 2), std::vector<int>{} });
			}
		}

		// check if it can capture diagonally
		if ((bPiecesData[BLACK_MOVES])[toInt(col - 1, row - 1)])
		{
			output.push_back({ toInt(col - 1, row - 1), std::vector<int>{} });
		}
		if (bPiecesData[BLACK_MOVES][toInt(col + 1, row - 1)])
		{
			output.push_back({ toInt(col + 1, row - 1), std::vector<int>{} });
		}
	}
	// needs to move down the board if black (pos row)
	else
	{
		// check if it can move one space forward
		if (!(bPiecesData[WHITE_MOVES] | bPiecesData[BLACK_MOVES])[toInt(col, row + 1)])
		{
			output.push_back({ toInt(col, row + 1), std::vector<int>{} });

			// check if it can move two spaces forward
			if (!(bPiecesData[WHITE_MOVES] | bPiecesData[BLACK_MOVES])[toInt(col, row + 2)] && row == 1)
			{
				output.push_back({ toInt(col, row + 2), std::vector<int>{} });
			}
		}

		// check if it can capture diagonally
		if (bPiecesData[WHITE_MOVES][toInt(col - 1, row + 1)])
		{
			output.push_back({ toInt(col - 1, row + 1), std::vector<int>{} });
		}
		if (bPiecesData[WHITE_MOVES][toInt(col + 1, row + 1)])
		{
			output.push_back({ toInt(col + 1, row + 1), std::vector<int>{} });
		}
	}

	return output;
}

std::vector<std::pair<int, std::vector<int>>> Pieces::getEnPassant(const int& col, const int& row, const std::string& color)
{
    constexpr DOUBLE_MOVE = 16;
    
    constexpr WHITE_PAWN = 6;
    constexpr BLACK_PAWN = 0;

    constexpr DOUBLE_ROW_WHITE = 3;
    constexpr DOUBLE_ROW_BLACK = 4;

    //en passant
	if (!allLastMoves.empty())
	{
		int lastMove = allLastMoves.back();
		int secondToLastMove = allLastMoves[allLastMoves.size() - 2];

		int lastMoveCol = lastMove % 8;
		int lastMoveRow = lastMove / 8;

		if (color == "white")
		{
			bool wasDoubleMove = lastMove - secondToLastMove == DOUBLE_MOVE;
			if (lastMoveRow == DOUBLE_ROW_WHITE && row == DOUBLE_ROW_WHITE && wasDoubleMove)
			{
				if (bPiecesData[WHITE_PAWN][toInt(col - 1, row)]) {
					output.push_back({ toInt(lastMoveCol, 2), std::vector<int>{toInt(col - 1, row)} });
				}
				else if (bPiecesData[WHITE_PAWN][toInt(col + 1, row)])
				{
					output.push_back({ toInt(lastMoveCol, 2), std::vector<int>{toInt(col + 1, row)} });
				}
			}
		}
		// black pawn
		else
		{
			bool wasDoubleMove = lastMove - secondToLastMove == -DOUBLE_MOVE;
			if (lastMoveRow == DOUBLE_ROW_BLACK && row == DOUBLE_ROW_BLACK && wasDoubleMove)
			{
				if (bPiecesData[BLACK_PAWN][toInt(col - 1, row)]) {
					output.push_back({ toInt(lastMoveCol, 5), std::vector<int>{toInt(col - 1, row)} });
				}
				else if (bPiecesData[BLACK_PAWN][toInt(col + 1, row)])
				{
					output.push_back({ toInt(lastMoveCol, 5), std::vector<int>{toInt(col + 1, row)} });
				}
			}
		}
	}
}

/**
* gets all the moves for Bishop, Rook, Queen based on the pos and the directions given
*/
std::vector<std::pair<int, std::vector<int>>> Pieces::getBRQMoves(const int& col, const int& row, const std::string& color, const Piece::PieceType& type)
{
	// get directions
	std::vector<std::pair<int, int>> directions{};
	switch (type)
	{
	case Piece::BISHOP:
		directions = { {1, 1}, {-1, 1}, {-1, -1}, {1, -1} };
		break;
	case Piece::ROOK:
		directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
		break;
	case Piece::QUEEN:
		directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1} };
		break;
	default:
		std::cerr << "ERROR: getBRQMoves() called on wrong type in Pieces.cpp" << std::endl;
		break;
	}

	std::vector<std::pair<int, std::vector<int>>> output{};

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
			if (bPiecesData[color == "black" ? 13 : 12][toInt(newCol, newRow)])
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

/**
* gets the moves for the Knight and King based on directions given
*/
std::vector<std::pair<int, std::vector<int>>> Pieces::getKnKMoves(const int& col, const int& row, const std::string& color, const Piece::PieceType& type)
{
	std::vector<std::pair<int, int>> directions{};
	switch (type)
	{
	case Piece::KNIGHT:
		directions = { {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2} };
		break;
	case Piece::KING:
		directions = { {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1} };
		break;
	default:
		std::cerr << "ERROR wrong type given to getKnKMoves() in Pieces.cpp" << std::endl;
		break;
	}

	std::vector<std::pair<int, std::vector<int>>> output{};

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

/**
* gets the moves for a castling king
*/
std::vector<std::pair<int, std::vector<int>>> Pieces::getKingCastling(const int& pos, const int& col, const int& row, const std::string& color, const Piece::PieceType& type)
{
	bool hasMoved{ false };
	if (std::find(allLastMoves.begin(), allLastMoves.end(), pos) != allLastMoves.end())
	{
		hasMoved = !hasMoved;
	}

	std::vector<std::pair<int, std::vector<int>>> output{};

	// castling
	std::vector<int> opponentsMoves{ getAllMoves(color == "white" ? "black" : "white") };

	// make something to store spaces that need to be checked and move that will result
	std::vector<std::tuple<std::vector<int>, int, std::vector<int>>> instructions{};
	if (color == "white")
	{
		instructions.push_back({ { 60, 61, 62 }, 62 , { 63, 61 } });
		instructions.push_back({ { 57, 58, 59, 60 }, 58, { 56, 59 } });
	}
	else
	{
		instructions.push_back({ { 4, 5, 6 } , 6, { 7, 5 } });
		instructions.push_back({ { 1, 2, 3, 4 }, 2, { 0, 3 } });
	}

	for (auto& instruction : instructions)
	{
		if (!hasMoved
			&& !((bPiecesData[12] | bPiecesData[13])[toInt(col + 1, row)])
			&& !((bPiecesData[12] | bPiecesData[13])[toInt(col + 2, row)])
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
				output.push_back({ std::get<1>(instruction), std::get<2>(instruction) });
			}
		}
		else if (!hasMoved
			&& !((bPiecesData[12] | bPiecesData[13])[toInt(col - 1, row)])
			&& !((bPiecesData[12] | bPiecesData[13])[toInt(col - 2, row)])
			&& !((bPiecesData[12] | bPiecesData[13])[toInt(col - 3, row)])
			&& std::get<0>(instruction).size() == 4)
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
				output.push_back({ std::get<1>(instruction), std::get<2>(instruction) });
			}
		}
	}

	return output;
}

/*
void Pieces::getPromote(){
	if(this.color=="white" &&this.type=="pawn" && row==0){
		whitePromotion();
	}
	else if(this.color=="black" && this.type=="pawn" && row==7){
		blackPromotion();
	}
}

//waits for white to input a number 1-4 to promote their past pawn
void Pieces::whitePromotion(){
	//continue checking
	while(!promoted){
		//checks if 1 is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			//promote pawn to bishop
			bPiecesData[6]toInt(col,row)=0;
			bPiecesData[7]toInt(col,row)=1;
			promoted=true;
		}
		//checks if 2 is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			//promote pawn to knight
			bPiecesData[6]toInt(col,row)=0;
			bPiecesData[8]toInt(col,row)=1;
			promoted=true;
		}
		//checks if 3 is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			//promote pawn to rook
			bPiecesData[6]toInt(col,row)=0;
			bPiecesData[9]toInt(col,row)=1;
			promoted=true;
		}
		//checks if 4 is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			//promote pawn to queen
			bPiecesData[6]toInt(col,row)=0;
			bPiecesData[10]toInt(col,row)=1;
			promoted=true;
		}
	}
}

/*waits for black to input a number 1 - 4 to promote their past pawn
void Pieces::blackPromotion(){
	//continue checking
	while(!promoted){
		//checks if 1 is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			//promote pawn to bishop
			bPiecesData[0]toInt(col,row)=0;
			bPiecesData[1]toInt(col,row)=1;
			promoted=true;
		}
		//checks if 2 is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			//promote pawn to knight
			bPiecesData[0]toInt(col,row)=0;
			bPiecesData[2]toInt(col,row)=1;
			promoted=true;
		}
		//checks if 3 is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			//promote pawn to rook
			bPiecesData[0]toInt(col,row)=0;
			bPiecesData[3]toInt(col,row)=1;
			promoted=true;
		}
		//checks if 4 is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			//promote pawn to queen
			bPiecesData[0]toInt(col,row)=0;
			bPiecesData[4]toInt(col,row)=1;
			promoted=true;
		}
	}
}*/

/**
* removes any spaces that would be under check from a vector based on the other color's moves
*/
std::vector<std::pair<int, std::vector<int>>> Pieces::removeChecks(const std::string& color, const std::vector<std::pair<int, std::vector<int>>>& tempOutput)
{
	std::vector<std::pair<int, std::vector<int>>> output{};

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

	return output;
}

/**
 * takes the position and finds all possible moves for it
 * @param pos1 move to check
 * @param checkingKing true if running while checking king (default value is false)
 * @returns an array of integers (0-63) representing possible moves
 */
std::vector<std::pair<int, std::vector<int>>> Pieces::getPossibleMoves(const int& pos, const bool& checkingKing)
{
	int col, row;
	std::tie(col, row) = toColRow(pos);

	// gets the type and color of the piece
	const std::string color{ piecesArr[col][row].getColor() };
	Piece::PieceType type{ piecesArr[col][row].getType() };

	// creates the output vector
	std::vector<std::pair<int, std::vector<int>>> output{};

	switch (type)
	{
	case Piece::PAWN:
		output = getPawnMoves(col, row, color);
		output = Pieces::combineVectors(output, getEnPassant(col, row, color));
		break;
	case Piece::BISHOP:
		output = getBRQMoves(col, row, color, type);
		break;
	case Piece::KNIGHT:
		output = getKnKMoves(col, row, color, type);
		break;
	case Piece::ROOK:
		output = getBRQMoves(col, row, color, type);
		break;
	case Piece::QUEEN:
		output = getBRQMoves(col, row, color, type);
		break;
	case Piece::KING:
		output = getKnKMoves(col, row, color, type);
		if (!checkingKing)
		{
			output = Pieces::combineVectors(output, getKingCastling(pos, col, row, color, type));
			output = removeChecks(color, output);
		}
		break;
	default:
		break;
	}

	if (!checkingKing)
	{
		std::cout << "\nnew" << std::endl;
		for (auto& move : output)
		{
			std::cout << move.first << std::endl;
		}
	}

	return output;
}

/**
 * changes the bit-sets that represent the board
 * @param pos1 takes in the old position
 * @param pos2 takes in new position
 * @param additionalMoves size(1) = do en passant stuff || size(2) = do castling stuff
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
				piecesArr[col][row].setScale(pieceScale, pieceScale);
			}
		}
	}
}

/**
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
* resizes the pieces and sets scale
* @param spaceSize the size of a space
*/
void Pieces::resize(const float& spaceSize)
{
	this->spaceSize = spaceSize;
	this->pieceScale = spaceSize / 64.f;
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
