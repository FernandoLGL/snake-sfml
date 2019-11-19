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
        }

        // Drawing the whole snake
        snake.draw(window);

        // Drawing food
        window.draw(food);

        window.display();
    }

    return 0;
}
