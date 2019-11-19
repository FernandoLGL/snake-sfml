#include "Snake.h"

Snake Snake::operator++(int dummy){
    // dummy == 0 and it only occurs in postfix increment (I'm not allowing prefix increment)
    // operator++ should add another square to the body
    sf::Vector2f lastPosition = mBody.back().getPosition();
    //adding the square itself
    mBody.emplace_back(sf::Vector2f(mSizeOfSquare, mSizeOfSquare));
    //setting the position of the new square
    mBody.back().setPosition(lastPosition.x + mSizeOfSquare, lastPosition.y);
    //setting color
    mBody.back().setFillColor(sf::Color::Green);
    // returning the newly formed snake object
    return *(this);
}

void Snake::draw(sf::RenderWindow& window) const{
    window.draw(mHead);
    for(const auto& bodyPart : mBody)
        window.draw(bodyPart);
}

Snake::Snake(const float& x, const float& y, const float& speed, const float sizeOfSquare, const sf::Color& headColor, const sf::Color& bodyColor) : mSizeOfSquare(sizeOfSquare), mHeadColor(headColor), mBodyColor(bodyColor), mDirection(Direction::LEFT), mSpeed(speed) {
    // reserving 10 spaces for the body beforehand to prevent copying
    // note the implicit conversion from float to integer
    mBody.reserve(sizeOfSquare + 10);
    for(int i = 0; i<4; ++i){
        //Adding a square in each position (the initial size of the snake is 5)
        mBody.emplace_back(sf::Vector2f(sizeOfSquare, sizeOfSquare));
        mBody[i].setPosition(x + (i+1)*sizeOfSquare, y);
        mBody[i].setFillColor(bodyColor);
    }
    mHead = sf::RectangleShape(sf::Vector2f(sizeOfSquare, sizeOfSquare));
    mHead.setPosition(mBody[0].getPosition() - sf::Vector2f(sizeOfSquare,0));
    mHead.setFillColor(headColor);
}

void Snake::eat(Food &food) const{

    food.setFillColor(sf::Color::Transparent);

}

// Just have to multiply/divide "mSizeOfSquare" to change the snake speed.

void Snake::moveLeft()
{
    mHead.setPosition(mHead.getPosition().x - mSizeOfSquare*mSpeed, mHead.getPosition().y);
    mDirection = Direction::LEFT;
}

void Snake::moveRight(){
    mHead.setPosition(mHead.getPosition().x + mSizeOfSquare*mSpeed, mHead.getPosition().y);
    mDirection = Direction::RIGHT;
}

void Snake::moveDown(){
    mHead.setPosition(mHead.getPosition().x, mHead.getPosition().y + mSizeOfSquare*mSpeed);
    mDirection = Direction::DOWN;
}

void Snake::moveUp(){
    mHead.setPosition(mHead.getPosition().x, mHead.getPosition().y - mSizeOfSquare*mSpeed);
    mDirection = Direction::UP;
}

void Snake::continueMoving()
{
    switch(mDirection){
    case Direction::UP:
        moveUp();
        break;
    case Direction::DOWN:
        moveDown();
        break;
    case Direction::LEFT:
        moveLeft();
        break;
    default:
        moveRight();
        break;
    }
}

bool Snake::isDead(){
    const float headX = mHead.getPosition().x;
    const float headY = mHead.getPosition().y;
    float bodyPartX;
    float bodyPartY;

    for (const auto& bodyPart : mBody){
        bodyPartX = bodyPart.getPosition().x;
        bodyPartY = bodyPart.getPosition().y;

        // This still isn't perfect. There are cases where this doesn't work. Have to find out why.
        if(headX <= bodyPartX + mSizeOfSquare && headX >= bodyPartX  // Horizontal coliding
                    && headY <= bodyPartY + mSizeOfSquare && headY >= bodyPartY // Vertical coliding
                )
            return true;
    }
    return false;
}
