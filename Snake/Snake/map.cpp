#include "map.h"

void MapInit(Map* map) {
	map->image.loadFromFile("images/map.png");
	map->texture.loadFromImage(map->image);
	map->sprite.setTexture(map->texture);
}
