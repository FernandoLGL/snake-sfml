#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Constants.h"

struct Food : public sf::RectangleShape
{
  Food(const float& x         = 20.f,
       const float& y         = 30.f,
       const float& size      = 10.f,
       const sf::Color& color = sf::Color::Cyan);

  void spawn();
};

#endif
