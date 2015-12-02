#pragma once
#include <vector>
#include "Block.h"

struct Animation
{
	std::vector<Block*>* blocks;
	sf::RenderWindow* window;
};


sf::RenderWindow* CreateWindow();

Animation* CreateAnimation();

void AnimationInit(Animation & animation);

void ProcessEvents(sf::RenderWindow & window);

void Update(Animation & animation);

void Render(Animation & animation);

void DestroyWindow(sf::RenderWindow & window);

void DestroyBlocks(std::vector<Block*> & blocks);

void DestroyAnimation(Animation & animation);

