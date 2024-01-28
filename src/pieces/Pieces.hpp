#ifndef PIECES_HPP
#define PIECES_HPP

#include "../piece_types/shared/Piece.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Pieces
{
public:
    Piece *getPiece(int pos);

    void updatePieces();
    void displayPieces(sf::Window &window);

private:
    std::vector<Piece> pieces;
};

#endif
