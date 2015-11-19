#pragma once
#include <SFML/Graphics.hpp>

struct ZoomButtons {
	sf::Texture* zoom_in_texture;
	sf::Texture* zoom_out_texture;
	sf::Sprite* zoom_in;
	sf::Sprite* zoom_out;
};

void ZoomButtonsInit(ZoomButtons& zoom);

void ZoomButtonsUpdate(sf::Vector2u win_size, sf::Vector2f win_scale, ZoomButtons& zoom);

void DestroyZoomButtons(ZoomButtons*& zoom);
