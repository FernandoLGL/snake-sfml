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

    Snake snake(400,300,0.5);
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
                    snake.setDirection(Direction::LEFT);
                    break;
                case sf::Keyboard::Key::Right:
                case sf::Keyboard::Key::D:
                    snake.setDirection(Direction::RIGHT);
                    break;

                case sf::Keyboard::Key::Up:
                case sf::Keyboard::Key::W:
                    snake.setDirection(Direction::UP);
                    break;
                case sf::Keyboard::Key::S:
                case sf::Keyboard::Key::Down:
                    snake.setDirection(Direction::DOWN);
                    break;
                 default:
                    break;
                }
            }
        }

        if(snake.getHead().getGlobalBounds().intersects(food.getGlobalBounds())){
            snake++;
            snake.eat(food);
        }

        snake.draw(window);
        if(snake.isDead())
            window.close();
        snake.move();

        window.draw(food);

        window.display();
    }

    return 0;
}
