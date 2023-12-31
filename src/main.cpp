#include <SFML/Graphics.hpp>
#include "./board/Board.hpp"
#include "./pieces/Pieces.hpp"
#include "./piece/Piece.hpp"

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
        int column{};
        int row{};

        // saves the column that the mouse clicks to a variable column
        for (int i{1}; i <= 8; i++)
        {
          if (position.x <= 64 * i)
          {
            column = --i;
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

        std::cout << position.x << " " << position.y << std::endl;
        std::cout << column << " " << row << std::endl;
        std::cout << row * 8 + column << std::endl;
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
