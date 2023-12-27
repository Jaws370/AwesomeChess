#include <SFML/Graphics.hpp>
#include "./board/Board.hpp"
#include "./pieces/Pieces.hpp"
#include "./piece/Piece.hpp"
/*
  To do list:
    figure out how to make the pieces move
    figure out how to make the pieces take other pieces
*/
int main()
{

  Board board;
  sf::RectangleShape(*boards)[8]{board.getRectangle()};
  Pieces pieces;
  Piece(*p)[8]{pieces.getPieces()};

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
            column = i;
          }
        }

        // saves the row that the mouse clicks to a variable row
        for (int i{1}; i <= 8; i++)
        {
          if (position.y <= 64 * i)
          {
            row = i;
          }
        }
      }

      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
      // need to add code to change board in case of resizing and change position of pieces
    }

    // clear the window with a black color
    window.clear(sf::Color::Black);

    for (int i{0}; i < 8; i++)
    {
      for (int j{0}; j < 8; j++)
      {
        window.draw(boards[i][j]);
      }
    }

    for (int i{0}; i < 8; i++)
    {
      for (int j{0}; j < 8; j++)
      {
        window.draw(p[i][j].getSprite());
      }
    }

    // display the window contents on screen
    window.display();
  }

  return 0;
}
