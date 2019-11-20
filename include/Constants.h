#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "SFML/Graphics.hpp"

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;
constexpr int borderSize = 10;
const sf::Color borderColor = sf::Color::White;

enum class Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

#endif
