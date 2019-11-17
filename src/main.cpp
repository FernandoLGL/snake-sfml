#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;

// we need to keep track of the snake direction
enum class Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake{
    // size of each snake body(including the head) square
    const float mSizeOfSquare;
    sf::RectangleShape mHead;
    std::vector<sf::RectangleShape> mBody;
    Direction direction;
    float mX, mY;

public:
    // operator++ should add another square to the body
    Snake operator++(int dummy){
        sf::Vector2f lastPosition = mBody.back().getPosition();
        //adding the square itself
        mBody.emplace_back(sf::Vector2f(mSizeOfSquare, mSizeOfSquare));
        //setting the position of the new square
        mBody.back().setPosition(lastPosition + sf::Vector2f(mSizeOfSquare, mSizeOfSquare));
        // returning the newly formed snake object
        return *(this);
    }

    const sf::RectangleShape& getHead() const{
        return mHead;
    }

    const std::vector<sf::RectangleShape>& getBody() const{
        return mBody;
    }

    void draw(sf::RenderWindow& window) const{
        window.draw(mHead);
        for(const auto& bodyPart : mBody)
            window.draw(bodyPart);
    }

public:
    Snake(float x, float y, const float sizeOfSquare = 10.f) : mSizeOfSquare(sizeOfSquare) {
        // reserving 10 spaces for the body beforehand to prevent copying
        mBody.reserve(10);
        for(int i = 0; i<4; ++i){
            //Adding a square in each position (the initial size of the snake is 5)
            mBody.emplace_back(sf::Vector2f(sizeOfSquare, sizeOfSquare));
            mBody.at(i).setPosition(x + (i+1)*sizeOfSquare, y);
            // the body color is green
            mBody.at(i).setFillColor(sf::Color::Green);
        }
        mHead = sf::RectangleShape(sf::Vector2f(sizeOfSquare, sizeOfSquare));
        mHead.setPosition(mBody.at(0).getPosition() - sf::Vector2f(sizeOfSquare,0));
        // the color of the head is red
        mHead.setFillColor(sf::Color::Red);
    }
};

int main() {

    // Game Window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Snake!");
    window.setFramerateLimit(60);

    // Game loop
    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        sf::Event event;

        Snake snake(400,300);

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

        window.display();
    }

    return 0;
}
