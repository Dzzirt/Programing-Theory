#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"


struct Pendulum
{
	sf::Texture leftCogwheelTexture;
	sf::Texture rightCogwheelTexture;
	sf::Sprite leftCogwheel;
	sf::Sprite rightCogwheel;
	sf::ConvexShape leftPaulder;
	sf::ConvexShape rightPaulder;
	sf::ConvexShape thread;
	sf::RenderWindow * window;
	float currentPendulumRotation;
	float currentLeftCogwheelRotation;
	float currentRightCogwheelRotation;
	float speed;
};

Pendulum* CreatePendulum();

sf::RenderWindow* CreateWindow();

void PendulumInit(Pendulum & pendulum);

void ProcessEvents(sf::RenderWindow& window);

void Update(Pendulum & pendulum);

void Render(Pendulum & pendulum);

void DestroyWindow(sf::RenderWindow & window);

void DestroyPendulum(Pendulum & pendulum);