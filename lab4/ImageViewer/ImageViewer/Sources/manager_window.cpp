#include "../Headers/manager_window.h"
#include "../Headers/consts_and_enums.h"

using namespace sf;

void WindowInit(ManagerWindow & man_window) {
	man_window.window = new RenderWindow(VideoMode(unsigned int(WindowWidth), unsigned int(WindowHeight)), "Image Viewer");
	man_window.is_win_resized = false;
	man_window.win_scale.x = WindowWidth / man_window.window->getSize().x;
	man_window.win_scale.y = WindowHeight / man_window.window->getSize().y;
	man_window.drag_and_drop = false;
	man_window.zoom = 1.f;
	man_window.last_pos_before_click = Vector2f(0, 0);
	man_window.drag = Vector2f(0, 0);
	man_window.last_drag = Vector2f(0, 0);
}

void DestroyManWindow(ManagerWindow*& man_window) {
	delete man_window->window;
	delete man_window;
}