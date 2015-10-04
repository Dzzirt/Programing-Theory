#include "SnakeParts.h"

void storeXY(SnakeParts * snake)
{
	snake->xStore = snake->xPos;
	snake->yStore = snake->yPos;
}

void snakeUpdate(SnakeParts * snake)
{
	storeXY(snake);

	switch (snake->dir)
	{
	case 0: snake->sprite.move(19, 0);
		snake->xPos += STEP;
		break;
	case 1: snake->sprite.move(-19, 0);
		snake->xPos -= STEP;
		break;
	case 2: snake->sprite.move(0, 19);
		snake->yPos += STEP;
		break;
	case 3: snake->sprite.move(0, -19);
		snake->yPos -= STEP;
		break;
	}
}

void snakeInit(SnakeParts * snake)
{
	for (size_t i = 0; i < ; i++)
	{
		(snake + i)->image.loadFromFile("images/snakePart.png");
		(snake + i)->texture.loadFromImage((snake + i)->image);
		(snake + i)->sprite.setTexture((snake + i)->texture);
		(snake + i)->sprite.setTextureRect(IntRect(0, 0, 19, 19));
	}
	
}