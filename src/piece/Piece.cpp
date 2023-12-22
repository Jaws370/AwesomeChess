#include "Piece.hpp"

void Piece::setTexture(std::string color, std::string type)
{
  this->color = color;
  this->type = type;

  // has to be ../../assets/image for vscode and assets/image for replit
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
