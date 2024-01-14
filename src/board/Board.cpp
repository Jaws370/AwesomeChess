#include "Board.hpp"

Board::Board()
{
	setSize(512);

	for (int i{ 0 }; i < 8; i++)
	{
		for (int j{ 0 }; j < 8; j++)
		{
			bool color{ (i + j) % 2 == 0 };
			if (color)
			{
				rectArr[i][j].setFillColor(sf::Color(118, 150, 86));
			}
			else
			{
				rectArr[i][j].setFillColor(sf::Color(238, 238, 210));
			}
		}
	}
}

void Board::setSize(const int& boardSize)
{
	this->boardSize = boardSize;

	for (int i{ 0 }; i < 8; i++)
	{
		for (int j{ 0 }; j < 8; j++)
		{
			rectArr[i][j].setSize(sf::Vector2f(boardSize / 8.f, boardSize / 8.f));
			rectArr[i][j].setPosition(i * boardSize / 8.f, j * boardSize / 8.f);
		}
	}
}

/**
 * draws the rectangles for board using window.draw
 * @param window takes in the window as a reference to use in the display process
 */
void Board::displayBoard(sf::RenderWindow& window)
{
	// calculate the size of each square on the board
	float squareSize = boardSize / 8.f;

	// set the size and position of each rectangle in the rectArr
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			rectArr[i][j].setSize(sf::Vector2f(squareSize, squareSize));
			rectArr[i][j].setPosition(i * squareSize, j * squareSize);
		}
	}

	// draw the board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			window.draw(rectArr[i][j]);
		}
	}
}

sf::RectangleShape(*Board::getRectangle())[8]
	{
		return rectArr;
	}
