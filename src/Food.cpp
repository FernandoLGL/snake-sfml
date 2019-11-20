#include "Food.h"
#include <cstdlib>

Food::Food(const float &x, const float &y, const float &size, const sf::Color &color)
    : sf::RectangleShape(sf::Vector2f(size,size))
{
    this->setPosition(x, y);
    this->setFillColor(color);
}

void Food::spawn(){
    std::srand(std::time(NULL));
    int randomNumber = std::rand();
    int randomX = (((randomNumber % windowWidth) > windowWidth/2) ? ((randomNumber % windowWidth) - 2*borderSize) : ((randomNumber % windowWidth) + 2*borderSize));
    randomNumber = std::rand();
    int randomY = (((randomNumber % windowHeight) > windowHeight/2) ? ((randomNumber % windowHeight) - 2*borderSize) : ((randomNumber % windowHeight) + 2*borderSize));
    this->setPosition(randomX, randomY);
}
