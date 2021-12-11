#include"Paddle.h"
#include"Brick.h"
#include"PowerUp.h"
using namespace std;



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "BREAKOUT!");
    window.setVerticalSyncEnabled(true);
    Clock clock;
    Clock powerUpClock;
    int gameLevel = 0;
    int powerUpScore = 55;
    float powerUpClockValue = 0;
    float powerUpCollectedClockValue = 0;

    Paddle paddle;
    Ball mainBall;
    PowerUp powerUp;
    vector<Brick> bricks;

    sf::Font font;
    sf::Text GameOverText;
    const char* fontPath = "American Captain.ttf";
    if (!font.loadFromFile(fontPath)) {
        cout << "Failed to load font\n";
    }

    GameOverText.setFont(font);
    GameOverText.setFillColor(sf::Color::White);
    GameOverText.setPosition(300.f, 300.f);

    bool areAllBrickDestroyed;
    bool powerUpSpawned = false;
    bool powerUpCollected = false;
  
    int brickCount;
#pragma region BrickInit
    
    if (gameLevel == 0)
    {
        vector<sf::Vector2f> BrickPosition;
        sf::Vector2f brickStartPos = sf::Vector2f(620.f, 75.f);
        brickCount = 12;
        areAllBrickDestroyed = false;

        for (float i = 0; i < brickCount; i++)
        {
            BrickPosition.push_back(brickStartPos);
            //cout << " X = " << brickStartPos.x << "    Y = " << brickStartPos.y << endl;
            brickStartPos.x -= 45;
            brickStartPos.y += 35;
        }

        

        for (float i = 0; i < BrickPosition.size(); i++)
        {
            Brick brick(1, BrickPosition[i]);
            bricks.push_back(brick);
        }
    }

    else if (gameLevel == 2) 
    {
        vector<sf::Vector2f> BrickPosition;
        sf::Vector2f brickStartPos = sf::Vector2f(620.f, 75.f);
        int brickCount = 10;
        bool areAllBrickDestroyed = false;
    }
    

