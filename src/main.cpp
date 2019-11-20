#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Constants.h"
#include "Snake.h"
#include "Food.h"

int main() {

    // Game Window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Snake!", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    // Borders
    sf::RectangleShape leftBorder(sf::Vector2f(borderSize, windowHeight));
    leftBorder.setPosition(0,0);
    leftBorder.setFillColor(borderColor);
    sf::RectangleShape rightBorder(sf::Vector2f(borderSize, windowHeight));
    rightBorder.setPosition(windowWidth-borderSize, 0);
    leftBorder.setFillColor(borderColor);
    sf::RectangleShape upBorder(sf::Vector2f(windowWidth, borderSize));
    upBorder.setPosition(0,0);
    upBorder.setFillColor(borderColor);
    sf::RectangleShape downBorder(sf::Vector2f(windowWidth, borderSize));
    downBorder.setPosition(0,windowHeight-borderSize);

    Snake snake(400,300,0.5);
    Food food;
    food.spawn();

    // Game loop
    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        sf::Event event;

        // just testing out Keyboard
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
//            window.close();

        // event pending ?
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){

                switch(event.key.code){
                case sf::Keyboard::Key::A:
                case sf::Keyboard::Key::Left:
                    if(snake.getDirection() == Direction::RIGHT)
                        break;
                    snake.setDirection(Direction::LEFT);
                    break;
                case sf::Keyboard::Key::Right:
                case sf::Keyboard::Key::D:
                    if(snake.getDirection() == Direction::LEFT)
                        break;
                    snake.setDirection(Direction::RIGHT);
                    break;

                case sf::Keyboard::Key::Up:
                case sf::Keyboard::Key::W:
                    if(snake.getDirection() == Direction::DOWN)
                        break;
                    snake.setDirection(Direction::UP);
                    break;
                case sf::Keyboard::Key::S:
                case sf::Keyboard::Key::Down:
                    if(snake.getDirection() == Direction::UP)
                        break;
                    snake.setDirection(Direction::DOWN);
                    break;
                 default:
                    break;
                }
            }
        }

        // For testing spawn points
        // food.spawn();

        // Drawing borders
        window.draw(leftBorder);
        window.draw(rightBorder);
        window.draw(upBorder);
        window.draw(downBorder);

        // if the snake has eaten the food
        if(snake.getHead().getGlobalBounds().intersects(food.getGlobalBounds())){
            snake++;
            food.spawn();
        }

        snake.draw(window);

        // if the snake collides with itself or with the borders
        if(snake.isDead()
                || snake.getHead().getGlobalBounds().intersects(leftBorder.getGlobalBounds())
                || snake.getHead().getGlobalBounds().intersects(rightBorder.getGlobalBounds())
                || snake.getHead().getGlobalBounds().intersects(upBorder.getGlobalBounds())
                || snake.getHead().getGlobalBounds().intersects(downBorder.getGlobalBounds()))
            window.close();
        snake.move();

        window.draw(food);

        window.display();
    }

    return 0;
}
