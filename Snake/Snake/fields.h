#pragma once

#include "Headers.h"

void headInit();
void textInit();
void DirAndPauseByButton();
int SnakeLength();
void Step();
void EatApple();
void AppleSpawn();

Map map;
Apple apple;
SnakeParts snake[50];
Font font;
Text text("", font, 80);
Text title("", font, 50);

Color color(155, 89, 182);
std::ostringstream playerScoreString;
std::ostringstream titleMessage;
int score = 0;
int partCount = 0;
bool startGame = true;
float timeCounter = 0, speed = 0.2;
bool pause = true;


void AppleSpawn(int snakeDrawCounter)
{
	bool safe = true;
	do
	{
		apple.draw();
		for (int i = 0; i < snakeDrawCounter; i++)
		{
			if (snake[i].xPos == apple.xPos && snake[i].yPos == apple.yPos)
			{
				safe = false;
				break;
			}
			else
			{
				safe = true;
			}
		}
	} while (safe != true);

	apple.sprite.setPosition(apple.xPos, apple.yPos);
}

void EatApple()
{
	score += 9;
	speed -= 0.005;
	partCount++;
	snake[partCount].draw = true;
	snake[partCount].sprite.setPosition(snake[partCount - 1].xStore, snake[partCount - 1].yStore);
}

int SnakeLength()
{
	int snakeDrawCounter = 0;
	for (int i = 0; i < 50; i++)
	{
		if (snake[i].draw == true)
		{
			snakeDrawCounter++;
		}
	}
	return snakeDrawCounter;
}

void Step()
{
	snake[0].Store();

	if (snake[0].dir == 3 && snake[0].yPos == 0)
	{
		snake[0].yPos = (MAP_HEIGHT - 1) * 19;
		snake[0].sprite.setPosition(snake[0].xPos, snake[0].yPos);
	}
	else if (snake[0].dir == 2 && snake[0].yPos == (MAP_HEIGHT - 1) * 19)
	{
		snake[0].yPos = 0;
		snake[0].sprite.setPosition(snake[0].xPos, snake[0].yPos);
	}
	else if (snake[0].dir == 1 && snake[0].xPos == 0)
	{
		snake[0].xPos = (MAP_WIDTH - 1) * 19;
		snake[0].sprite.setPosition(snake[0].xPos, snake[0].yPos);
	}
	else if (snake[0].dir == 0 && snake[0].xPos == (MAP_WIDTH - 1) * 19)
	{
		snake[0].xPos = 0;
		snake[0].sprite.setPosition(snake[0].xPos, snake[0].yPos);
	}
	else snake->update();

	for (int i = 1; i < 50; i++)
	{
		if (snake[i].draw == 1)
		{
			snake[i].Store();
			snake[i].xPos = snake[i - 1].xStore;
			snake[i].yPos = snake[i - 1].yStore;
			snake[i].sprite.setPosition(snake[i].xPos, snake[i].yPos);
		}
	}
}

void DirAndPauseByButton()
{
	if (Keyboard::isKeyPressed(Keyboard::W) && snake[0].dir != 2)
	{
		snake[0].dir = 3;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S) && snake[0].dir != 3)
	{
		snake[0].dir = 2;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A) && snake[0].dir != 0)
	{
		snake[0].dir = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D) && snake[0].dir != 1)
	{
		snake[0].dir = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::P))
	{
		pause = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::U))
	{
		pause = false;
	}
}

void headInit()
{
	snake[0].xPos = 190;
	snake[0].yPos = 95;
	snake[0].sprite.setPosition(190, 95);
	snake[0].draw = true;
}

void textInit()
{
	font.loadFromFile("font/font.otf");
	text.setColor(color);
	title.setColor(color);
	title.setStyle(Text::Bold);
}

void GameStart()
{
	RenderWindow window(VideoMode(380, 190), "Snake");
	Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timeCounter += time;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		DirAndPauseByButton();


		if (!pause)
		{
			startGame = false;
			if (timeCounter > speed)
			{
				timeCounter = 0;

				//Snake movement

				Step();

				int snakeDrawCounter = SnakeLength();

				//Collision with Walls

				try
				{
					if (TileMap[snake[0].yPos / 19][snake[0].xPos / 19] == '1')
					{
						window.clear();
						playerScoreString << score;
						text.setString("Score: " + playerScoreString.str());
						text.setPosition(14, 28);
						window.draw(text);
						window.display();
						sleep(seconds(4));
						window.close();
					}
				}
				catch (...)
				{
				}

				//Collision with itself

				for (int i = 1; i < snakeDrawCounter; i++)
				{
					if (snake[i].xPos == snake[0].xPos && snake[i].yPos == snake[0].yPos)
					{
						window.clear();
						playerScoreString << score;
						text.setString("Score: " + playerScoreString.str());
						text.setPosition(14, 28);
						window.draw(text);
						window.display();
						sleep(seconds(4));
						window.close();
						break;
					}
				}



				//Interact with Apple

				if (apple.xPos == snake[0].xPos && apple.yPos == snake[0].yPos)
				{
					EatApple();
					AppleSpawn(snakeDrawCounter);
				}
			}
			window.clear();

			//Map draw

			for (int i = 0; i < MAP_HEIGHT; i++)
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (TileMap[i][j] == ' ') map.sprite.setTextureRect(IntRect(0, 0, 19, 19));
					if (TileMap[i][j] == '1') map.sprite.setTextureRect(IntRect(19, 0, 19, 19));
					map.sprite.setPosition(j * 19, i * 19);
					window.draw(map.sprite);
				}

			//Snake draw

			for (int i = 0; i < 50; ++i)
			{
				if (snake[i].draw == true)
				{
					window.draw(snake[i].sprite);
				}
			}

			//Apple draw

			window.draw(apple.sprite);

			window.display();
		}
		else
		{
			window.clear();

			//Map draw

			for (int i = 0; i < MAP_HEIGHT; i++)
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (TileMap[i][j] == ' ') map.sprite.setTextureRect(IntRect(0, 0, 19, 19));
					if (TileMap[i][j] == '1') map.sprite.setTextureRect(IntRect(19, 0, 19, 19));
					map.sprite.setPosition(j * 19, i * 19);
					window.draw(map.sprite);
				}
			if (startGame)
			{
				window.clear();
				title.setString("       Snake!\nPress 'U' to start!");
				title.setPosition(4, 10);
				window.draw(title);
			}
			else
			{
				title.setString("Pause");
				title.setPosition(122, 50);
				window.draw(title);
			}
			

			window.display();

		}
	}

}