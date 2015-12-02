#include "Animation.h"
#include <iostream>

using namespace sf;


Animation* CreateAnimation()
{
	Animation* animation = new Animation();
	AnimationInit(*animation);
	return animation;

}

RenderWindow* CreateWindow() {
	return new RenderWindow(VideoMode(WindowWidth, WindowHeight), "Animation");
}

std::vector<Block*>* CreateBlocks() {
	std::vector<Block*>* blocks = new std::vector<Block*>;
	float step = 0.f;
	for (size_t i = 0; i < BlocksCount; i++) {
		Block* block = CreateBlock(StartBlockPos.x + step, StartBlockPos.y, i);
		step += Margin;
		blocks->push_back(block);
	}
	return blocks;
}

void AnimationInit(Animation& animation)
{
	animation.window = CreateWindow();
	animation.blocks = CreateBlocks();
}

void ProcessEvents(RenderWindow & window)
{
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
		}

	}
}

void Update(Animation & animation) {

	for (Block* &block : *animation.blocks) {
		LogicBlock & logic = *block->logic;
		MoveBlock(*block);
		logic.current_distance += abs((logic.deltaX == 0 ? logic.deltaY : logic.deltaX) * TimePerFrame.asSeconds());
		BlockAnimUpdate(*block);
		if (logic.current_distance >= logic.maxDistance) {
			logic.x = int(logic.x) + 0.f;
			logic.y = int(logic.y) + 0.f;
			logic.current_distance = 0.f;
			logic.maxDistance = MaxDistance;
			ResetAnimation(logic.anim, *block);
			ChangeDirection(logic.dir);
			ChangeAnimation(logic.anim);
			block->visual->shape.setFillColor(BlockColor);
			
		}
	}
}

void Render(Animation & animation)
{
	RenderWindow & window = *animation.window;
	window.clear(Color(255, 255, 255));
	for (Block* &block : *animation.blocks) {
		window.draw(block->visual->shape);
	}
	window.display();
}

void DestroyBlocks(std::vector<Block*> & blocks) {
	for (Block* &block : blocks) {
		DestroyBlock(*block);
	}
	delete &blocks;
}

void DestroyWindow(RenderWindow & window) {
	delete &window;
}

void DestroyAnimation(Animation & animation) {
	DestroyWindow(*animation.window);
	DestroyBlocks(*animation.blocks);
}