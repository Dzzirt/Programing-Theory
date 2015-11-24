#pragma once
#include "SFML/Graphics.hpp"
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>

struct WinClock
{
	SYSTEMTIME locTime;
	sf::RectangleShape* labels;
	sf::RenderWindow* window;
	sf::CircleShape mainCircle;
	sf::CircleShape middleCircle;
	sf::RectangleShape secHand;
	sf::RectangleShape minHand;
	sf::RectangleShape hourHand;
};

WinClock* CreateWinClock();

void WinClockInit(WinClock& clock);

sf::RenderWindow* CreateClockWindow();

sf::RectangleShape* CreateLabels();

void MainCircleInit(sf::CircleShape& mainCircle);

void MiddleCircleInit(sf::CircleShape& middleCircle);

void SecondHandInit(sf::RectangleShape& secHand);

void MinuteHandInit(sf::RectangleShape& minHand);

void HourHandInit(sf::RectangleShape& hourHand);

void ProcessEvents(sf::RenderWindow& window);

void Render(WinClock& win_clock);

void Update(WinClock& win_clock);
