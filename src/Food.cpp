#include "Food.h"

Food::Food(const float &x, const float &y, const float &size, const sf::Color &color)
    : sf::RectangleShape(sf::Vector2f(size,size))
{
    this->setPosition(x, y);
    this->setFillColor(color);
}
