#pragma once
#include "main_fields.h"
#include <SFML/Graphics.hpp>
using namespace sf;

struct Apple {
	float x_pos, y_pos;
	String file_name;
	Image image;
	Texture texture;
	Sprite sprite;
};

void AppleInit(Apple* apple);
void AppleDraw(Apple* apple);
