#include "Food.h"

Food::Food(const float &x, const float &y, sf::RenderWindow &window, const float &size, const bool &eatable, const sf::Color &color)
    : mX(x), mY(y), mEatable(eatable), mSize(size), mColor(color)
{

}
