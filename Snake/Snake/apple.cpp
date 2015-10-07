#include "apple.h"
#include  "main_fields.h"

void AppleInit(Apple* apple) {
	AppleDraw(apple);
	apple->sprite.setPosition(apple->x_pos, apple->y_pos);
	apple->image.loadFromFile("images/apple.png");
	apple->texture.loadFromImage(apple->image);
	apple->sprite.setTexture(apple->texture);
	apple->sprite.setTextureRect(IntRect(0, 0, SpriteSize, SpriteSize));
}

void AppleDraw(Apple* apple) {
	apple->x_pos = (rand() % MapWidth) * (float)SpriteSize;
	apple->y_pos = (rand() % MapHeight) * (float)SpriteSize;
	while (TileMap[(int)(apple->y_pos / SpriteSize)][(int)(apple->x_pos / SpriteSize)] != ' ') {
		apple->x_pos = (rand() % MapWidth) * (float)SpriteSize;
		apple->y_pos = (rand() % MapHeight) * (float)SpriteSize;
	}
}
