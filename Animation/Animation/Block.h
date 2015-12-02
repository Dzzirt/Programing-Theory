#pragma once
#include "SFML/Graphics.hpp"
#include "LogicBlock.h"
#include "VisualBlock.h"


struct Block {
	LogicBlock* logic;
	VisualBlock* visual;
};

Block* CreateBlock(float x, float y, int number);

void BlockInit(Block & block, float x, float y, int number);

void DestroyBlock(Block & block);

void ChangeDirection(Direction & dir);

void ChangeAnimation(State & state);

void ResetAnimation(State state, Block & block);

void MoveBlock(Block & block);

void BlockAnimUpdate(Block & block);

void RightSideAnimUpdate(Block & block);

void LeftSideAnimUpdate(Block & block);