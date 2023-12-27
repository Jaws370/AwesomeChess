#include "Piece.hpp"

void Piece::setTexture(const std::string &color, const std::string &type)
{
  this->color = color;
  this->type = type;

  // has to be ../../assets/image for jack and assets/image for tyler
  if (!image.loadFromFile("../../assets/image/" + color + "_" + type + ".png"))
    std::cerr << std::endl;

  displayPiece.setTexture(image);
}

sf::Sprite Piece::getSprite()
{
  return displayPiece;
}

void Piece::setPosition(int x, int y)
{
  displayPiece.setPosition(x, y);
}
