#include "Ball.h"

Ball::Ball()
{
    radius = 10.f;
    color = sf::Color::White;
    //InitialPosition = sf::Vector2f(x, y);
    ballInitialVelocity = sf::Vector2f(-600.f, -400.f);
    ballVelocity = sf::Vector2f(-600.f, -400.f);
    ball.setRadius(radius);
    ball.setFillColor(color);
    ball.setPosition(InitialPosition);
    ballRect = ball.getGlobalBounds();

    //Setting font
    const char* fontPath = "American Captain.ttf";
    if (!font.loadFromFile(fontPath)) {
        cout << "Failed to load font\n";
    }

    numberOfLivesText.setFont(font);
    numberOfLivesText.setFillColor(sf::Color::White);
    numberOfLivesText.setPosition(570.f, 20.f);
    numberOfLivesText.setString("Number Of Lives = " + to_string(numberOfLives));

    playerScoreText.setFont(font);
    playerScoreText.setFillColor(sf::Color::White);
    playerScoreText.setPosition(70.f, 20.f);
    playerScoreText.setString("SCORE = " + to_string(playerScore));

    const char* texturePath("Ball.png");
    if (!texture.loadFromFile(texturePath)) {
        cout << "Failed to load texture\n";
    }
    ball.setTexture(&texture);
}

void Ball::CollisionWithPaddle(sf::RectangleShape* paddle, bool hasLaunchedTheBall)
{
    if (!hasLaunchedTheBall)
    {
        ball.setPosition(paddle->getPosition() + sf::Vector2f(0.f, -20.f));
        ballSprite.setPosition(ball.getPosition());
    }
    else 
    {
        sf::FloatRect ballRect =ball.getGlobalBounds();
        sf::FloatRect paddleRect = paddle->getGlobalBounds();

            if (paddleRect.intersects(ballRect)) {
                // cout << "Collision\n";
                if (ball.getPosition().x > (paddle->getPosition().x + paddle->getSize().x * 4 / 5)) //Greater than 80%
                {
                    //cout << "Collision 80\n";
                    ballVelocity.y = -abs(ballVelocity.y);
                    srand(time(0));
                    int value = rand() % 100 + 600;
                    ballVelocity.x = abs(value);
                }
                else if (ball.getPosition().x > (paddle->getPosition().x + paddle->getSize().x * 3 / 5) && ball.getPosition().x < (paddle->getPosition().x + paddle->getSize().x * 4 / 5)) //Greater than 60%, Less than 80%
                {
                    //cout << "Collision 60 80 \n";
                    ballVelocity.y = -abs(ballVelocity.y);
                    srand(time(0));
                    int value = rand() % 100 + 500;
                    ballVelocity.x = abs(value);
                }
                else if (ball.getPosition().x > (paddle->getPosition().x + paddle->getSize().x * 2 / 5) && ball.getPosition().x < (paddle->getPosition().x + paddle->getSize().x * 3 / 5)) //Greater than 40%, Less than 60%
                {
                    //cout << "Collision 50\n";
                    ballVelocity.y = -abs(ballVelocity.y);
                    cout << "Ball velocity =  " << ballVelocity.y << endl;
                    ballVelocity.x = abs(0.f);
                }
                else if (ball.getPosition().x > (paddle->getPosition().x + paddle->getSize().x * 1 / 5) && ball.getPosition().x < (paddle->getPosition().x + paddle->getSize().x * 2 / 5)) //Greater than 20%, Less than 40%
                {
                    //cout << "Collision 40\n";
                    ballVelocity.y = -abs(ballVelocity.y);
                    srand(time(0));
                    int value = rand() % 100 + 500;
                    ballVelocity.x = -abs(value);
                }
                if (ball.getPosition().x < (paddle->getPosition().x + paddle->getSize().x * 1 / 5)) //Less than 20%
                {
                    //cout << "Collision 20\n";
                    ballVelocity.y = -abs(ballVelocity.y);
                    srand(time(0));
                    int value = rand() % 100 + 600;
                    ballVelocity.x = -abs(value);
                }

            }
    
    }
}

void Ball::CollisionWithBrick(Brick* brick) 
{
    if (brick->isDead)   return;
    sf::FloatRect ballRect = ball.getGlobalBounds();
    sf::FloatRect brickRect = brick->brick.getGlobalBounds();

    if (ballRect.intersects(brickRect))
    {
        playerScore += brick->scoreIncrement;
        brick->numberOfHitsTakenToDestroy--;
        if (brick->numberOfHitsTakenToDestroy <= 0) {
            brick->isDead = true;
            playerScore += brick->scoreIncrementOnDestroy;
        }
        ballVelocity.x = (ballVelocity.x);
        ballVelocity.y = -(ballVelocity.y);

        playerScoreText.setString("SCORE = " + to_string(playerScore));
    }
}

void Ball::UpdateBallPosition(sf::RenderWindow* window, float delta_s)
{
    auto ballPos = ball.getPosition();
    ballPos += ballVelocity * delta_s;

    auto maxX = window->getSize().x - ball.getRadius() * 2.0f;
    if (ballPos.x >= maxX) {
        //bounce.play();
        ballVelocity.x = -abs(ballVelocity.x);
        ballPos.x = maxX;
        return;
    }

    if (ballPos.x <= 0.0) {
        ballVelocity.x = abs(ballVelocity.x);
        ballPos.x = 0.f;
        return;
    }

    auto maxY = window->getSize().y - ball.getRadius() * 2.0f;
    if (ballPos.y >= maxY) {
        ballPos.y = maxY;
        hasLaunchedTheBall = false;
        ballVelocity = ballInitialVelocity;
        UpdatePlayerLives();
    }

    if (ballPos.y <= 0.0) {
        ballVelocity.y = abs(ballVelocity.y);
        ballPos.y = 0.f;
    }
    ball.setPosition(ballPos);
}

void Ball::ResetBallWithMoreSpeed(bool didGameRestart) 
{
    if (!didGameRestart) {
        hasLaunchedTheBall = false;
        ballInitialVelocity.x *= 1.1f;
        ballInitialVelocity.y *= 1.2;
        ballVelocity = ballInitialVelocity;
    }

    else {
        hasLaunchedTheBall = false;
        ballInitialVelocity = sf::Vector2f(-600.f, -400.f);
        ballVelocity = ballInitialVelocity;
    }
    
}

void Ball::UpdatePlayerLives() 
{
    
    numberOfLives--;
    if (numberOfLives <= 0)  numberOfLives = 0;
    numberOfLivesText.setString("Number Of Lives = " + to_string(numberOfLives));
}

