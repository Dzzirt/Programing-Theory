#include "Pendulum.h"
#include <iostream>

using namespace sf;


Pendulum* CreatePendulum()
{
	Pendulum* pendulum = new Pendulum();
	PendulumInit(*pendulum);
	return pendulum;
}

RenderWindow* CreateWindow()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow* window = new RenderWindow(VideoMode(WinWidth, WinHeight), "Clock", Style::Default, settings);
	return window;
}

void LeftPaulderInit(ConvexShape& lPaulder)
{
	lPaulder.setPointCount(3);
	lPaulder.setPoint(0, PendulumPos);
	lPaulder.setPoint(1, Vector2f(550, 200 + 50));
	lPaulder.setPoint(2, Vector2f(500, 300));
	lPaulder.setFillColor(Color::Black);
	lPaulder.setOrigin(lPaulder.getPoint(0));
	lPaulder.setPosition(lPaulder.getPoint(0));
}

void RightPaulderInit(ConvexShape& rPaulder)
{
	rPaulder.setPointCount(3);
	rPaulder.setPoint(0, PendulumPos);
	rPaulder.setPoint(1, Vector2f(550, 250));
	rPaulder.setPoint(2, Vector2f(600, 300));
	rPaulder.setFillColor(Color::Black);
	rPaulder.setOrigin(rPaulder.getPoint(0));
	rPaulder.setPosition(rPaulder.getPoint(0));
}

void PendulumThreadInit(ConvexShape & thread)
{
	thread.setPointCount(6);
	thread.setPoint(0, Vector2f(550, 220));
	thread.setPoint(1, Vector2f(552, 220));
	thread.setPoint(2, Vector2f(552, 500));
	thread.setPoint(3, Vector2f(562, 482));
	thread.setPoint(4, Vector2f(540,482));
	thread.setPoint(5, Vector2f(550, 500));
	thread.setFillColor(Color::Black);
	thread.setOrigin(551, 220);
	thread.setPosition(PendulumPos);
}


void LeftCogwheelInit(Sprite& leftCogwheel, Texture& leftCogwheelTexture)
{
	leftCogwheelTexture.loadFromFile("Assets/cogwheel1.png");
	leftCogwheelTexture.setSmooth(true);
	Vector2u texture_size = leftCogwheelTexture.getSize();
	leftCogwheel.setTexture(leftCogwheelTexture);
	leftCogwheel.setPosition(LeftCogwheelPos);
	leftCogwheel.setOrigin(texture_size.x / 2.f, texture_size.y / 2.f);
}

void RightCogwheelInit(Sprite& rightCogwheel, Texture& rightCogwheelTexture)
{
	rightCogwheelTexture.loadFromFile("Assets/cogwheel2.png");
	rightCogwheelTexture.setSmooth(true);
	Vector2u texture_size = rightCogwheelTexture.getSize();
	rightCogwheel.setTexture(rightCogwheelTexture);
	rightCogwheel.setPosition(RightCogwheelPos);
	rightCogwheel.setOrigin(texture_size.x / 2.f, texture_size.y / 2.f);
}


void SetPendulumRotation(Pendulum& pendulum, float value)
{
	pendulum.leftPaulder.setRotation(value);
	pendulum.rightPaulder.setRotation(value);
	pendulum.thread.setRotation(value);
	pendulum.currentPendulumRotation = value;
}

void PendulumInit(Pendulum& pendulum)
{
	pendulum.window = CreateWindow();
	pendulum.currentPendulumRotation = StartAngle;
	pendulum.speed = 0.f;
	LeftCogwheelInit(pendulum.leftCogwheel, pendulum.leftCogwheelTexture);
	RightCogwheelInit(pendulum.rightCogwheel, pendulum.rightCogwheelTexture);
	LeftPaulderInit(pendulum.leftPaulder);
	RightPaulderInit(pendulum.rightPaulder);
	PendulumThreadInit(pendulum.thread);
	SetPendulumRotation(pendulum, StartAngle);
}

void ProcessEvents(RenderWindow& window)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
		}
	}
}

void Update(Pendulum& pendulum)
{
	if (pendulum.currentPendulumRotation < 0)
	{
		pendulum.speed -= PendulumDeltaSpeed;
	}
	else  {
		pendulum.speed += PendulumDeltaSpeed;
	}	
	if (pendulum.speed < 0) {
		pendulum.currentLeftCogwheelRotation += CogwheelDeltaSpeed;
		pendulum.currentRightCogwheelRotation -= CogwheelDeltaSpeed;
		pendulum.leftCogwheel.setRotation(pendulum.currentLeftCogwheelRotation);
		pendulum.rightCogwheel.setRotation(pendulum.currentRightCogwheelRotation);
	}
	else {
		pendulum.currentLeftCogwheelRotation -= CogwheelDeltaSpeed;
		pendulum.currentRightCogwheelRotation += CogwheelDeltaSpeed;
		pendulum.leftCogwheel.setRotation(pendulum.currentLeftCogwheelRotation);
		pendulum.rightCogwheel.setRotation(pendulum.currentRightCogwheelRotation);
	}
	SetPendulumRotation(pendulum, pendulum.currentPendulumRotation - pendulum.speed);
}

void Render(Pendulum& pendulum)
{
	pendulum.window->clear(Color::White);
	pendulum.window->draw(pendulum.leftPaulder);
	pendulum.window->draw(pendulum.rightPaulder);
	pendulum.window->draw(pendulum.thread);
	pendulum.window->draw(pendulum.leftCogwheel);
	pendulum.window->draw(pendulum.rightCogwheel);
	pendulum.window->display();
}

void DestroyWindow(sf::RenderWindow& window)
{
	delete &window;
}

void DestroyPendulum(Pendulum& pendulum)
{
	DestroyWindow(*pendulum.window);
	delete &pendulum;
}
