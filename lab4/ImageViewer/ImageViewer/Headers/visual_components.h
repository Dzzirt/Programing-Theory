#pragma once
#include <SFML/Graphics.hpp>
#include "arrow.h"
#include "zoom_buttons.h"

struct VisualComponents {
	sf::Texture* texture;
	sf::Sprite* picture;
	Arrow* arrow;
	ZoomButtons* zoom_buttons;
	bool is_img_loaded;
	bool pic_increase;
	bool pic_decrease;
	bool pic_less_than_win;
};

void VisualCompInit(VisualComponents & visual);

void DestroyVisComp(VisualComponents *& visual);