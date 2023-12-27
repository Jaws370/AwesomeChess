#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
private:
  int boardSize{512};
  sf::RectangleShape board[8][8];

public:
  Board();
  void displayBoard(sf::RenderWindow &window);
  sf::RectangleShape (*getRectangle())[8];
};

#endif
