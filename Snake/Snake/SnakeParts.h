#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

struct SnakeParts
{
	float xPos = 0.f, yPos = 0.f, xStore, yStore;
	int dir = 0;
	bool draw = false;
	String fileName;
	Image image;
	Texture texture;
	Sprite sprite;
};

void storeXY(SnakeParts * snake);

void snakeUpdate(SnakeParts * snake);

void snakeInit(SnakeParts * snake);