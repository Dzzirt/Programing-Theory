#include "structs.h"


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

struct Apple
{
	float xPos, yPos;
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
		xPos = (rand() % MAP_WIDTH) * 19.f;
		yPos = (rand() % MAP_HEIGHT) * 19.f;
		while (TileMap[(int)(yPos / 19)][xPos / 19] != ' ')
		{
			xPos = (rand() % MAP_WIDTH) * 19;
			yPos = (rand() % MAP_HEIGHT) * 19;
		}
	}
};
