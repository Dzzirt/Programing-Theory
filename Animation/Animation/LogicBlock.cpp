#include "LogicBlock.h"


LogicBlock* CreateLogicBlock(float x, float y, int number) {
	LogicBlock* block = new LogicBlock();
	LogicBlockInit(*block, x, y, number);
	return block;
}

void LogicBlockInit(LogicBlock& block, float x, float y, int number) {
	block.x = x;
	block.y = y;
	block.step = Step;
	block.deltaX = block.step;
	block.deltaY = 0;
	block.number = number;
	block.maxDistance = MaxDistance + (BlocksCount - number) * Margin;
	block.current_distance = 0.f;
	block.dir = RIGHT;
	block.anim = TRANSPARENCY;
	block.color = BlockColor;
	block.scale = DefaultScale;
	block.rotation = 0.f;

}

void DestroyLogicBlock(LogicBlock & block) {
	delete &block;
}