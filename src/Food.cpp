#include "Food.h"
#include <cstdlib>

Food::Food(const float &x, const float &y, const float &size, const sf::Color &color)
    : sf::RectangleShape(sf::Vector2f(size,size))
{
    this->setPosition(x, y);
    this->setFillColor(color);
}

void Food::respawn(){
    std::srand(std::time(NULL));
    int randomX = (std::rand() % windowWidth) + 1;
    int randomY = (std::rand() % windowHeight) + 1;
    this->setPosition(randomX, randomY);
}
