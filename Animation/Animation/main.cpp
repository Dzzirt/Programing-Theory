// Animation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "Animation.h"

using namespace sf;


int main()
{
	Animation* animation = CreateAnimation();
	Clock clock;
	Time time_since_last_update = Time::Zero;
	while (animation->window->isOpen()) {
		ProcessEvents(*animation->window);
		time_since_last_update += clock.restart();
		while (time_since_last_update > TimePerFrame) {
			time_since_last_update -= TimePerFrame;
			ProcessEvents(*animation->window);
			Update(*animation);
		}
		Render(*animation);
	}
	DestroyAnimation(*animation);
	return 0;
}
