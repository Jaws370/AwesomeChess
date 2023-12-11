#include <SFML/Graphics.hpp>
#include "./board/board.hpp"
#include "./piece/Piece.hpp"

int main()
{

  Board board;
  sf::RectangleShape(*boards)[8] = board.getRectangle();

  Piece piece("black", "bishop");
  sf::Sprite p = piece.getSprite();

  sf::RenderWindow window(sf::VideoMode(800, 600), "AwesomeChess");

  // Run the program as long as the window is open
  while (window.isOpen())
  {
    // Check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
      // need to add code to change board in case of resizing and change position of pieces
    }

    // Clear the window with a black color
    window.clear(sf::Color::Black);

    for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
      {
        window.draw(boards[i][j]);
      }
    }

    window.draw(p);

    // Display the window contents on screen
    window.display();
  }

  return 0;
}
