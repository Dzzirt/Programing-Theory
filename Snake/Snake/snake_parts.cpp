#include "snake_parts.h"
#include "main_fields.h"

void StoreXY(SnakeParts* snake) {
	snake->x_store = snake->x_pos;
	snake->y_store = snake->y_pos;
}

void SnakeUpdate(SnakeParts* snake) {
	StoreXY(snake);

	switch (snake->dir) {
	case 0: snake->sprite.move((float)SpriteSize, 0);
		snake->x_pos += STEP;
		break;
	case 1: snake->sprite.move(-SpriteSize, 0);
		snake->x_pos -= STEP;
		break;
	case 2: snake->sprite.move(0, (float)SpriteSize);
		snake->y_pos += STEP;
		break;
	case 3: snake->sprite.move(0, -SpriteSize);
		snake->y_pos -= STEP;
		break;
	}
}

void SnakeInit(SnakeParts* snake) {
	for (size_t i = 0; i < MaxLengthSnake; i++) {
		(snake + i)->image.loadFromFile("images/snakePart.png");
		(snake + i)->texture.loadFromImage((snake + i)->image);
		(snake + i)->sprite.setTexture((snake + i)->texture);
		(snake + i)->sprite.setTextureRect(IntRect(0, 0, SpriteSize, SpriteSize));
	}

}
