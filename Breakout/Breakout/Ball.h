#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

//#include"Paddle.h"
#include"Brick.h"

#include<iostream>
#include<vector>
using namespace std;
using namespace sf;

class Ball
{
public:
	sf::CircleShape ball;
	float radius;
	sf::Vector2f InitialPosition;
	sf::Color color;
	sf::Vector2f ballInitialVelocity;
	sf::Vector2f ballVelocity;
	sf::FloatRect ballRect;

	sf::Font font;
	sf::Text numberOfLivesText;
	sf::Text gameLevel;
	sf::Text playerScoreText;

	SoundBuffer ballPaddleBuffer;
	SoundBuffer ballDamageBuffer;
	SoundBuffer ballDestroyBuffer;
	SoundBuffer ballWallBuffer;
	SoundBuffer playerLostAlifeBuffer;
	SoundBuffer gameOverBuffer;
	SoundBuffer winLevelBuffer;


	sf::Sound ballPaddleSound;
	sf::Sound ballDamageSound;
	sf::Sound ballDestroySound;
	sf::Sound ballWallSound;
	sf::Sound playerLostAlifeSound;
	sf::Sound gameOverSound;
	sf::Sound winLevelSound;

	sf::Texture texture;
	sf::Sprite ballSprite;

	int numberOfLives = 3;
	int playerScore = 0;
	bool hasLaunchedTheBall = false;

	Ball();
	void CollisionWithPaddle(sf::RectangleShape* paddle, bool hasLaunchedTheBall);
	void CollisionWithBrick(Brick* brick);
	void UpdateBallPosition(sf::RenderWindow* window, float delta_s);
	void ResetBallWithMoreSpeed(bool didGameRestart);
	void UpdatePlayerLives();
};


