#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Constants.h"

struct Food : public sf::RectangleShape{

    Food(const float& x, const float& y, const float& size = blockSize, const sf::Color& color = sf::Color::Cyan);
};

#endif
