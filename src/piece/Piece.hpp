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
  void setTexture(const std::string &color, const std::string &type);
  sf::Sprite getSprite();
  void setPosition(int x, int y);
};

#endif