#pragma endregion

    while (window.isOpen())
    {
#pragma region ClockEvent
        float delta_s = clock.getElapsedTime().asSeconds();
        clock.restart();
#pragma endregion

#pragma region WindowEvents
        sf::Event evt;
        while (window.pollEvent(evt)) {
            switch (evt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:

                //cout << "New Window width:" << evt.size.width << " New Window Height: " << evt.size.height << endl;
                break;

            default:
                break;
            }
        }
#pragma endregion

#pragma region KeyBoardInput
        paddle.Movement(&paddle.paddle, 10.5f);
        paddle.MovementWithMouse(&paddle.paddle, 10.5f, &window);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            mainBall.hasLaunchedTheBall = true;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
        {
            mainBall.hasLaunchedTheBall = true;
        }
#pragma endregion

#pragma region UpdateBallsPosition
        if (mainBall.hasLaunchedTheBall)
        {
            mainBall.UpdateBallPosition(&window, delta_s);
        }
        else
        {
            mainBall.CollisionWithPaddle(&paddle.paddle, mainBall.hasLaunchedTheBall);
        }

#pragma endregion

#pragma region Collision Check
        mainBall.CollisionWithPaddle(&paddle.paddle, mainBall.hasLaunchedTheBall);

        for (int i = 0; i < bricks.size(); i++) 
        {
            mainBall.CollisionWithBrick(&bricks[i]);
        }
        if (powerUpCollected) {

            for (int i = 0; i < bricks.size(); i++)
            {
                powerUp.CollisionWithBrick(&bricks[i], &mainBall);
            }
        }
        //        mainBall.CollisionCheck(paddle);
        //        mainBall.CollisionCheck(leftPlayer);
        //
        //        if (fourPlayerMode == 1) {
        //            mainBall.CollisionCheck(smallLeftPlayer);
        //            mainBall.CollisionCheck(smallRightPlayer);
        //        }
        //
        //        if (blockInTheMiddle == 1) {
        //            mainBall.CollisionCheck(wallLeft);
        //            mainBall.CollisionCheck(wallRight);
        //        }
        //
        //        if (powerUp == 1) {
        //            if (mainBall.RightHit)
        //            {
        //                mainBall.CollisionWithPowerUp(power, power.rightPaddle);
        //            }
        //            else {
        //                mainBall.CollisionWithPowerUp(power, power.leftPaddle);
        //            }
        //        }
#pragma endregion   

        if (mainBall.playerScore >= powerUpScore) 
        {
            if (!powerUpSpawned) 
            {
                powerUpClockValue = powerUp.powerUpClock.getElapsedTime().asSeconds();
                powerUpSpawned = true;
            }

            if (powerUpClockValue + 5 > powerUp.powerUpClock.getElapsedTime().asSeconds()) 
            {
                powerUp.SpawnPowerUp(delta_s);
                paddle.CollisionWithPowerUp(&powerUp);
            }
            else 
            {
                //cout << "false";
                powerUpScore += powerUpScore * 1.5f;
                powerUp.powerUp.setPosition(powerUp.InitialPosition);
                powerUpSpawned = false;

            }
            

        }

        if (powerUp.powerUpCollected)
        {
            if (!powerUpCollected) 
            {
                //cout << "powerUpCOlle";
                powerUpCollectedClockValue = paddle.powerUpCollectedTime.getElapsedTime().asSeconds();
                powerUpCollected = true;
            }

            if (powerUpCollectedClockValue + 5 > paddle.powerUpCollectedTime.getElapsedTime().asSeconds()) 
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                {
                    paddle.bulletReachedEnd = false;
                }
                if(!powerUp.shotBullet && !paddle.bulletReachedEnd)
                powerUp.bullet.setPosition(Vector2f(paddle.paddle.getPosition().x + paddle.paddle.getSize().x / 2, paddle.paddle.getPosition().y));
                paddle.ShootBullet(&powerUp, delta_s);
               
            }
            else 
            {
                powerUp.powerUpCollected = false;
                powerUpCollected = false;
            }      
        }

