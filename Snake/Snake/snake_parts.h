#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

#define STEP 19;

struct SnakeParts {
	float x_pos = 0.f, y_pos = 0.f, x_store, y_store;
	int dir = 0;
	bool draw = false;
	String file_name;
	Image image;
	Texture texture;
	Sprite sprite;
};

void StoreXY(SnakeParts* snake);

void SnakeUpdate(SnakeParts* snake);

void SnakeInit(SnakeParts* snake);
