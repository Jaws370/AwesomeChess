#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
private:
  int boardSize = 512;
  sf::RectangleShape rectangle[8][8];

public:
  Board();
  sf::RectangleShape (*getRectangle())[8];
};

#endif
