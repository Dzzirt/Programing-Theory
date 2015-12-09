#pragma once
#include "SFML/Graphics.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

struct Wheel
{
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	float circleLength;
};

Wheel* CreateWheel();

void WheelInit(Wheel & wheel);

void DestroyWheel(Wheel & wheel);