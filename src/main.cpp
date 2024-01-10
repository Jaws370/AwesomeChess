#include "./board/Board.hpp"
#include "./piece/Piece.hpp"
#include "./pieces/Pieces.hpp"
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

	USER INPUT: (create new class?)
	allow for the chess pieces to be dragged and point-and-click
	allow for resizing of the window

	CODE:
	needs to be better optimized (learn how to use heap for memory management, and use the stack for the pieces) <- bro ai just suggested i do that, idek what the crap that means

DONE STUFF:
	checking and movement for the king

*/

int main()
{
	Board board;
	Pieces pieces;

	std::pair<int, int> moves{ -1, -1 };
	std::vector<int> possibleMoves{};

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
				sf::Vector2i position = sf::Mouse::getPosition(window);
				int col{};
				int row{};

				// saves the column that the mouse clicks to a variable column
				for (int i{ 1 }; i <= 8; i++)
				{
					if (position.x <= 64 * i)
					{
						col = --i;
						break;
					}
				}

				// saves the row that the mouse clicks to a variable row
				for (int i{ 1 }; i <= 8; i++)
				{
					if (position.y <= 64 * i)
					{
						row = --i;
						break;
					}
				}

				if (moves.first == -1)
				{
					std::cout << "move 1" << std::endl;
					moves.first = pieces.toInt(col, row);
					possibleMoves = pieces.getPossibleMoves(pieces.toInt(col, row));
				}
				else
				{
					std::cout << "move 2" << std::endl;
					moves.second = pieces.toInt(col, row);
					if (std::find(possibleMoves.begin(), possibleMoves.end(), moves.second) != possibleMoves.end())
					{
						pieces.movePiece(moves.first, moves.second);
						pieces.updateBoard();
					}
					moves = { -1, -1 };
				}
			}

			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			// need to add code to change board in case of resizing and change position of pieces
		}

		// clear the window with a black color
		window.clear(sf::Color::Black);

		// draw all of the parts of the game
		board.displayBoard(window);
		pieces.displayPieces(window);

		// display the window contents on screen
		window.display();
	}

	return 0;
}
