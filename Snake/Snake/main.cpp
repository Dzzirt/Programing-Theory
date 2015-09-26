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

void MapDraw()
{
}

int main()
{
	RenderWindow window(VideoMode(380, 190), "SFML works!");
	Clock clock;
	Map map;
	Apple apple;
	SnakeParts parts[50];
	int partCount = 0, missmatch = 0;
	float timeCounter = 0;
	parts[0].xPos = 0;
	parts[0].yPos = 0;
	parts[0].sprite.setPosition(0, 0);
	parts[0].draw = true;


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timeCounter += time;


		//printf("%f\n", timeCounter);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			parts[0].dir = 3;
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			parts[0].dir = 2;
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			parts[0].dir = 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			parts[0].dir = 0;
		}

		if (timeCounter > 0.1)
		{
			timeCounter -= 0.1;
			parts[0].Store();
			parts[0].update();
			for (int i = 1; i < 50; i++)
			{
				if (parts[i].draw == 1)
				{
					parts[i].Store();
					parts[i].xPos = parts[i - 1].xStore;
					parts[i].yPos = parts[i - 1].yStore;
					parts[i].sprite.setPosition(parts[i].xPos, parts[i].yPos);
				}
			}
			if (apple.xPos == parts[0].xPos && apple.yPos == parts[0].yPos)
			{
				partCount++;
				int partsDrawCounter = 0;
				for (int i = 0; i < 50; i++)
				{
					if (parts[i].draw == true)
					{
						partsDrawCounter++;
					}
				}
				bool safe = true;

				// We make sure that it doesn't spawn on the snake
				do
				{
					apple.draw();
					for (int i = 0; i < partsDrawCounter; i++)
					{
						if (parts[i].xPos == apple.xPos && parts[i].yPos == apple.yPos)
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

				parts[partCount].draw = true;
				parts[partCount].sprite.setPosition(parts[partCount - 1].xStore, parts[partCount - 1].yStore);
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
			if (parts[i].draw == true)
			{
				window.draw(parts[i].sprite);
			}
		}

		//Apple draw

		window.draw(apple.sprite);

		window.display();
	}

	return 0;
}
