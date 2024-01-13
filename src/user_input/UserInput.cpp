#include "UserInput.hpp"

void UserInput::handleLeftClick(const sf::Vector2i& mousePosition, Pieces& pieces)
{
	int col{};
	int row{};

	// saves the column that the mouse clicks to a variable column
	for (int i{ 1 }; i <= 8; i++)
	{
		if (mousePosition.x <= 64 * i)
		{
			col = --i;
			break;
		}
	}

	// saves the row that the mouse clicks to a variable row
	for (int i{ 1 }; i <= 8; i++)
		if (mousePosition.y <= 64 * i)
		{
			row = --i;
			break;
		}

	if (moves.first == -1)
	{
		std::cout << "move 1" << std::endl;
		moves.first = Pieces::toInt(col, row);
		possibleMoves = pieces.getPossibleMoves(Pieces::toInt(col, row));
	}
	else
	{
		std::cout << "move 2" << std::endl;
		moves.second = Pieces::toInt(col, row);
		if (std::find(possibleMoves.begin(), possibleMoves.end(), moves.second) != possibleMoves.end())
		{
			pieces.movePiece(moves.first, moves.second);
			pieces.updateBoard();
		}
		moves = { -1, -1 };
	}
}

// need to change the pieces to be the correct size
// also need to make sure that the window will change to always be the correct shape (square for now)

void UserInput::handleWindowResize(sf::RenderWindow& window, Board& board)
{
	std::cout << window.getSize().x << std::endl;
	int newSize = std::min(window.getSize().x, window.getSize().y);
	board.setSize(newSize);
}
