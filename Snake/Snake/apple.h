#pragma once
#include "mainConst.h"
#include <SFML/Graphics.hpp>
using namespace sf;

struct Apple
{
	float xPos, yPos;
	String fileName;
	Image image;
	Texture texture;
	Sprite sprite;
};

void appleInit(Apple * apple);
void appleDraw(Apple * apple);