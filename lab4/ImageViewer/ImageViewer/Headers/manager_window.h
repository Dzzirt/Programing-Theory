#pragma once
#include <SFML/Graphics.hpp>

struct ManagerWindow {
	sf::RenderWindow * window;
	bool is_win_resized;
	sf::Vector2f win_scale;
	bool drag_and_drop;
	float zoom;
	sf::Vector2f last_pos_before_click;
	sf::Vector2f drag;
	sf::Vector2f last_drag;
};

void WindowInit(ManagerWindow & man_window);

void DestroyManWindow(ManagerWindow *& man_window);