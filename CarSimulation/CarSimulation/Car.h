#pragma once
#include "SFML/Graphics.hpp"
#include "Wheel.h"
#include "Constants.h"

struct Car
{
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	Wheel* rearWheel;
	Wheel* frontWheel;
	float speed;
};

Car* CreateCar();

void CarInit(Car & car);

void DestroyCar(Car & car);

