#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"

struct LogicBlock
{
	float x;
	float y;
	float deltaX;
	float deltaY;
	float step;
	int number;
	sf::Color color;
	float maxDistance;
	float current_distance;
	Direction dir;
	State anim;
	sf::Vector2f scale;
	float rotation;

};


LogicBlock* CreateLogicBlock(float x, float y, int number);

void LogicBlockInit(LogicBlock & block, float x, float y, int number);

void DestroyLogicBlock(LogicBlock & block);