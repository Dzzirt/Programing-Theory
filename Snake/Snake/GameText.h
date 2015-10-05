#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

struct GameText
{
	Font font;
	Text text;
	Color color;
};

void textInit(GameText * text);