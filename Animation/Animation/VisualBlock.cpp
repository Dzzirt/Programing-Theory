#include "VisualBlock.h"

VisualBlock* CreateVisualBlock()
{
	VisualBlock* block = new VisualBlock();
	VisualBlockInit(*block);
	return block;
}

void VisualBlockInit(VisualBlock& block)
{
	block.shape.setFillColor(BlockColor);
	block.shape.setOrigin(BlockSize / 2.f);
	block.shape.setSize(BlockSize);
}

void DestroyVisualBlock(VisualBlock& block)
{
	delete &block;
}