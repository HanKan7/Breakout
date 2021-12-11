#include"Ball.h"
#include"PowerUp.h"
class Paddle
{
public:
	sf::RectangleShape paddle;
	sf::Vector2f Size;
	sf::Vector2f InitialPostion;
	sf::Color color;
	sf::FloatRect paddleRect;
	sf::Vector2i prevMousPos = sf::Vector2i(0, 0);
	Clock powerUpCollectedTime;
	bool bulletReachedEnd = true;
	
	Paddle();
	void Clamp(sf::RectangleShape* paddle);
	void Movement(sf::RectangleShape* paddle, int moveSpeed);
	void MovementWithMouse(sf::RectangleShape* paddle, int moveSpeed, sf::RenderWindow* window);
	void UpdateBallsPosition(Ball* ball, bool hasLaunchedTheBall);
	void CollisionCheckWithBall(Ball* ball);
	void CollisionWithPowerUp(PowerUp* powerUp);
	void ShootBullet(PowerUp* powerUp, float delta_s);
};


