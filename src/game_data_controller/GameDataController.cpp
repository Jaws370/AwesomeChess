#include "GameDataController.hpp"

GameDataController::GameDataController()
{
    // add all of the pieces to pieces
    for (int i{0}; i < 32; i++) {
        pieces.push_back(std::make_unique<Bishop>(i >= 16 ? i + 32 : i));
    }
}

void GameDataController::handleLeftClick(const sf::Vector2i &mousePosition)
{
    int col{};
    int row{};

    // saves the column that the mouse clicks to a variable column
    for (int i{1}; i <= 8; i++) {
        if (mousePosition.x <= 64 * i) {
            col = --i;
            break;
        }
    }

    // saves the row that the mouse clicks to a variable row
    for (int i{1}; i <= 8; i++)
        if (mousePosition.y <= 64 * i) {
            row = --i;
            break;
        }

    if (moves.first == -1) {
        // TODO readd move stuff later
    } else {
        // TODO readd move stuff later
    }
}

// need to change the pieces to be the correct size
// also need to make sure that the window will change to always be the correct
// shape (square for now)
void GameDataController::handleWindowResize(sf::RenderWindow &window, Board &board)
{
    std::cout << window.getSize().x << std::endl;
    int newSize = std::min(window.getSize().x, window.getSize().y);
    board.setSize(newSize);
    // TODO readd resizing later pieces.resize(newSize / 8.f);
}

void GameDataController::displayPieces(sf::RenderWindow &window)
{
    for (auto &piece : pieces) {
        window.draw(piece->getSprite());
    }
}