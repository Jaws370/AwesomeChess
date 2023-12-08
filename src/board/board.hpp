#ifndef RENDERING_H
#define RENDERING_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
  sf::RectangleShape rectangle[8][8];

public:
  Board();
  sf::RectangleShape (*getRectangle())[8];

};

#endif