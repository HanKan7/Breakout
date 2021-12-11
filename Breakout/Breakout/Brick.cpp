#include "Brick.h"

Brick::Brick(int numberOfHitsTakenToDestroy, sf::Vector2f pos) 
{
	this->numberOfHitsTakenToDestroy = numberOfHitsTakenToDestroy;
	this->InitialPostion = pos;
    this->Size = sf::Vector2f(75.0f, 15.0f);
    this->color = sf::Color::White;
    brick.setFillColor(color);
    brick.setPosition(InitialPostion);
    brick.setSize(Size);
    brickRect = brick.getGlobalBounds();

    const char* texturePath("Brick.png");
    if (!texture.loadFromFile(texturePath)) {
        cout << "Failed to load texture\n";
    }

    scoreIncrement = 5;
    scoreIncrementOnDestroy = 10;
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
    const char* texturePath("Brick.png");
    if (!texture.loadFromFile(texturePath)) {
        cout << "Failed to load texture\n";
    }
    brick.setTexture(&texture);
}
