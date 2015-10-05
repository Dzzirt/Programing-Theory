#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

struct Map {
	Image image;
	Texture texture;
	Sprite sprite;
};

void MapInit(Map* map);
