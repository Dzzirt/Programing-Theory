#pragma once
#include <SFML/Graphics.hpp>

struct Arrow {
	sf::Texture* left_arrow_texture;
	sf::Texture* right_arrow_texture;
	sf::Sprite* left_arrow;
	sf::Sprite* right_arrow;
};

void ArrowUpdate(sf::Vector2u win_size, sf::Vector2f win_scale, Arrow & arrow);

void ArrowInit(Arrow & arrow);

void DestroyArrow(Arrow *& arrow);