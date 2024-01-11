#include "./board/Board.hpp"
#include "./piece/Piece.hpp"
#include "./pieces/Pieces.hpp"
#include "./user_input/UserInput.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

/*

TODO List:
	PIECE MOVEMENT: (ez pz)
	bug-fix and test castling
	add en passant
	add computer to play against

	AUDIO: (can be done in pieces.cpp, but need to import audio from sfml)
	add sounds for actions such as pieces moving, king being in check, etc.

	DISPLAY: (need new classes fo sho)
	add a main menu screen with a start button, and a screen that plays after someone wins, which displays who won and who lost, as well as a replay button
	add a counter that counts the material lost and gained for each player, as well as an icon of the pieces lost, just like chess.com
	make the pieces move instead of teleport
	add a hud for player 1 and player 2
	add dots to each square where the piece can move and for the king, make the dots red where he can't go
	add a circle around pieces that could be captured when a piece is selected
	letters and numbers on the edge of the board, labeled 1-8 on the left column and a-h on the bottom row
	when a piece moves to a new square, make the old position and new position a lighter green if it is on a green square, and slightly yellow if on a white square

	USER INPUT:
	allow for the chess pieces to be dragged and point-and-click
	allow for resizing of the window

	CODE:
	optimize functions to be smaller and faster while still being very understandable
	needs to be better optimized (learn how to use heap for memory management, and use the stack for the pieces) <- bro ai just suggested i do that, idek what the crap that means
		*NOTE:
			stack is memory that works fast, but is limited in size. You want small local vars to be on it (will destroy when out of scope).
			(used whenever you create a var)
		*NOTE:
			heap is memory that works slower (still faster than any storage), but is dynamic in size. You want big vars to be on it.
			(created with new keyword or smart pointers [smart pointers are better because they will destroy at certain points that you don't have to make])
			harder to use because you need to deallocate memory

DONE STUFF:
	checking and movement for the king
	added user input class

*/

int main()
{
	// unique pointers for board and pieces (allocates memory on the heap)
	std::unique_ptr board = std::make_unique<Board>();
	std::unique_ptr pieces = std::make_unique<Pieces>();

	UserInput in;

	sf::RenderWindow window(sf::VideoMode(512, 512), "AwesomeChess");

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// check if mouse buttons have been pressed
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					// get the position of the mouse and send it to be handled
					in.handleLeftClick(sf::Mouse::getPosition(window), *pieces);
				}
			}

			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			// TODO need to add code to change board and pieces in case of resizing
		}

		// clear the window with a black color
		window.clear(sf::Color::Black);

		// draw all of the parts of the game
		board->displayBoard(window);
		pieces->displayPieces(window);

		// display the window contents on screen
		window.display();
	}

	return 0;
}
