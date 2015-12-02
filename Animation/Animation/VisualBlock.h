#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"

struct VisualBlock {
	sf::RectangleShape shape;
};


VisualBlock* CreateVisualBlock();

void VisualBlockInit(VisualBlock & block);

void DestroyVisualBlock(VisualBlock & block);