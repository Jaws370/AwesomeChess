#include "Piece.hpp"

Piece::Piece(std::string color, std::string type)
{
  this->color = color;
  this->type = type;
  
  if (!image.loadFromFile("../../assets/images/" + color + type + ".png"))
  {
     std::cerr << "Failed to load image" << std::endl;
  }

  displayPiece.setTexture(image);
}

sf::Sprite Piece::getSprite()
{
  return displayPiece;
}
