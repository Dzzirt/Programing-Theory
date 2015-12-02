#include "Block.h"

Block* CreateBlock(float x, float y, int number)
{
	Block* block = new Block();
	BlockInit(*block, x, y, number);
	return block;
}

void BlockInit(Block& block, float x, float y, int number)
{
	block.logic = CreateLogicBlock(x, y, number);
	block.visual = CreateVisualBlock();
}

void DestroyBlock(Block & block)
{
	DestroyLogicBlock(*block.logic);
	DestroyVisualBlock(*block.visual);
	delete &block;
}

void ChangeDirection(Direction& dir)
{
	switch (dir)
	{
		case RIGHT:
			dir = DOWN;
			break;
		case DOWN:
			dir = LEFT;
			break;
		case LEFT:
			dir = UP;
			break;
		case UP:
			dir = RIGHT;
			break;
	}
}

void ChangeAnimation(State & state)
{
	switch (state) {
	case TRANSPARENCY:
		state = SIZE;
		break;
	case SIZE:
		state = ROTATION;
		break;
	case ROTATION:
		state = COLOR;
		break;
	case COLOR:
		state = TRANSPARENCY;
		break;
	}
}

void ResetAnimation(State state, Block& block)
{
	if (state == ROTATION) {
		block.logic->rotation = 0.f;
		block.visual->shape.setRotation(block.logic->rotation);
	}
	else if (state == COLOR) {
		block.logic->color = BlockColor;
		block.visual->shape.setFillColor(BlockColor);
	}
}

void MoveBlock(Block& block)
{
	LogicBlock & logic = *block.logic;
	switch (logic.dir) {
	case LEFT:
		logic.deltaX = -logic.step;
		logic.deltaY = 0.f;
		break;
	case RIGHT:
		logic.deltaX = logic.step;
		logic.deltaY = 0.f;
		break;
	case UP:
		logic.deltaX = 0.f;
		logic.deltaY = -logic.step;
		break;
	case DOWN:
		logic.deltaX = 0.f;
		logic.deltaY = logic.step;
		break;

	}
	block.visual->shape.setPosition(logic.x, logic.y);
	logic.x += logic.deltaX * TimePerFrame.asSeconds();
	logic.y += logic.deltaY * TimePerFrame.asSeconds();
}

void LeftSideAnimUpdate(Block & block)
{
	LogicBlock & logic = *block.logic;
	switch (logic.anim) {
	case TRANSPARENCY:
		block.logic->color.a -= TransparensyStep;
		block.visual->shape.setFillColor(logic.color);
		break;
	case SIZE:
		block.logic->scale += ScaleVal;
		block.visual->shape.setScale(logic.scale);
		break;
	case ROTATION:
		block.visual->shape.setRotation(logic.rotation += RotationAngle);
		break;
	case COLOR:
		block.logic->color += ColorStep;
		block.visual->shape.setFillColor(logic.color);
		break;
	}
}

void RightSideAnimUpdate(Block & block)
{
	LogicBlock & logic = *block.logic;
	switch (logic.anim) {
	case TRANSPARENCY:
		if (block.logic->color.a <= MaxTranspValue - TransparensyStep) {
			block.logic->color.a += TransparensyStep;
		}
		block.visual->shape.setFillColor(logic.color);
		break;
	case SIZE:
		block.logic->scale -= ScaleVal;
		block.visual->shape.setScale(logic.scale);
		break;
	case ROTATION:
		block.visual->shape.setRotation(logic.rotation -= RotationAngle);
		break;
	case COLOR:
		block.logic->color -= ColorStep;
		block.visual->shape.setFillColor(logic.color);
		break;
	}
}

void BlockAnimUpdate(Block & block)
{
	LogicBlock & logic = *block.logic;
	if (int(logic.current_distance) <= int(logic.maxDistance / 2.f)) {
		LeftSideAnimUpdate(block);
	}
	else {
		RightSideAnimUpdate(block);
	}
}