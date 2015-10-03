#include "methods.h"
#include "Headers.h"


std::string toString(int val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

void reinitAll()
{
	map = new Map();
	apple = new Apple();
	snake = new SnakeParts[50];
	headInit();
	score = 0;
	timeCounter = 0.f;
	speed = 0.2f;
}

void deleteAll()
{
	delete apple;
	delete map;
	delete[] snake;
}

void appleSpawn(int snakeDrawCounter, Apple& apple)
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
			safe = true;
		}
	}
	while (safe != true);

	apple.sprite.setPosition(apple.xPos, apple.yPos);
}

void eatApple(int snakeDrawCounter)
{
	score += 9;
	speed -= 0.005f;
	snake[snakeDrawCounter].draw = true;
	snake[snakeDrawCounter].sprite.setPosition(snake[snakeDrawCounter - 1].xStore, snake[snakeDrawCounter - 1].yStore);
}

int snakeLength()
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

void step()
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
	else snake[0].update();

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

void processEvents(RenderWindow& window)
{
	Event event;
	while (window.pollEvent(event))
	{
		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::W) && snake[0].dir != 2)
		{
			snake[0].dir = 3;
		}
		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::S) && snake[0].dir != 3)
		{
			snake[0].dir = 2;
		}
		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::A) && snake[0].dir != 0)
		{
			snake[0].dir = 1;
		}
		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::D) && snake[0].dir != 1)
		{
			snake[0].dir = 0;
		}

		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::P))
		{
			state = PAUSE;
		}
		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::U))
		{
			state = PLAY;
		}
		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::R) && state == ENDGAME)
		{
			state = PLAY;
			deleteAll();
			reinitAll();
		}
		if (event.type == Event::Closed || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape) && state == ENDGAME))
			window.close();
	}
	/*if (Keyboard::isKeyPressed(Keyboard::W) && snake[0].dir != 2)
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
	}*/
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

void render(RenderWindow& window)
{
	window.clear();

	//Map draw

	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (TileMap[i][j] == ' ') map->sprite.setTextureRect(IntRect(0, 0, 19, 19));
			if (TileMap[i][j] == '1') map->sprite.setTextureRect(IntRect(19, 0, 19, 19));
			map->sprite.setPosition(j * 19.f, i * 19.f);
			window.draw(map->sprite);
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

	window.draw(apple->sprite);
}

void gameStart()
{
	RenderWindow window(VideoMode(380, 190), "Snake");
	Clock clock;
	while (window.isOpen()) //разбить на 3 метода
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timeCounter += time;

		processEvents(window);

		if (state == STARTGAME)
		{
			window.clear();
			title.setString("       Snake!\nPress 'U' to start!");
			title.setPosition(4, 10);
			window.draw(title);
			window.display();
		}

		if (state == PAUSE)
		{
			window.clear();

			//Map draw

			render(window);

			title.setString("Pause");
			title.setPosition(122, 50);
			window.draw(title);
			window.display();
		}

		if (state == PLAY)
		{
			if (timeCounter > speed)
			{
				timeCounter = 0;

				//Snake movement

				step();

				int snakeDrawCounter = snakeLength();

				//Collision with Walls

				try
				{
					if (TileMap[(int)(snake[0].yPos / 19)][(int)(snake[0].xPos / 19)] == '1')
					{
						state = ENDGAME;
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
						state = ENDGAME;
					}
				}


				//Interact with Apple

				if (apple->xPos == snake[0].xPos && apple->yPos == snake[0].yPos)
				{
					eatApple(snakeDrawCounter);
					appleSpawn(snakeDrawCounter, *apple);
				}
			}
			render(window);
			window.display();
		}

		if (state == ENDGAME)
		{
			window.clear();
			text.setString(" Score: " + toString(score) + "\n Press 'Esc' to exit\n Press 'R' to restart");
			text.setPosition(14, 28);
			window.draw(text);
			window.display();
		}
	}
	deleteAll();
}
