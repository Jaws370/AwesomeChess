#ifndef USER_INPUT_HPP
#define USER_INPUT_HPP

#include "../board/Board.hpp"
#include "../piece_types/bishop/Bishop.hpp"
#include "../piece_types/piece_base/PieceBase.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

/*
 * TODO:
 * add resizing of window
 * add clicks (eventually right click too)
 * add drag and drop
 */
class GameDataController
{
public:
    // constructor
    GameDataController();

    void handleLeftClick(const sf::Vector2i &mousePosition);
    void handleWindowResize(sf::RenderWindow &window, Board &board);
    void displayPieces(sf::RenderWindow &window);

private:
    std::pair<int, int> moves{-1, -1};
    std::vector<std::pair<int, std::vector<int>>> possibleMoves{};
    std::vector<std::unique_ptr<PieceBase>> pieces{};
};

#endif
