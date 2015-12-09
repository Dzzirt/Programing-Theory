#include "Wheel.h"

Wheel* CreateWheel()
{
	Wheel* wheel = new Wheel();
	WheelInit(*wheel);
	return wheel;
}

void WheelInit(Wheel& wheel)
{
	wheel.image.loadFromFile("Assets/wheel.png");
	wheel.texture.loadFromImage(wheel.image);
	wheel.texture.setSmooth(true);
	wheel.sprite.setTexture(wheel.texture);
	sf::Vector2f wheelSize = sf::Vector2f(wheel.texture.getSize());
	wheel.sprite.setOrigin(wheelSize.x / 2.f, wheelSize.y / 2.f);
	wheel.circleLength = float(wheel.texture.getSize().x * M_PI);

}

void DestroyWheel(Wheel& wheel)
{
	delete &wheel;
}