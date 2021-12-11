#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include<iostream>
using namespace std;
class ParentBrick
{
public:
	sf::RectangleShape brick;
	sf::Vector2f Size;
	sf::Vector2f InitialPostion;
	sf::Color color;
	sf::FloatRect brickRect;


	int scoreIncrement = 5;
	int scoreIncrementOnDestroy = 10;


	bool isDead;
};

