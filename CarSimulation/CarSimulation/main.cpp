// CarSimulation.cpp : Defines the entry point for the console application.
//

#include "SFML/Graphics.hpp"
#include "CarSimulator.h"

using namespace sf;


int main()
{
	CarSimulator* car_simulator = CreateCarSimulator();
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	while (car_simulator->window->isOpen()) {
		ProcessEvents(*car_simulator->window);
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) {
			ProcessEvents(*car_simulator->window);
			Update(*car_simulator);
			timeSinceLastUpdate -= TimePerFrame;
		}
		Render(*car_simulator);
	}
	DestroyCarSimulator(*car_simulator);
	return 0;
}
