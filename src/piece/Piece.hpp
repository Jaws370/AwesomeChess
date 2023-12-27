#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class Piece
{
private:
  sf::Texture image{};
  std::string color{};
  std::string type{};
  sf::Sprite displayPiece{};

public:
  Piece() = default;
  void setType(std::string const &color, std::string const &type);
  sf::Sprite getSprite();
  void setPosition(int const &x, int const &y);
};

#endif
