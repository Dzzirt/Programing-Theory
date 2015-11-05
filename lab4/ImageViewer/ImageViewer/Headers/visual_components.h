#pragma once
#include <SFML/Graphics.hpp>

struct VisualComponents {
	sf::Texture* texture;
	sf::Sprite* picture;
	sf::Texture* left_arrow_texture;
	sf::Texture* right_arrow_texture;
	sf::Sprite* left_arrow;
	sf::Sprite* right_arrow;
	bool is_img_loaded;
};

void VisualCompInit(VisualComponents & visual);

void DestroyVisComp(VisualComponents *& visual);