#pragma region GameHasEnded
        bool didGameRestart = false;
        if (mainBall.numberOfLives <= 0) 
        {
            mainBall.gameOverSound.play();
            GameOverText.setString("GAME OVER\nYOUR SCORE IS " + to_string(mainBall.playerScore) + "\n Press R to restart the game\n Q to quit the game");
            bool playerHasEnteredTheInput = false;
            while (!playerHasEnteredTheInput)
            {
                window.clear();
                window.draw(GameOverText);
                window.display();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
                {
                    didGameRestart = true;
                    playerHasEnteredTheInput = true;
                    mainBall.numberOfLives = 3;
                    powerUpScore = 55;
                    mainBall.numberOfLivesText.setString("Number Of Lives = " + to_string(mainBall.numberOfLives));
                    mainBall.playerScore = 0;
                    mainBall.playerScoreText.setString("SCORE = " + to_string(mainBall.playerScore));
                    //mainBall.ballVelocity = mainBall.ballInitialVelocity();
                    gameLevel = 1;

                    for (int i = 0; i < bricks.size(); i++)
                    {
                        bricks[i].isDead = false;
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) 
                {
                    return 1;
                }
            }
        }

#pragma endregion

#pragma region AreAllBrickDestroyed

        for (int i = 0; i < brickCount; i++) 
        {
            if (!bricks[i].isDead)   break;
            if (i == brickCount - 1 && bricks[i].isDead) 
            {
                areAllBrickDestroyed = true;
            }
        }

        if (areAllBrickDestroyed) 
        {
            mainBall.winLevelSound.play();
            mainBall.ResetBallWithMoreSpeed(didGameRestart);
            didGameRestart = false;
            /*for (int i = 0; i < bricks.size(); i++) {
                bricks[i].isDead = false;
            }*/
            gameLevel = (gameLevel + 1) % 3;
            bricks.clear();

            if (gameLevel == 0)
            {
                vector<sf::Vector2f> BrickPosition;
                sf::Vector2f brickStartPos = sf::Vector2f(620.f, 75.f);
                brickCount = 12;
                areAllBrickDestroyed = false;

                for (float i = 0; i < brickCount; i++)
                {
                    BrickPosition.push_back(brickStartPos);
                    //cout << " X = " << brickStartPos.x << "    Y = " << brickStartPos.y << endl;
                    brickStartPos.x -= 45;
                    brickStartPos.y += 35;
                }



                for (float i = 0; i < BrickPosition.size(); i++)
                {
                    Brick brick(1, BrickPosition[i]);
                    bricks.push_back(brick);
                }
            }

            if (gameLevel == 1) 
            {
                
                vector<sf::Vector2f> BrickPosition;
                sf::Vector2f brickStartPos = sf::Vector2f(37.5f, 75.f);
                brickCount = 12;
                areAllBrickDestroyed = false;

                for (float i = 0; i < 7; i++)
                {
                    BrickPosition.push_back(brickStartPos);
                    //cout << " X = " << brickStartPos.x << "    Y = " << brickStartPos.y << endl;
                    brickStartPos.x += 105;                    
                }

                brickStartPos = Vector2f(142.5f, 200);

                for (float i = 0; i < 5; i++)
                {
                    BrickPosition.push_back(brickStartPos);
                    //cout << " X = " << brickStartPos.x << "    Y = " << brickStartPos.y << endl;
                    brickStartPos.x += 105;
                }



                for (float i = 0; i < BrickPosition.size(); i++)
                {
                    Brick brick(1, BrickPosition[i]);
                    brick.numberOfHitsTakenToDestroy = 3;
                    brick.color = Color::Red;
                    bricks.push_back(brick);
                }
            }

            if (gameLevel == 2)
            {

                vector<sf::Vector2f> BrickPosition;
                sf::Vector2f brickStartPos = sf::Vector2f(600, 100.f);
                brickCount = 12;
                areAllBrickDestroyed = false;

                for (float i = 0; i < 6; i++)
                {
                    BrickPosition.push_back(brickStartPos);
                    //cout << " X = " << brickStartPos.x << "    Y = " << brickStartPos.y << endl;
                    brickStartPos.x -= 50;
                    brickStartPos.y += 50;
                }

                brickStartPos = Vector2f(100, 100);

                for (float i = 0; i < 6; i++)
                {
                    BrickPosition.push_back(brickStartPos);
                    //cout << " X = " << brickStartPos.x << "    Y = " << brickStartPos.y << endl;
                    brickStartPos.x += 50;
                    brickStartPos.y += 50;
                }



                for (float i = 0; i < BrickPosition.size(); i++)
                {
                    Brick brick(1, BrickPosition[i]);
                    bricks.push_back(brick);
                }
            }


            areAllBrickDestroyed = false;
        }

#pragma endregion


#pragma region WindowReset
        window.clear();
        window.draw(paddle.paddle);
        window.draw(mainBall.ball);
        for (int i = 0; i < bricks.size(); i++) 
        {
            if (!bricks[i].isDead)
            {
                bricks[i].brick.setTexture(&bricks[i].texture);
                window.draw(bricks[i].brick);
            }
            
        }

        if (powerUpSpawned) 
        {
            window.draw(powerUp.powerUp);
        }

        if (powerUp.powerUpCollected && powerUpCollected) 
        {
            window.draw(powerUp.bullet);
        }


        window.draw(mainBall.numberOfLivesText);
        window.draw(mainBall.playerScoreText);

        window.draw(mainBall.ballSprite);
        window.display();
#pragma endregion
    }
    return 0;

}