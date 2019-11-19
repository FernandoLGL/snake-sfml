#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Constants.h"
#include "Snake.h"
#include "Food.h"

int main() {

    // Game Window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Snake!");
    window.setFramerateLimit(60);

    Snake snake(400,300);
    Food food(20,30);

    // Game loop
    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        sf::Event event;

        // just testing out Keyboard
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        // event pending ?
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){

                switch(event.key.code){
                case sf::Keyboard::Key::A:
                case sf::Keyboard::Key::Left:
                    // You can't move left or right if you're already moving left
                    if(snake.getDirection() == Direction::LEFT || snake.getDirection() == Direction::RIGHT)
                        break;
                    snake.moveLeft();
                    break;
                case sf::Keyboard::Key::Right:
                case sf::Keyboard::Key::D:
                    if(snake.getDirection() == Direction::RIGHT || snake.getDirection() == Direction::LEFT)
                        break;
                    snake.moveRight();
                    break;

                case sf::Keyboard::Key::Up:
                case sf::Keyboard::Key::W:
                    if(snake.getDirection() == Direction::UP || snake.getDirection() == Direction::DOWN)
                        break;
                    snake.moveUp();
                    break;
                case sf::Keyboard::Key::S:
                case sf::Keyboard::Key::Down:
                    if(snake.getDirection() == Direction::UP || snake.getDirection() == Direction::DOWN)
                        break;
                    snake.moveDown();
                    break;
                 default:
                    break;
                }
            }
        }

        snake.draw(window);
        if(snake.isDead())
            window.close();
        snake.continueMoving();

        window.draw(food);

        window.display();
    }

    return 0;
}
