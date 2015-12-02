// iClock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "WinClock.h"
#include "WinClockConsts.h"

using namespace sf;


int main()
{
	WinClock* winClock = CreateWinClock();
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	while (winClock->window->isOpen())
	{
		ProcessEvents(*winClock->window);
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{ 
			ProcessEvents(*winClock->window);
			Update(*winClock);
			timeSinceLastUpdate -= TimePerFrame;
		}
		Render(*winClock);
	}
	DestroyWinClock(*winClock);
	return 0;
}
