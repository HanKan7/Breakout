#include"Paddle.h"
#include"Brick.h"
using namespace std;



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "BREAKOUT!");
    window.setVerticalSyncEnabled(true);
    Clock clock;
    int gameLevel = 0;

    Paddle paddle;
    Ball mainBall;
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
    int brickCount;
#pragma region BrickInit
    
    if (gameLevel == 0)
    {
        vector<sf::Vector2f> BrickPosition;
        sf::Vector2f brickStartPos = sf::Vector2f(620.f, 75.f);
        brickCount = 2;
        areAllBrickDestroyed = false;

        for (float i = 0; i < brickCount; i++)
        {
            BrickPosition.push_back(brickStartPos);
            cout << " X = " << brickStartPos.x << "    Y = " << brickStartPos.y << endl;
            brickStartPos.x -= 45;
            brickStartPos.y += 45;
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
        //
        //#pragma region ViewPort
        //        /*sf::View view;
        //        auto windowSize = window.getSize();
        //        view.reset(sf::FloatRect(0.0f, 0.0f, windowSize.x, windowSize.y));
        //        window.setView(view);*/
        //#pragma endregion
        //




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
        //        if (humanVsHuman == 1)
        //        {
        //            leftPlayer.Movement(&leftPlayer.paddle, false, 10.5f, false);
        //        }
        //        if (fourPlayerMode == 1)
        //        {
        //            smallLeftPlayer.Movement(&smallLeftPlayer.paddle, false, 12.5f, true);
        //            smallRightPlayer.Movement(&smallRightPlayer.paddle, true, 12.5, true);
        //        }
        //
        //        if (blockInTheMiddle == 1)
        //        {
        //            wallLeft.WallMovement(5);
        //            wallRight.WallMovement(5);
        //        }
        //
#pragma endregion
//
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
        //paddle.CollisionCheckWithBall(&mainBall);
        mainBall.CollisionWithPaddle(&paddle.paddle, mainBall.hasLaunchedTheBall);

        for (int i = 0; i < bricks.size(); i++) 
        {
            mainBall.CollisionWithBrick(&bricks[i]);
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
//
//#pragma region PowerUp
//        if (!powerUpSpawned)
//        {
//            power.SpawnPowerUp();
//            powerUpSpawned = true;
//        }
//        if (!clockValueTaken)
//        {
//            clockValue = powerUpClock.getElapsedTime().asSeconds();
//            clockValueTaken = true;
//        }
//        if (powerUpSpawned && powerUpClock.getElapsedTime().asSeconds() >= clockValue + 5)
//        {
//            power.SpawnPowerUp();
//            clockValueTaken = false;
//        }
//#pragma endregion
//
//
//#pragma region AiPaddleClamp
//        if (humanVsHuman == 2)
//        {
//            sf::Vector2f BallPosMinusAiPos = mainBall.ball.getPosition() - leftPlayer.paddle.getPosition();
//            leftPlayer.AiMovement(&leftPlayer.paddle, BallPosMinusAiPos, 0.15f);
//            leftPlayer.Clamp(&leftPlayer.paddle);
//        }
//
//
//#pragma endregion
//
// 
        if (mainBall.numberOfLives <= 0) 
        {

        }
#pragma region GameHasEnded
        bool didGameRestart = false;
        if (mainBall.numberOfLives <= 0) 
        {
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
                    mainBall.numberOfLivesText.setString("Number Of Lives = " + to_string(mainBall.numberOfLives));
                    mainBall.playerScore = 0;
                    mainBall.playerScoreText.setString("SCORE = " + to_string(mainBall.playerScore));
                    gameLevel = 1;
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
            mainBall.ResetBallWithMoreSpeed(didGameRestart);
            didGameRestart = false;
            /*for (int i = 0; i < bricks.size(); i++) {
                bricks[i].isDead = false;
            }*/
            gameLevel = (gameLevel + 1) % 2;
            bricks.clear();

            if (gameLevel == 0)
            {
                vector<sf::Vector2f> BrickPosition;
                sf::Vector2f brickStartPos = sf::Vector2f(620.f, 75.f);
                brickCount = 2;
                areAllBrickDestroyed = false;

                for (float i = 0; i < brickCount; i++)
                {
                    BrickPosition.push_back(brickStartPos);
                    cout << " X = " << brickStartPos.x << "    Y = " << brickStartPos.y << endl;
                    brickStartPos.x -= 45;
                    brickStartPos.y += 45;
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
                brickCount = 7;
                areAllBrickDestroyed = false;

                for (float i = 0; i < brickCount; i++)
                {
                    BrickPosition.push_back(brickStartPos);
                    cout << " X = " << brickStartPos.x << "    Y = " << brickStartPos.y << endl;
                    brickStartPos.x += 105;                    
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
            if(!bricks[i].isDead)
            window.draw(bricks[i].brick);
        }
        window.draw(mainBall.numberOfLivesText);
        window.draw(mainBall.playerScoreText);
        window.display();
#pragma endregion
    }
    return 0;

}