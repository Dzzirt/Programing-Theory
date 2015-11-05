#pragma once
#include <SFML/Graphics.hpp>

struct Message {
	sf::Font font;
	sf::Text text;
};

void MessageInit(Message & message);

void DestroyMessage(Message *& message);