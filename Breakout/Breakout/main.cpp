#include"Paddle.h"
#include"Brick.h"
using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "BREAKOUT!");
    window.setVerticalSyncEnabled(true);
    Clock clock;


    Paddle paddle;
    Ball mainBall;

#pragma region BrickInit

    vector<sf::Vector2f> BrickPosition;
    sf::Vector2f brickStartPos = sf::Vector2f(620.f, 75.f);
    int brickCount = 1;
    bool areAllBrickDestroyed = false;

    for (float i = 0; i < brickCount; i++)
    {
        BrickPosition.push_back(brickStartPos);
        cout << " X = " << brickStartPos.x << "    Y = " << brickStartPos.y <<endl;
        brickStartPos.x -= 45;
        brickStartPos.y += 45;
    }

    vector<Brick> bricks;

    for (float i = 0; i < BrickPosition.size(); i++)
    {
        Brick brick(1, BrickPosition[i]);
        bricks.push_back(brick);
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
//#pragma region GameHasEnded
//        if (mainBall.player1Point >= 2 || mainBall.player2Point >= 2)
//        {
//            if (mainBall.player1Point >= 5)
//            {
//                cout << "RED HAS WON THE GAME!\n";
//                cout << "Do you want to restart the game? Press Space to continue the game. Press Q to quit the game \n";
//                message.setString("YOU   HAVE   WON   THE   GAME! \n Do you want to restart the game? \n Press    Space    to continue the game \n Press    Q    to quit the game \n");
//                bool playerHasEnteredTheInput = false;
//                while (!playerHasEnteredTheInput)
//                {
//                    window.clear();
//                    window.draw(message);
//                    window.display();
//                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
//                    {
//                        playerHasEnteredTheInput = true;
//                        mainBall.player1Point = 0;
//                        mainBall.player2Point = -1;
//                        mainBall.player1Score.setString("0");
//                        mainBall.player2Score.setString("0");
//                        paddle.paddle.setPosition(paddle.InitialPostion);
//                        paddle.paddle.setSize(sf::Vector2f(15.0f, 145.0f));
//                        leftPlayer.paddle.setSize(sf::Vector2f(15.0f, 145.0f));
//                        mainBall.ball.setPosition(mainBall.InitialPosition);
//                    }
//
//                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//                    {
//                        return 1;
//                    }
//                }
//                playerHasEnteredTheInput = false;
//                //ResetGame(&mainBall, &paddle);
//            }
//
//            if (mainBall.player2Point >= 5)
//            {
//                cout << "BLUE HAS WON THE GAME! \n";
//                cout << "Do you want to restart the game? Press Space to continue the game. Press Q to quit the game \n";
//                message.setString("BLUE WON  THE  GAME! \n Do you want to restart the game? \n Press    Space    to continue the game \n Press    Q    to quit the game \n");
//                bool playerHasEnteredTheInput = false;
//                while (!playerHasEnteredTheInput)
//                {
//                    window.clear();
//                    window.draw(message);
//                    window.display();
//                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
//                    {
//                        playerHasEnteredTheInput = true;
//                        mainBall.player1Point = 0;
//                        mainBall.player2Point = -1;
//                        mainBall.player1Score.setString("0");
//                        mainBall.player2Score.setString("0");
//                        paddle.paddle.setPosition(paddle.InitialPostion);
//                        paddle.paddle.setSize(sf::Vector2f(15.0f, 145.0f));
//                        leftPlayer.paddle.setSize(sf::Vector2f(15.0f, 145.0f));
//                        mainBall.ball.setPosition(mainBall.InitialPosition);
//                    }
//
//                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//                    {
//                        return 1;
//                    }
//                }
//                playerHasEnteredTheInput = false;
//                //ResetGame(&mainBall, &ai);
//            }
//        }
//
//
//
//#pragma endregion

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
            mainBall.ResetBallWithMoreSpeed();
            for (int i = 0; i < bricks.size(); i++) {
                bricks[i].isDead = false;
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
        window.display();
#pragma endregion
    }
    return 0;

}