#include "Brick.h"

Brick::Brick(int numberOfHitsTakenToDestroy, sf::Vector2f pos) 
{
	this->numberOfHitsTakenToDestroy = numberOfHitsTakenToDestroy;
	this->InitialPostion = pos;
    this->Size = sf::Vector2f(100.0f, 15.0f);
    this->color = sf::Color::White;
    brick.setFillColor(color);
    brick.setPosition(InitialPostion);
    brick.setSize(Size);
    brickRect = brick.getGlobalBounds();
    isDead = false;
}


void Brick::BrickInit(int numberOfHitTakenToDestroy, sf::Vector2f pos) 
{
    this->numberOfHitsTakenToDestroy = numberOfHitsTakenToDestroy;
    this->InitialPostion = pos;
    this->Size = sf::Vector2f(145.0f, 15.0f);
    this->color = sf::Color::Red;
    brick.setFillColor(color);
    brick.setPosition(InitialPostion);
    brick.setSize(Size);
    brickRect = brick.getGlobalBounds();
    isDead = false;
}
