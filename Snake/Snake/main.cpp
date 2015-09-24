#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "map.h"
using namespace sf;


struct SnakeParts
{
	float xPos, yPos, dx = 0, dy = 0;
	int dir = 0;
	bool draw;
	String fileName;
	Image image;
	Texture texture;
	Sprite sprite;
	int predX = 0;
	int predY = 0;
	int predDir;
	
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
			predX = xPos;
			predY = yPos;
			xPos += 19;
			break;
		case 1: sprite.move(-19, 0);
			predX = xPos;
			predY = yPos;
			xPos -= 19;
			break;
		case 2: sprite.move(0, 19);
			predY = yPos;
			predX = xPos;
			yPos += 19;
			break;
		case 3: sprite.move(0, -19);
			predY = yPos;
			predX = xPos;
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
	RenderWindow window(VideoMode(380, 380), "SFML works!");
	Clock clock;
	Map map;
	Apple apple;
	SnakeParts parts[50];
	int potentialX, potentialY, potentialDir, partCount = 0;
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


		printf("%f\n", timeCounter);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			parts[0].predDir = parts[0].dir;
			parts[0].dir = 3;
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			parts[0].predDir = parts[0].dir;
			parts[0].dir = 2;
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			parts[0].predDir = parts[0].dir;
			parts[0].dir = 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			parts[0].predDir = parts[0].dir;
			parts[0].dir = 0;
		}

		if (timeCounter > 0.2)
		{
			potentialX = parts[partCount].xPos; // потенц Х след части змейки
			potentialY = parts[partCount].yPos; // потенц У след части змейки
			potentialDir = parts[partCount].dir; // потенц Направление 
			timeCounter -= 0.2;
			
			for (int partCount = 1; partCount < 50; partCount++)
			{
				parts[partCount].xPos = parts[partCount - 1].predX;
				parts[partCount].yPos = parts[partCount - 1].predY;
				//parts[partCount].dir = parts[partCount - 1].predDir;
				parts[partCount].sprite.setPosition(parts[partCount].xPos, parts[partCount].yPos);
				//parts[partCount].dir = parts[partCount - 1].dir;
			}
			parts[0].update();
			for (int i = 1; i < 50; i++)
			{
				if (i > 1 && parts[i].dir != parts[i].predDir)
				{
					parts[i].dir = parts[i].predDir;
				}
				//else parts[i].dir = parts[i - 1].dir;
				parts[i].update();
				
			}
			
			if(apple.xPos == parts[0].xPos && apple.yPos == parts[0].yPos)
			{
				partCount++;
				apple.xPos = (rand() % MAP_WIDTH) * 19;
				apple.yPos = (rand() % MAP_HEIGHT) * 19;
				apple.sprite.setPosition(apple.xPos, apple.yPos);
				parts[partCount].xPos = potentialX;
				parts[partCount].yPos = potentialY;
				parts[partCount].sprite.setPosition(parts[partCount].xPos, parts[partCount].yPos);
				parts[partCount].dir = potentialDir;
				parts[partCount].draw = 1;
				
			}
			
			
		}

		window.clear();

		//MAP draw

		for (int i = 0; i < MAP_HEIGHT; i++)
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (TileMap[i][j] == ' ') map.sprite.setTextureRect(IntRect(0, 0, 19, 19));
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
