#include "CarSimulator.h"
using namespace sf;

CarSimulator* CreateCarSimulator()
{
	CarSimulator* simulator = new CarSimulator();
	CarSimulatorInit(*simulator);
	return simulator;
}

RenderWindow* CreateWindow()
{
	return new RenderWindow(VideoMode(WindowWidth, WindowHeight), "Car Simulator");
}

void CarSimulatorInit(CarSimulator& simulator)
{
	simulator.window = CreateWindow();
	simulator.car = CreateCar();
	RoadInit(simulator.road);
	float carWidth = simulator.car->sprite.getGlobalBounds().width;
	simulator.maxDistance = WindowWidth - carWidth - StartCarPos.x;
	simulator.currentDistance = 0.f;
}

void RoadInit(RectangleShape& road)
{
	road.setSize(Vector2f(float(WindowWidth), 100.f));
	road.setFillColor(Color(108, 122, 137));
	road.setPosition(0.f, 500.f);
}

void SetWheelsRotate(Car & car) {
	float rearTurnCount = (car.sprite.getPosition().x - StartCarPos.x) / car.rearWheel->circleLength;
	float frontTurnCount = (car.sprite.getPosition().x - StartCarPos.x) / car.frontWheel->circleLength;
	float rearWheelRotation = rearTurnCount  * 360.f;
	float frontWheelRotation = frontTurnCount * 360.f;
	if ((car.sprite.getPosition().x - StartCarPos.x) / car.rearWheel->circleLength > 1.f) {
		rearWheelRotation = (rearTurnCount - int(rearTurnCount)) * 360.f;
		frontWheelRotation = (frontTurnCount - int(frontTurnCount)) * 360.f;
	}
	car.rearWheel->sprite.setRotation(rearWheelRotation);
	car.frontWheel->sprite.setRotation(frontWheelRotation);
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

void Update(CarSimulator& simulator)
{
	Car& car = *simulator.car;
	car.sprite.move(Vector2f(car.speed, 0.f));
	if (car.sprite.getPosition().x <= StartCarPos.x + simulator.maxDistance / 2.f)
	{
		car.speed += CarAcceleration;
	}
	else
	{
		car.speed -= CarAcceleration;
	}
	const FloatRect& carBounds = car.sprite.getGlobalBounds();
	car.rearWheel->sprite.setPosition(carBounds.left + RearWheelPos.x, carBounds.top + RearWheelPos.y);
	car.frontWheel->sprite.setPosition(carBounds.left + FrontWheelPos.x, carBounds.top + FrontWheelPos.y);
	SetWheelsRotate(car);
}

void Render(CarSimulator& simulator)
{
	simulator.window->clear(Color(218, 223, 225));
	simulator.window->draw(simulator.road);
	simulator.window->draw(simulator.car->sprite);
	simulator.window->draw(simulator.car->frontWheel->sprite);
	simulator.window->draw(simulator.car->rearWheel->sprite);
	simulator.window->display();
}

void DestroyWindow(RenderWindow& window)
{
	delete &window;
}

void DestroyCarSimulator(CarSimulator& simulator)
{
	DestroyWindow(*simulator.window);
	DestroyCar(*simulator.car);
	delete &simulator;
}
