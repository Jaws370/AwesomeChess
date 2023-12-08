#include "board.hpp"

Board::Board() 
{
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      bool color = (i + j) % 2 == 0;
      rectangle[i][j].setSize(sf::Vector2f(40.f, 40.f));
      rectangle[i][j].setPosition(i * 40.f, j * 40.f);
      if (color) {
        rectangle[i][j].setFillColor(sf::Color(118,150,86));
      }
      else
      {
        rectangle[i][j].setFillColor(sf::Color(238,238,210));
      }
    }
  }
}

sf::RectangleShape (*Board::getRectangle())[8]
{
  return rectangle;
}