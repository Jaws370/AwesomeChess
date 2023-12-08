#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
  
Class Piece 
{
  private:
    sf::Texture image;
    string color{};
    string type{};

  public:
    sf::Sprite displayPiece;
    Piece(string color, string type);
    
    
}

#endif
