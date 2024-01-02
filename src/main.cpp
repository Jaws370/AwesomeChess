#include <SFML/Graphics.hpp>
#include "./board/Board.hpp"
#include "./pieces/Pieces.hpp"
#include "./piece/Piece.hpp"
#include <iostream>

int main()
{

  Board board;
  Pieces pieces;

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
        for (int i{1}; i <= 8; i++)
        {
          if (position.x <= 64 * i)
          {
            col = --i;
            break;
          }
        }

        // saves the row that the mouse clicks to a variable row
        for (int i{1}; i <= 8; i++)
        {
          if (position.y <= 64 * i)
          {
            row = --i;
            break;
          }
        }

        std::vector<int> possibleMoves = pieces.getPossibleMoves(pieces.toInt(col, row));
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
