#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;

int main() {

    // Game Window
    sf::RenderWindow window({windowWidth, windowHeight}, "Snake!");
    window.setFramerateLimit(60);

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

        window.display();
    }

    return 0;
}
