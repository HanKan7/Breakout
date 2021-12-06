#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

class Brick
{
	public:
	sf::RectangleShape brick;
	sf::Vector2f Size;
	sf::Vector2f InitialPostion;
	sf::Color color;
	sf::FloatRect brickRect;
	int numberOfHitsTakenToDestroy;
	bool isDead;

	Brick(int numberOfHitTakenToDestroy, sf::Vector2f pos);
	void BrickInit(int numberOfHitTakenToDestroy, sf::Vector2f pos);
};

