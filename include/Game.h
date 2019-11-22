#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"

class Game{

public:
    Game();
    sf::RectangleShape mLeftBorder;
    sf::RectangleShape mRightBorder;
    sf::RectangleShape mUpBorder;
    sf::RectangleShape mDownBorder;

public:
    void drawBorders(sf::RenderWindow& window);
    void setupScore(sf::Text& scoreText, sf::Font& font, const Snake& snake);
    void setupGameOver(sf::Text& gameOverText, sf::Font& font, const Snake& snake);

};



#endif
