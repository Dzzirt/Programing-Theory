#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include "Car.h"

struct CarSimulator
{
	sf::RenderWindow * window;
	sf::RectangleShape road;
	Car* car;
	float maxDistance;
	float currentDistance;

};

CarSimulator* CreateCarSimulator();

sf::RenderWindow* CreateWindow();

void CarSimulatorInit(CarSimulator & simulator);

void RoadInit(sf::RectangleShape & road);

void ProcessEvents(sf::RenderWindow & window);

void Update(CarSimulator& simulator);

void Render(CarSimulator & simulator);

void DestroyWindow(sf::RenderWindow & window);

void DestroyCarSimulator(CarSimulator & simulator);

