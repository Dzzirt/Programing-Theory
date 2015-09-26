#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "map.h"
using namespace sf;


struct SnakeParts
{
	int xPos = 0, yPos = 0, xStore, yStore;
	int dir = 0;
	bool draw = false;
	String fileName;
	Image image;
	Texture texture;
	Sprite sprite;

	SnakeParts()
	{
		image.loadFromFile("images/snakePart.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 19, 19));
	}

	void Store()
	{
		xStore = xPos;
		yStore = yPos;
	}

	void update()
	{
		Store();
		switch (dir)
		{
		case 0: sprite.move(19, 0);
			xPos += 19;
			break;
		case 1: sprite.move(-19, 0);
			xPos -= 19;
			break;
		case 2: sprite.move(0, 19);
			yPos += 19;
			break;
		case 3: sprite.move(0, -19);
			yPos -= 19;
			break;
		}
	}
};

struct Apple
{
	int xPos, yPos;
	String fileName;
	Image image;
	Texture texture;
	Sprite sprite;

	Apple()
	{
		draw();
		sprite.setPosition(xPos, yPos);
		image.loadFromFile("images/apple.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 19, 19));
	}

	void draw()
	{
		xPos = (rand() % MAP_WIDTH) * 19;
		yPos = (rand() % MAP_HEIGHT) * 19;
		printf("%d  %d \n", xPos, yPos);
		while (TileMap[yPos / 19][xPos / 19] != ' ')
		{
			xPos = (rand() % MAP_WIDTH) * 19;
			yPos = (rand() % MAP_HEIGHT) * 19;
		}
	}
};

struct Map
{
	Image image;
	Texture texture;
	Sprite sprite;

	Map()
	{
		image.loadFromFile("images/map.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};

int main()
{
	RenderWindow window(VideoMode(380, 190), "Snake");
	Clock clock;
	Map map;
	Apple apple;
	SnakeParts snake[50];
	int partCount = 0;
	float timeCounter = 0;
	snake[0].xPos = 0;
	snake[0].yPos = 0;
	snake[0].sprite.setPosition(0, 0);
	snake[0].draw = true;


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

		if (Keyboard::isKeyPressed(Keyboard::W) && snake[0].dir != 2)
		{
			snake[0].dir = 3;
		}

		if (Keyboard::isKeyPressed(Keyboard::S) && snake[0].dir != 3)
		{
			snake[0].dir = 2;
		}

		if (Keyboard::isKeyPressed(Keyboard::A) && snake[0].dir != 0)
		{
			snake[0].dir = 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::D) && snake[0].dir != 1)
		{
			snake[0].dir = 0;
		}

		if (timeCounter > 0.1)
		{
			timeCounter -= 0.1;

			//Snake movement

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
				snake[0].xPos = (MAP_WIDTH - 1)  * 19;
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

			//Interact with Apple

			if (apple.xPos == snake[0].xPos && apple.yPos == snake[0].yPos)
			{
				partCount++;
				int snakeDrawCounter = 0;
				for (int i = 0; i < 50; i++)
				{
					if (snake[i].draw == true)
					{
						snakeDrawCounter++;
					}
				}

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

				snake[partCount].draw = true;
				snake[partCount].sprite.setPosition(snake[partCount - 1].xStore, snake[partCount - 1].yStore);
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

	return 0;
}
