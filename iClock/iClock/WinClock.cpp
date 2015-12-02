#include "stdafx.h"
#include "WinClock.h"
#include "WinClockConsts.h"

using namespace sf;

WinClock* CreateWinClock()
{
	WinClock* win_clock = new WinClock();
	WinClockInit(*win_clock);
	return win_clock;
}

void WinClockInit(WinClock& clock)
{
	clock.window = CreateClockWindow();
	clock.labels = CreateLabels();
	MainCircleInit(clock.mainCircle);
	MiddleCircleInit(clock.middleCircle);
	SecondHandInit(clock.secHand);
	MinuteHandInit(clock.minHand);
	HourHandInit(clock.hourHand);
}

RenderWindow* CreateClockWindow()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow* window = new RenderWindow(VideoMode(WindowWidth, WindowHeight), "Clock", Style::Default, settings);
	return window;
}

RectangleShape* CreateLabels()
{
	RectangleShape* shapes = new RectangleShape[LabelsCount];
	for (size_t i = 0; i < LabelsCount; ++i)
	{
		RectangleShape& label = *(shapes + i);
		size_t angle = LabelStepInDegree * i + 90;
		double x = (WindowWidth / 2.f) + MainCircleRadius * cos(i * LabelStepInDegree * M_PI / 180);
		double y = WindowWidth / 2.f + MainCircleRadius * sin(i * LabelStepInDegree * M_PI / 180);
		label.setPosition(float(x), float(y));
		label.setFillColor(Color::Black);
		label.setOrigin(LabelWidth / 2.f, 0);
		label.setSize(Vector2f(LabelWidth, LabelHeight));
		label.setRotation(float(angle));
	}
	return shapes;
}

void MainCircleInit(CircleShape& mainCircle)
{
	mainCircle.setRadius(MainCircleRadius);
	mainCircle.setPointCount(MainCirclePointCount);
}

void MiddleCircleInit(CircleShape& middleCircle)
{
	middleCircle.setRadius(MiddleCircleRadius);
	middleCircle.setOrigin(MiddleCircleRadius, MiddleCircleRadius);
	middleCircle.setPointCount(MiddleCirclePointCount);
	middleCircle.setFillColor(Color::Black);
	middleCircle.setPosition(Vector2f(MainCircleRadius, MainCircleRadius));
}

void MinuteHandInit(RectangleShape& minHand)
{
	minHand.setSize(Vector2f(MinLineWidth, MinLineHeight));
	minHand.setOrigin(MinLineWidth / 2.f, MinLineHeight);
	minHand.setFillColor(Color::Black);
	minHand.setPosition(Vector2f(MainCircleRadius, MainCircleRadius));
}

void SecondHandInit(RectangleShape& secHand)
{
	secHand.setSize(Vector2f(SecLineWidth, SecLineHeight));
	secHand.setOrigin(SecLineWidth / 2.f, SecLineHeight);
	secHand.setFillColor(Color::Black);
	secHand.setPosition(Vector2f(MainCircleRadius, MainCircleRadius));
}

void HourHandInit(RectangleShape& hourHand)
{
	hourHand.setSize(Vector2f(HourLineWidth, HourLineHeight));
	hourHand.setOrigin(HourLineWidth / 2.f, HourLineHeight);
	hourHand.setFillColor(Color::Black);
	hourHand.setPosition(Vector2f(MainCircleRadius, MainCircleRadius));
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

void Update(WinClock& win_clock)
{
	GetLocalTime(&win_clock.locTime);
	if (win_clock.locTime.wHour > 12)
	{
		win_clock.locTime.wHour -= 12;
	}
	int min = win_clock.locTime.wMinute;
	int sec = win_clock.locTime.wSecond;
	int hour = win_clock.locTime.wHour;

	win_clock.secHand.setRotation(sec * SecStepInDegree);
	win_clock.minHand.setRotation(min * MinStepInHour + sec * SecStepInMin);
	win_clock.hourHand.setRotation(hour * HourStepInHalfDay + min * MinStepInHalfDay + sec * SecStepInHalfDay);
}

void Render(WinClock& win_clock)
{
	win_clock.window->clear();
	win_clock.window->draw(win_clock.mainCircle);
	win_clock.window->draw(win_clock.middleCircle);
	win_clock.window->draw(win_clock.secHand);
	win_clock.window->draw(win_clock.minHand);
	win_clock.window->draw(win_clock.hourHand);
	for (size_t i = 0; i < LabelsCount; i++)
	{
		win_clock.window->draw(*(win_clock.labels + i));
	}
	win_clock.window->display();
}


void DestroyLabels(sf::RectangleShape& labels) {
	delete[] & labels;
}

void DestroyClockWindow(sf::RenderWindow& window) {
	delete &window;
}

void DestroyWinClock(WinClock& win_clock) {
	DestroyLabels(*win_clock.labels);
	DestroyClockWindow(*win_clock.window);
	delete &win_clock;
}