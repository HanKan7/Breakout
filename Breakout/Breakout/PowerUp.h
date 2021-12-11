#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include"Brick.h"
#include"Ball.h"
using namespace sf;

class PowerUp
{
public:
	sf::CircleShape powerUp;
	sf::CircleShape bullet;
	float radius;
	sf::Vector2f InitialPosition;
	sf::Color color;
	sf::Vector2f initialVelocity;
	sf::Vector2f velocity;
	sf::Vector2f bulletVelocity;
	Clock powerUpClock;

	bool powerUpCollected = false;;
	bool shotBullet = false;

	PowerUp();
	void SpawnPowerUp(float delta_s);
	void CollisionWithBrick(Brick* brick, Ball* ball);
};

