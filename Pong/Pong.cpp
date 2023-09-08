#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<cmath>
using namespace sf;
using namespace std;

int main()
{
	srand(time(NULL));
	const float pi = 3.14159f;
	RenderWindow window;
	window.create(VideoMode(800.f, 600.f), "Pong", Style::Default);

	RectangleShape leftPaddle, rightPaddle;
	Vector2u windowSize = window.getSize();
	long long screenWidth = windowSize.x;
	long long screenHeight = windowSize.y;
	long long edge = screenWidth / 20;

	//create LeftPaddle
	long long PaddleWidth = 8.f;
	long long PaddleHeight = 100.f;
	long long PaddleOutlineThickness = 0.f;
	//////////////////////////////////////////
	leftPaddle.setSize(Vector2f(PaddleWidth, PaddleHeight));
	leftPaddle.setFillColor(Color::White);
	leftPaddle.setOutlineThickness(PaddleOutlineThickness);
	leftPaddle.setOutlineColor(Color(0, 0, 0));
	leftPaddle.setPosition(PaddleOutlineThickness + edge, screenHeight / 2 - PaddleHeight / 2);

	//create RightPaddle
	rightPaddle.setSize(Vector2f(PaddleWidth, PaddleHeight));
	rightPaddle.setFillColor(Color::White);
	rightPaddle.setOutlineThickness(PaddleOutlineThickness);
	rightPaddle.setOutlineColor(Color(0, 0, 0));
	rightPaddle.setPosition(screenWidth - PaddleWidth - PaddleOutlineThickness - edge, screenHeight / 2 - PaddleHeight / 2);


	//create a ball
	CircleShape ball;
	long long ballRadius = PaddleWidth / 0.85;
	ball.setRadius(ballRadius);
	ball.setFillColor(Color::White);
	ball.setOutlineThickness(PaddleOutlineThickness);
	ball.setOutlineColor(Color::Black);
	ball.setPosition(screenWidth / 2, screenHeight / 2);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
	//define paddle properties
	float paddleSpeed = 500.f;

	//define ball properities
	float ballSpeed = 500.f;
	float angleBall = -90.f; //changed

	//Create Bot-Bot Properties
	int botTarget = screenHeight / 2;
	float botPeriod = 0.0001f;
	float botTimer1 = 0.f, botTimer2 = 0.f;


	//LoadFont
	Font font;
	if (!font.loadFromFile("D:/GameC++/Pong/Freedom-10eM.TTF")) return EXIT_FAILURE;
	//Init pauseMessage
	Text message1;
	message1.setFont(font);
	message1.setPosition(screenWidth / 2 - edge, screenHeight / 2 - edge);
	message1.setFillColor(Color::White);
	message1.setCharacterSize(40);
	message1.setString("PONG \n");
	Text message2;
	message2.setFont(font);
	message2.setPosition(screenWidth / 2 - edge * 5, screenHeight / 2 + edge / 2);
	message2.setFillColor(Color::White);
	message2.setCharacterSize(28);
	message2.setString("Press SpaceBar to play... \n");

	///////////////////////////////////
	Clock clock;
	float deltaTime = 0.f;
	///////////////////////////////////

	//GameState
	bool isPlayed = false;


	//Sound
	SoundBuffer ballsoundload;
	ballsoundload.loadFromFile("D:/GameC++/Pong/ball_sfx.wav");
	Sound ballsound;
	ballsound.setBuffer(ballsoundload);

	//GameLoop
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		if (!isPlayed && Keyboard::isKeyPressed(Keyboard::Space))
		{
			ball.setPosition(screenWidth / 2, screenHeight / 2);
			rightPaddle.setPosition(screenWidth - PaddleWidth - PaddleOutlineThickness - edge, screenHeight / 2 - PaddleHeight / 2);
			leftPaddle.setPosition(PaddleOutlineThickness + edge, screenHeight / 2 - PaddleHeight / 2);
			do
			{
				angleBall = rand() % 360;
			} while (angleBall < 15 || angleBall > 165 && angleBall < 195 || angleBall > 345);

			isPlayed = true;
		}
		if (isPlayed)
		{
			//leftPaddleMovement
			//Vector2f pos1 = leftPaddle.getPosition();
			//if (Keyboard::isKeyPressed(Keyboard::S))
			//{
				//if (pos1.y + paddleSpeed * deltaTime >= screenHeight - PaddleHeight - PaddleOutlineThickness)
				//	leftPaddle.setPosition(pos1.x, screenHeight - PaddleHeight - PaddleOutlineThickness);
				//else
					//leftPaddle.move(0, paddleSpeed * deltaTime);
			//}
			//else
				//if (Keyboard::isKeyPressed(Keyboard::W))
				//{
					//if (pos1.y - paddleSpeed * deltaTime < PaddleOutlineThickness + edge/4)
					//	leftPaddle.setPosition(pos1.x, PaddleOutlineThickness + edge/4);
				//	else
					//	leftPaddle.move(0, -paddleSpeed * deltaTime);
		//	}


			//rightPaddleMovement
		//	Vector2f pos2 = rightPaddle.getPosition();
		//	if (Keyboard::isKeyPressed(Keyboard::Up))
		//	{
			//	if (pos2.y - paddleSpeed * deltaTime < PaddleOutlineThickness + edge/4)
			//		rightPaddle.setPosition(pos2.x, PaddleOutlineThickness + edge/4);
			//	else
			//		rightPaddle.move(0, - paddleSpeed * deltaTime);
			//}

			//else if (Keyboard::isKeyPressed(Keyboard::Down))
		//	{
			//	if (pos2.y + paddleSpeed * deltaTime > screenHeight - PaddleHeight - PaddleOutlineThickness)
			//		rightPaddle.setPosition(pos2.x, screenHeight - PaddleHeight - PaddleOutlineThickness);
			//	else
				//	rightPaddle.move(0, paddleSpeed * deltaTime);
		//	}

			//leftPaddle_Bot
			botTimer1 += deltaTime;
			if (botTimer1 > botPeriod)
			{
				if (-sin(angleBall * pi / 180) > 0.f) //ball moving toward bot
				{
					botTarget = ball.getPosition().y;
					botTimer1 = 0.f;
				}
			}

			if (leftPaddle.getPosition().y + 3 * PaddleHeight / 4 <= botTarget) //moving down
			{
				Vector2f pos1 = leftPaddle.getPosition();
				if (pos1.y + PaddleHeight + paddleSpeed * deltaTime >= screenHeight - edge / 4)
					leftPaddle.setPosition(pos1.x, screenHeight - PaddleHeight - edge / 4);
				else
					leftPaddle.move(0, paddleSpeed * deltaTime);
			}
			else if (leftPaddle.getPosition().y + PaddleHeight / 4 > botTarget) //moving up
			{
				Vector2f pos1 = leftPaddle.getPosition();
				if (pos1.y - paddleSpeed * deltaTime <= edge / 4)
					leftPaddle.setPosition(pos1.x, edge / 4);
				else
					leftPaddle.move(0, -paddleSpeed * deltaTime);
			}

			botTimer2 += deltaTime;
			if (botTimer2 >= botPeriod)
			{
				if (sin(angleBall * pi / 180) > 0.f) //ball moving toward bot
				{
					botTarget = ball.getPosition().y;
					botTimer2 = 0.f;
				}
			}
			if (rightPaddle.getPosition().y + 3 * PaddleHeight / 4 <= botTarget) //moving down
			{
				Vector2f pos2 = rightPaddle.getPosition();
				if (pos2.y + PaddleHeight + paddleSpeed * deltaTime >= screenHeight - edge / 4)
					rightPaddle.setPosition(pos2.x, screenHeight - PaddleHeight - edge / 4);
				else
					rightPaddle.move(0, paddleSpeed * deltaTime);
			}
			else if (rightPaddle.getPosition().y + PaddleHeight / 4 > botTarget) //moving up
			{
				Vector2f pos2 = rightPaddle.getPosition();
				if (pos2.y - paddleSpeed * deltaTime <= edge / 4)
					rightPaddle.setPosition(pos2.x, edge / 4);
				else
					rightPaddle.move(0, -paddleSpeed * deltaTime);
			}





			//Ball Movement
			float factor = ballSpeed * deltaTime;
			//angleBall can be changed suring the game
			ball.move(sin(angleBall * pi / 180) * factor, cos(angleBall * pi / 180) * factor);

			//Check Interact Ball-Screen
			if (ball.getPosition().y - ballSpeed * deltaTime <= ballRadius + edge / 4
				|| ball.getPosition().y + ballSpeed * deltaTime >= screenHeight - ballRadius - edge / 4)
			{
				angleBall = 180.f - angleBall;
			}

			//Check Interact Ball-Paddles

			Vector2f leftPadpos = leftPaddle.getPosition();
			Vector2f ballpos = ball.getPosition();
			long long padWidth = PaddleWidth, padHeight = PaddleHeight;
			long long mini = 1.f;
			//LeftPaddle
			if (ballpos.x >= leftPadpos.x + padWidth)
			{
				if (ballpos.x - ballRadius - mini <= leftPadpos.x + padWidth)
				{
					if (ballpos.y >= leftPadpos.y
						&& ballpos.y <= leftPadpos.y + padHeight)
					{
						angleBall = 360.f - angleBall + rand() % 12 - 12;
						ballsound.play();
					}
					else if (ballpos.y <= leftPadpos.y && ballpos.y + ballRadius >= leftPadpos.y)
					{
						angleBall = 360 - angleBall + rand() % 30 - 30;
						ballsound.play();
					}
					else if (ballpos.y >= leftPadpos.y + padHeight && ballpos.y - ballRadius <= leftPadpos.y + padHeight)
					{
						angleBall = 360 - angleBall + rand() % 30 - 30;
						ballsound.play();
					}
					ballSpeed = ballSpeed * 1.009f;
					paddleSpeed = paddleSpeed * 1.009f;
				}
			}

			else if (ballpos.x <= leftPadpos.x + padWidth && ballpos.x >= leftPadpos.x)
			{
				if (ballpos.y + ballRadius <= leftPadpos.y)
				{
					if (ballpos.y + ballRadius + mini >= leftPadpos.y)
					{
						angleBall = 360 - angleBall + rand() % 12 - 12;
						ballsound.play();
					}
					ballSpeed = ballSpeed * 1.009f;
					paddleSpeed = paddleSpeed * 1.009f;
				}
				else if (ballpos.y - ballRadius >= leftPadpos.y + padHeight)
				{
					if (ballpos.y - ballRadius - mini <= leftPadpos.y + padHeight)
					{
						angleBall = 360 - angleBall + rand() % 12 - 12;
						ballsound.play();
					}
					ballSpeed = ballSpeed * 1.009f;
					paddleSpeed = paddleSpeed * 1.009f;
				}
			}

			//RightPaddle
			Vector2f rightPadpos = rightPaddle.getPosition();
			if (ballpos.x <= rightPadpos.x)
			{
				if (ballpos.x + ballRadius + mini >= rightPadpos.x)
				{
					if (ballpos.y >= rightPadpos.y
						&& ballpos.y <= rightPadpos.y + padHeight)
					{
						angleBall = 360.f - angleBall + rand() % 12 - 12;
						ballsound.play();
					}
					else if (ballpos.y <= rightPadpos.y && ballpos.y + ballRadius >= rightPadpos.y)
					{
						angleBall = 360 - angleBall + rand() % 30 - 30;
						ballsound.play();
					}
					else if (ballpos.y >= rightPadpos.y + padHeight && ballpos.y - ballRadius <= rightPadpos.y + padHeight)
					{
						angleBall = 360 - angleBall + rand() % 30 - 30;
						ballsound.play();
					}
					ballSpeed = ballSpeed * 1.009f;
					paddleSpeed = paddleSpeed * 1.009f;
				}
			}

			else if (ballpos.x <= rightPadpos.x + padWidth && ballpos.x >= rightPadpos.x)
			{
				if (ballpos.y + ballRadius <= rightPadpos.y)
				{
					if (ballpos.y + ballRadius + mini >= rightPadpos.y)
					{
						angleBall = 360 - angleBall + rand() % 12 - 12;
						ballsound.play();
					}
					ballSpeed = ballSpeed * 1.009f;
					paddleSpeed = paddleSpeed * 1.009f;
				}
				else if (ballpos.y - ballRadius >= rightPadpos.y + padHeight)
				{
					if (ballpos.y - ballRadius - mini <= rightPadpos.y + padHeight)
					{
						angleBall = 360 - angleBall + rand() % 12 - 12;
						ballsound.play();
					}
					ballSpeed = ballSpeed * 1.009f;
					paddleSpeed = paddleSpeed * 1.009f;
				}
			}


			if (ball.getPosition().x <= 0)
			{
				message1.setPosition(screenWidth / 2 - edge * 4, screenHeight / 2 - edge);
				message1.setFillColor(Color::White);
				message1.setCharacterSize(32);
				message1.setString("Right Player Win!");
				message2.setString("Press SpaceBar to playe again ...");
				message2.setPosition(screenWidth / 2 - edge * 6.5, screenHeight / 2 + edge / 2);
				isPlayed = false;
				paddleSpeed = 500.f;
				ballSpeed = 500.f;
			}
			else if (ball.getPosition().x >= screenWidth)
			{
				message1.setPosition(screenWidth / 2 - edge * 4, screenHeight / 2 - edge);
				message1.setFillColor(Color::White);
				message1.setCharacterSize(32);
				message1.setString("Left PLayer Win!");
				message2.setString("Press SpaceBar to playe again ...");
				message2.setPosition(screenWidth / 2 - edge * 6.5, screenHeight / 2 + edge / 2);
				isPlayed = false;
				paddleSpeed = 500.f;
				ballSpeed = 500.f;
			}

		}

		window.clear(Color::Black);
		if (isPlayed)
		{
			window.draw(leftPaddle);
			window.draw(rightPaddle);
			window.draw(ball);
		}
		else
		{
			window.draw(message1);
			window.draw(message2);
		}
		window.display();
	}

	return 0;
}
