#include "Game.h"
#include "Constants.h"

Game::Game(){
    // Setting up the borders
    // left border
    mLeftBorder = sf::RectangleShape(sf::Vector2f(borderSize, windowHeight));
    mLeftBorder.setPosition(0,0);
    mLeftBorder.setFillColor(borderColor);
    //right border
    mRightBorder = sf::RectangleShape(sf::Vector2f(borderSize, windowHeight));
    mRightBorder.setPosition(windowWidth-borderSize, 0);
    mRightBorder.setFillColor(borderColor);
    //up border
    mUpBorder = sf::RectangleShape(sf::Vector2f(windowWidth, borderSize));
    mUpBorder.setPosition(0,0);
    mUpBorder.setFillColor(borderColor);
    //down border
    mDownBorder = sf::RectangleShape(sf::Vector2f(windowWidth, borderSize));
    mDownBorder.setPosition(0,windowHeight-borderSize);
    mDownBorder.setFillColor(borderColor);

}

void Game::drawBorders(sf::RenderWindow &window)
{
    // left border
    window.draw(mLeftBorder);
    // right border
    window.draw(mRightBorder);
    // up border
    window.draw(mUpBorder);
    // down border
    window.draw(mDownBorder);
}

void Game::setupScore(sf::Text& scoreText, sf::Font &font, const Snake& snake){
    // Subtracted 4 because that's the defined initial snake size
    scoreText.setString("Score: " + std::to_string(snake.getBodySize() - 4));
    scoreText.setPosition(borderSize + 5, borderSize + 5);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setFont(font);
    scoreText.setStyle(sf::Text::Bold);
}

void Game::setupGameOver(sf::Text& gameOverText, sf::Font &font, const Snake &snake){
    // Subtracting 4 because that's the initial snake's body size
    gameOverText.setString("Game over!\nPress ENTER to quit\nScore: " + std::to_string(snake.getBodySize()-4));
    gameOverText.setPosition(windowWidth/2, windowHeight/2);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setCharacterSize(20);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setFont(font);
}
