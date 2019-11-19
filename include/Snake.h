#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Snake{
    // size of each snake body(including the head) square
    const float mSizeOfSquare;
    sf::RectangleShape mHead;
    sf::Color mHeadColor;
    sf::Color mBodyColor;
    std::vector<sf::RectangleShape> mBody;
    Direction direction;
    float mX, mY;

public:
    // operator++ should add another square to the body
    // This is only the postfix increment, since it takes an int as an argument
    Snake operator++(int dummy);

    const sf::RectangleShape& getHead() const{
        return mHead;
    }

    const std::vector<sf::RectangleShape>& getBody() const{
        return mBody;
    }

    void draw(sf::RenderWindow& window) const;

public:
    Snake(const float& x, const float& y, const float sizeOfSquare = 10.f, const sf::Color& headColor = sf::Color::Red, const sf::Color& bodyColor = sf::Color::Green);
};

#endif
