#include "Bishop.hpp"

Bishop::Bishop(int position)
{
    setTexture("./assets/images/white_bishop.png");
    setSprite();
    setType(BISHOP);
    setPosition(position);
}
