#include "UserInput.hpp"

void UserInput::handleLeftClick(const sf::Vector2i &mousePosition, Pieces &pieces)
{
    int col{};
    int row{};

    // saves the column that the mouse clicks to a variable column
    for (int i{1}; i <= 8; i++)
    {
        if (mousePosition.x <= 64 * i)
        {
            col = --i;
            break;
        }
    }

    // saves the row that the mouse clicks to a variable row
    for (int i{1}; i <= 8; i++)
        if (mousePosition.y <= 64 * i)
        {
            row = --i;
            break;
        }

    if (moves.first == -1)
    {
        moves.first   = Pieces::toInt(col, row);
        possibleMoves = pieces.getPossibleMoves(Pieces::toInt(col, row));
        if (possibleMoves.size() == 0)
        {
            moves = {-1, -1};
        }
    }
    else
    {
        moves.second = Pieces::toInt(col, row);
        auto output  = std::find_if(possibleMoves.begin(), possibleMoves.end(), [this](const std::pair<int, std::vector<int>> &pair) { return pair.first == this->moves.second; });
        if (output != possibleMoves.end())
        {
            if (output->second.size() == 2)
            {
                std::vector<int> tempVec = {output->second[0], output->second[1]};
                pieces.movePiece(moves.first, moves.second, tempVec);
            }
            else if (output->second.size() == 1)
            {
                std::vector<int> tempVec = {output->second[0]};
                pieces.movePiece(moves.first, moves.second, tempVec);
            }
            else
            {
                std::vector<int> tempVec;
                pieces.movePiece(moves.first, moves.second, tempVec);
            }
        }
        moves = {-1, -1};
    }
}

// need to change the pieces to be the correct size
// also need to make sure that the window will change to always be the correct
// shape (square for now)
void UserInput::handleWindowResize(sf::RenderWindow &window, Board &board, Pieces &pieces)
{
    std::cout << window.getSize().x << std::endl;
    int newSize = std::min(window.getSize().x, window.getSize().y);
    board.setSize(newSize);
    pieces.resize(newSize / 8.f);
}
