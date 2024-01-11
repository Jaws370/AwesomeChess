#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
private:
  int boardSize{}; // <- defaults to 512 at start of game
  sf::RectangleShape rectArr[8][8];

public:
  Board();
  void displayBoard(sf::RenderWindow &window);
  void setSize(const int& boardSize);
  sf::RectangleShape (*getRectangle())[8];
};

#endif
