#include "./board/Board.hpp"
#include "./pieces/Pieces.hpp"
#include "./user_input/UserInput.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

/*
TODO List:
    PIECE MOVEMENT:
    need to make it so you have to move king if under check
    add computer to play against

    AUDIO: (can be done in pieces.cpp, but need to import audio from sfml)
    add sounds for actions such as pieces moving, king being in check, etc.

    DISPLAY: (need new classes fo sho)
    NEED BETTER SPRITES FOR PIECES: HIGHER QUALITY (need to make sure that the pieces are not distorted)
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

    CODE:
    optimize functions to be smaller and faster while still being very understandable <- change getPossibleMoves to be more functional programming (higher order functions?)
    needs to be better optimized memory wise

    DONE STUFF:
    checking and movement for the king
    added user input class
    added board and pieces to heap to limit stack size
    king now recognizes castling
    en pissant
    rook and pawn movement works for castling and en passant
    window can now resize
    changed the function getPossibleMoves to have multiple functions of get(&piece)Moves for easier replacement
    need to add something to make sure king does not castle while under check
    bugfix promoting to queen, rook, bishop, knight
*/

int main()
{
    // unique pointers for board and pieces (allocates memory on the heap)
    std::unique_ptr board  = std::make_unique<Board>();
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
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);

            switch (event.type)
            {
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        // get the position of the mouse and send it to be handled
                        in.handleLeftClick(sf::Mouse::getPosition(window), *pieces);
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    window.setView(sf::View(visibleArea));
                    in.handleWindowResize(window, *board, *pieces);
                    break;
                default:
                    break;
            }
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
