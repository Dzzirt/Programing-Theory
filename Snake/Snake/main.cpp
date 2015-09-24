#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "map.h"
using namespace sf;


struct SnakeParts
{
	float xPos, yPos, dx = 0, dy = 0;
	float dxInt = 0, dyInt = 0;
	String fileName;
	Image image;
	Texture texture;
	Sprite sprite;
	int dir = 0;
	bool draw;
	float speed = 0.1;

	SnakeParts()
	{
		image.loadFromFile("images/snakePart.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 19, 19));
	}

	void update()
	{
		switch (dir)
		{
		case 0:	sprite.move(19, 0);
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
	float xPos, yPos;
	String fileName;
	Image image;
	Texture texture;
	Sprite sprite;

	Apple()
	{
		xPos = (rand() % MAP_WIDTH) * 19;
		yPos = (rand() % MAP_HEIGHT) * 19;
		image.loadFromFile("images/apple.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 19, 19));
		sprite.setPosition(xPos, yPos);
	}
};

int main()
{
	Clock clock;
	RenderWindow window(VideoMode(380, 380), "SFML works!");
	struct SnakeParts parts[50];
	int potentialX = 0;
	int potentialY = 0;
	float timeCounter = 0;
	int partCount = 0;
	parts[0].xPos = 0;
	parts[0].yPos = 0;
	parts[0].sprite.setPosition(0, 0);
	parts[0].draw = true;
	Apple apple;
	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timeCounter += time;


		printf("%f\n", timeCounter);
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
			potentialX = parts[partCount].xPos;
			potentialY = parts[partCount].yPos;
			parts[partCount].update();
			timeCounter -= 0.1;
			if(apple.xPos == parts[0].xPos && apple.yPos == parts[0].yPos)
			{
				partCount++;
				apple.xPos = (rand() % MAP_WIDTH) * 19;
				apple.yPos = (rand() % MAP_HEIGHT) * 19;
				apple.sprite.setPosition(apple.xPos, apple.yPos);
				parts[partCount].xPos = potentialX;
				parts[partCount].yPos = potentialY;
				parts[partCount].sprite.setPosition(parts[partCount].xPos, parts[partCount].yPos);
				parts[partCount].draw = 1;
				
			}
		}

		window.clear();
		for (int i = 0; i < MAP_HEIGHT; i++)
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 19, 19));
				s_map.setPosition(j * 19, i * 19);
				window.draw(s_map);
			}
		for (int i = 0; i < 50; ++i)
		{
			if (parts[i].draw == true)
			{
				window.draw(parts[i].sprite);
			}
		}
		window.draw(apple.sprite);

		window.display();
	}

	return 0;
}
