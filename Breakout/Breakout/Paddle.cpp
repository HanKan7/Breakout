#include "Paddle.h"

Paddle::Paddle()
{
    this->InitialPostion = sf::Vector2f(335.0f, 560.0f);
    this->Size = sf::Vector2f(145.0f, 15.0f);
    this->color = sf::Color::Red;
    paddle.setFillColor(color);
    paddle.setPosition(InitialPostion);
    paddle.setSize(Size);
    paddleRect = paddle.getGlobalBounds();
}

void Paddle::Clamp(sf::RectangleShape* paddle)
{
    if (paddle->getPosition().x < 45.0f)
    {
        paddle->setPosition(sf::Vector2f(45.0f, paddle->getPosition().y));
    }

    if (paddle->getPosition().x > 615.0f)
    {
        paddle->setPosition(sf::Vector2f(615.0f, paddle->getPosition().y));
    }
}

void Paddle::Movement(sf::RectangleShape* paddle, int moveSpeed)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        paddle->move(sf::Vector2f(-moveSpeed * 1.5f, 0.f));
        //neonSprite.setPosition(player->getPosition());
        Clamp(paddle);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        paddle->move(sf::Vector2f(moveSpeed * 1.5f, 0.f));
        //neonSprite.setPosition(player->getPosition());
        Clamp(paddle);
    }
}

void Paddle::MovementWithMouse(sf::RectangleShape* paddle, int moveSpeed, sf::RenderWindow* window) 
{
    sf::Vector2f paddlePos = paddle->getPosition();
    sf::Vector2i mousePos = sf::Mouse::getPosition();
    

    if (mousePos.x > prevMousPos.x) 
    {
        paddle->move(sf::Vector2f(moveSpeed, 0.f));
        //neonSprite.setPosition(player->getPosition());
        Clamp(paddle);
    }

    else if (mousePos.x < prevMousPos.x)
    {
        paddle->move(sf::Vector2f(-moveSpeed , 0.f));
        //neonSprite.setPosition(player->getPosition());
        Clamp(paddle);
    }

    prevMousPos = mousePos;

}

void Paddle::UpdateBallsPosition(Ball* ball, bool hasLaunchedTheBall)
{
    if (!ball->hasLaunchedTheBall)
    {
        ball->ball.setPosition(paddle.getPosition() + sf::Vector2f(0.f, -20.f));
    }
}

void Paddle::CollisionCheckWithBall(Ball* ball)
{
    sf::FloatRect ballRect = ball->ball.getGlobalBounds();
    sf::FloatRect paddleRect = paddle.getGlobalBounds();
    if (ball->hasLaunchedTheBall) {


        if (paddleRect.intersects(ballRect)) {
            // cout << "Collision\n";
            if (ball->ball.getPosition().x > (paddle.getPosition().x + paddle.getSize().x * 4 / 5)) //Greater than 80%
            {
                //cout << "Collision 80\n";
                ball->ballVelocity.y = -abs(ball->ballVelocity.y);
                srand(time(0));
                int value = rand() % 100 + 600;
                ball->ballVelocity.x = abs(value);
            }
            else if (ball->ball.getPosition().x > (paddle.getPosition().x + paddle.getSize().x * 3 / 5) && ball->ball.getPosition().x < (paddle.getPosition().x + paddle.getSize().x * 4 / 5)) //Greater than 60%, Less than 80%
            {
                //cout << "Collision 60 80 \n";
                ball->ballVelocity.y = -abs(ball->ballVelocity.y);
                srand(time(0));
                int value = rand() % 100 + 500;
                ball->ballVelocity.x = abs(value);
            }
            else if (ball->ball.getPosition().x > (paddle.getPosition().x + paddle.getSize().x * 2 / 5) && ball->ball.getPosition().x < (paddle.getPosition().x + paddle.getSize().x * 3 / 5)) //Greater than 40%, Less than 60%
            {
                //cout << "Collision 50\n";
                ball->ballVelocity.y = -abs(ball->ballVelocity.y);
                //cout << "Ball velocity =  " << ball->ballVelocity.y << endl;
                ball->ballVelocity.x = abs(0.f);
            }
            else if (ball->ball.getPosition().x > (paddle.getPosition().x + paddle.getSize().x * 1 / 5) && ball->ball.getPosition().x < (paddle.getPosition().x + paddle.getSize().x * 2 / 5)) //Greater than 20%, Less than 40%
            {
                //cout << "Collision 40\n";
                ball->ballVelocity.y = -abs(ball->ballVelocity.y);
                srand(time(0));
                int value = rand() % 100 + 500;
                ball->ballVelocity.x = -abs(value);
            }
            if (ball->ball.getPosition().x < (paddle.getPosition().x + paddle.getSize().x * 1 / 5)) //Less than 20%
            {
                //cout << "Collision 20\n";
                ball->ballVelocity.y = -abs(ball->ballVelocity.y);
                srand(time(0));
                int value = rand() % 100 + 600;
                ball->ballVelocity.x = -abs(value);
            }

        }

    }

}

void Paddle::CollisionWithPowerUp(PowerUp* powerUp)
{
    sf::FloatRect powerUpRect = powerUp->powerUp.getGlobalBounds();
    sf::FloatRect paddleRect = paddle.getGlobalBounds();

    if (paddleRect.intersects(powerUpRect)) 
    {
        powerUp->powerUpCollected = true;
        powerUp->bullet.setPosition(Vector2f(paddle.getPosition().x + paddle.getSize().x / 2, paddle.getPosition().y));
    }
}

void Paddle::ShootBullet(PowerUp* powerUp,float delta_s)
{
    if (powerUp->powerUpCollected && !bulletReachedEnd) 
    {
        powerUp->shotBullet = true;

        auto ballPos = powerUp->bullet.getPosition();
        ballPos += powerUp->bulletVelocity * delta_s;

        if (powerUp->bullet.getPosition().y <= 0)
        {
            //cout << "reached end\n";
            powerUp->shotBullet = false;
            powerUp->bullet.setPosition(Vector2f(paddle.getPosition().x + paddle.getSize().x / 2, paddle.getPosition().y));
            bulletReachedEnd = true;
        }

        powerUp->bullet.setPosition(ballPos);
    }
}
