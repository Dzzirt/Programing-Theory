#include <SFML/Graphics.hpp>
#include "Pendulum.h"
using namespace sf;

int main()
{
	Pendulum * pendulum = CreatePendulum();
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	while (pendulum->window->isOpen()) {
		ProcessEvents(*pendulum->window);
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) {
			ProcessEvents(*pendulum->window);
			Update(*pendulum);
			timeSinceLastUpdate -= TimePerFrame;
		}
		Render(*pendulum);
	}
	DestroyPendulum(*pendulum);
	return 0;
}
