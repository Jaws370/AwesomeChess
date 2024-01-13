#ifndef USER_INPUT_HPP
#define USER_INPUT_HPP

#include "../pieces/Pieces.hpp"
#include "../board/Board.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

/*
* TODO:
* add resizing of window
* add clicks (eventually right click too)
*/
class UserInput
{
public:
	void handleLeftClick(const sf::Vector2i& mousePosition, Pieces& pieces);
	void handleWindowResize(sf::RenderWindow& window, Board& board);
private:
	std::pair<int, int> moves{ -1, -1 };
	std::vector<int> possibleMoves{};
};

#endif
