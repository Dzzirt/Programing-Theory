#pragma once
#include <SFML/Graphics.hpp>

struct ManagerWindow {
	sf::RenderWindow * window;
	bool is_win_resized;
	float scale_x;
	float scale_y;

};

void WindowInit(ManagerWindow & man_window);

void DestroyManWindow(ManagerWindow *& man_window);