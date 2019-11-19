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

Snake::Snake(const float& x, const float& y, const float sizeOfSquare, const sf::Color& headColor, const sf::Color& bodyColor) : mSizeOfSquare(sizeOfSquare), mHeadColor(headColor), mBodyColor(bodyColor) {
        // reserving 10 spaces for the body beforehand to prevent copying
        mBody.reserve(10);
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

    food.mColor = sf::Color::Transparent;

}
