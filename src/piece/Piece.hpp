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
  Piece(std::string color, std::string type);
  sf::Sprite getSprite();
};

#endif
