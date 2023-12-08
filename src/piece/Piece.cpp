#include "Piece.hpp"

Piece::Piece(string color, string type)
{
  this->color = color;
  this->type = type;
  
  if (!image.loadFromFile("assets/images/" + color + type + ".png"))
  {
     std::cerr << "Failed to load image" << std::endl;
  }

  displayPiece.setTexture(image);
  displayPiece.setSize(sf::Vector2f(40, 40));
}