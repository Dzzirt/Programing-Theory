#include "Car.h"

Car* CreateCar()
{
	Car * car = new Car();
	CarInit(*car);
	return car;
}

void CarInit(Car& car)
{
	car.image.loadFromFile("Assets/gelig.png");
	car.texture.loadFromImage(car.image);
	car.sprite.setTexture(car.texture);
	car.sprite.setPosition(StartCarPos);
	car.rearWheel = CreateWheel();
	car.frontWheel = CreateWheel();
	car.speed = 0.f;
}

void DestroyCar(Car& car)
{
	DestroyWheel(*car.rearWheel);
	DestroyWheel(*car.frontWheel);
	delete &car;
}