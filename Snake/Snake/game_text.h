#pragma once
#include <SFML/Graphics.hpp>

struct GameText {
	sf::Font font;
	sf::Text text;
	sf::Color color;
};

void TextInit(GameText* text);
