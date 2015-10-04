#include "apple.h"


void appleInit(Apple * apple)
{
	appleDraw(apple);
	apple->sprite.setPosition(apple->xPos, apple->yPos);
	apple->image.loadFromFile("images/apple.png");
	apple->texture.loadFromImage(apple->image);
	apple->sprite.setTexture(apple->texture);
	apple->sprite.setTextureRect(IntRect(0, 0, 19, 19));
}

void appleDraw(Apple * apple)
{
	apple->xPos = (rand() % MAP_WIDTH) * 19.f;
	apple->yPos = (rand() % MAP_HEIGHT) * 19.f;
	while (TileMap[(int)(apple->yPos / 19)][(int)(apple->xPos / 19)] != ' ')
	{
		apple->xPos = (rand() % MAP_WIDTH) * 19.f;
		apple->yPos = (rand() % MAP_HEIGHT) * 19.f;
	}
}
