#include "../Headers/manager_window.h"
#include "../Headers/consts_and_enums.h"

using namespace sf;

void WindowInit(ManagerWindow & man_window) {
	man_window.window = new RenderWindow(VideoMode(unsigned int(WindowWidth), unsigned int(WindowHeight)), "Image Viewer");
	man_window.is_win_resized = false;
	man_window.scale_x = WindowWidth / man_window.window->getSize().x;
	man_window.scale_y = WindowHeight / man_window.window->getSize().y;
}

void DestroyManWindow(ManagerWindow*& man_window) {
	delete man_window->window;
	delete man_window;
}