#include "PowerUp.h"

PowerUp::PowerUp() 
{
	radius = 7.f;
	color = sf::Color::Yellow;
	InitialPosition = Vector2f(350, 20);
	initialVelocity = sf::Vector2f(0, 30.f);
	velocity = sf::Vector2f(0, 120.f);
	bulletVelocity = Vector2f(0, -200);
	powerUp.setRadius(radius);
	powerUp.setFillColor(color);
	powerUp.setPosition(InitialPosition);

	bullet.setRadius(radius);
	bullet.setFillColor(Color::Cyan);
	bullet.setPosition(InitialPosition);
}

void PowerUp::SpawnPowerUp(float delta_s)
{
	auto ballPos = powerUp.getPosition();
	ballPos += velocity * delta_s;

	powerUp.setPosition(ballPos);
}

void PowerUp::CollisionWithBrick(Brick* brick, Ball* ball)
{
	if (brick->isDead)   return;
	sf::FloatRect ballRect = bullet.getGlobalBounds();
	sf::FloatRect brickRect = brick->brick.getGlobalBounds();

	if (ballRect.intersects(brickRect))
	{
		ball->playerScore += brick->scoreIncrement;
		brick->numberOfHitsTakenToDestroy--;
		if (brick->numberOfHitsTakenToDestroy <= 0) {
			brick->isDead = true;
			ball->playerScore += brick->scoreIncrementOnDestroy;
		}

		ball->playerScoreText.setString("SCORE = " + to_string(ball->playerScore));
	}
}
