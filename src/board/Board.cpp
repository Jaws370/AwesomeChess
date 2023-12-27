#include "Board.hpp"

Board::Board()
{
  for (int i{0}; i < 8; i++)
  {
    for (int j{0}; j < 8; j++)
    {
      bool color{(i + j) % 2 == 0};
      board[i][j].setSize(sf::Vector2f(boardSize / 8.f, boardSize / 8.f));
      board[i][j].setPosition(i * boardSize / 8.f, j * boardSize / 8.f);
      if (color)
      {
        board[i][j].setFillColor(sf::Color(118, 150, 86));
      }
      else
      {
        board[i][j].setFillColor(sf::Color(238, 238, 210));
      }
    }
  }
}

/**
 * draws the rectangles for board using window.draw
 * @param window takes in the window as a reference to use in the display process
 */
void Board::displayBoard(sf::RenderWindow &window)
{
  for (int i{0}; i < 8; i++)
  {
    for (int j{0}; j < 8; j++)
    {
      window.draw(board[i][j]);
    }
  }
}

sf::RectangleShape (*Board::getRectangle())[8]
{
  return board;
}
