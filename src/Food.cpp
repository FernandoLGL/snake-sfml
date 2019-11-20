#include "Food.h"
#include <cstdlib>

Food::Food(const float &x, const float &y, const float &size, const sf::Color &color)
    : sf::RectangleShape(sf::Vector2f(size,size))
{
    this->setPosition(x, y);
    this->setFillColor(color);
}

void Food::spawn(){
    // Nothing stops the food from spawning in a body part location FOR NOW
    // It also doesn't stop it from spawning on "Score" but I don't plan to stop it from doing that.
    std::srand(std::time(NULL));
    int randomNumber = std::rand();
    int randomX = (((randomNumber % windowWidth) > windowWidth/2) ? ((randomNumber % windowWidth) - 2*borderSize) : ((randomNumber % windowWidth) + 2*borderSize));
    randomNumber = std::rand();
    int randomY = (((randomNumber % windowHeight) > windowHeight/2) ? ((randomNumber % windowHeight) - 2*borderSize) : ((randomNumber % windowHeight) + 2*borderSize));
    this->setPosition(randomX, randomY);
}
