#include "Headers/image_manager.h"
#include "Headers/consts_and_enums.h"

int main(int argc, char* argv[]) {
	ImageManager* manager = new ImageManager();
	argv[1] = "C:\\Users\\Dzzirt\\Documents\\Programing-Theory\\lab4\\images";
	ManagerInit(*manager, argv[1]);
	sf::RenderWindow & window = *manager->man_window->window;
	while (window.isOpen()) {
		ProcessEvents(window, *manager);
		Update(*manager, window);
		Render(window, *manager);
	}
	DestroyManager(manager);
	return 0;
}
