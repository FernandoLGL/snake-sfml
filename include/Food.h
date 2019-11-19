#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct Food{
    const float mX;
    const float mY;
    bool mEatable;
    const float mSize;
    sf::Color mColor;

    Food(const float& x, const float& y, sf::RenderWindow& window, const float& size = 10.f, const bool& eatable = 1, const sf::Color& color = sf::Color::Cyan);

private:

    void draw(sf::RenderWindow& window) const;
};

#endif
