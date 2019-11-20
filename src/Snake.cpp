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
    sf::RectangleShape temporaryVariable(sf::Vector2f(mSizeOfSquare, mSizeOfSquare));
    for(int i = 0; i<4; ++i){
        temporaryVariable.setFillColor(bodyColor);
        temporaryVariable.setPosition(x + (i+1)*sizeOfSquare, y);
        mBody.emplace_back(temporaryVariable);
    }
    mHead = sf::RectangleShape(sf::Vector2f(sizeOfSquare, sizeOfSquare));
    // *1.5 just for now
    mHead.setPosition(mBody.front().getPosition() - sf::Vector2f(sizeOfSquare,0));
    mHead.setFillColor(headColor);
}

void Snake::eat(Food &food) const{

    //food.setFillColor(sf::Color::Transparent);
    food.respawn();
}

void Snake::move()
{
    const sf::Vector2f lastHeadPosition = mHead.getPosition();
    switch(mDirection){
    case Direction::UP:
        mHead.setPosition(mHead.getPosition().x, mHead.getPosition().y - mSizeOfSquare*mSpeed);
        mBody.front().setPosition(lastHeadPosition + sf::Vector2f(0,mSizeOfSquare/2));
        break;
    case Direction::DOWN:
    mHead.setPosition(mHead.getPosition().x, mHead.getPosition().y + mSizeOfSquare*mSpeed);
        mBody.front().setPosition(lastHeadPosition - sf::Vector2f(0,mSizeOfSquare/2));
        break;
    case Direction::LEFT:
    mHead.setPosition(mHead.getPosition().x - mSizeOfSquare*mSpeed, mHead.getPosition().y);
        mBody.front().setPosition(lastHeadPosition + sf::Vector2f(mSizeOfSquare/2,0));
        break;
    default:
    mHead.setPosition(mHead.getPosition().x + mSizeOfSquare*mSpeed, mHead.getPosition().y);
        mBody.front().setPosition(lastHeadPosition - sf::Vector2f(mSizeOfSquare/2,0));
        break;
    }
        mBody.insert(mBody.begin(), mBody.back());
        mBody.pop_back();
}

bool Snake::isDead(){
    bool collides;

    for (const auto& bodyPart : mBody){
            collides = mHead.getGlobalBounds().intersects(bodyPart.getGlobalBounds());
            if(collides)
                return true;
    }
    return false;
}
