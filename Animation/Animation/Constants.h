#pragma once

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

const unsigned int WindowWidth = 800U;
const unsigned int WindowHeight = 600U;

const sf::Vector2f StartBlockPos = sf::Vector2f(100, 100);
const sf::Vector2f BlockSize = sf::Vector2f(20, 20);
const float Margin = 30.f;
const int BlocksCount = 6;
const float Step = 200.f;
const float MaxDistance = 420.f;
const sf::Vector2f ScaleVal = sf::Vector2f(0.02f, 0.f);
const float RotationAngle = 6.f;
const int TransparensyStep = 2;
const int MaxTranspValue = 255;
const sf::Color ColorStep = sf::Color(3, -2, 1, 0);
const sf::Vector2f DefaultScale = sf::Vector2f(1.f, 1.f);


const sf::Color BlockColor = sf::Color(65, 131, 215, 255);

enum Direction
{
	RIGHT,
	DOWN,
	LEFT,
	UP,
};

enum State
{
	TRANSPARENCY,
	SIZE,
	ROTATION,
	COLOR
};