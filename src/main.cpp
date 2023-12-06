#include <SFML/Graphics.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "awesomechess");

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
        }

        // Clear the window with a black color
        window.clear(sf::Color::Black);

       // Display the window contents on screen
       window.display();
       
   }

    return 0;
}
