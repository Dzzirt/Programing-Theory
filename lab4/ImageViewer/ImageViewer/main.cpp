#include "Headers/image_manager.h"
#include "Headers/consts_and_enums.h"

int main(int argc, char* argv[]) {
	ImageManager* manager = new ImageManager();
	ManagerInit(*manager, argv[1]);
	sf::RenderWindow & window = *manager->man_window->window;
	while (window.isOpen()) {
		ProcessEvents(*manager);
		Update(*manager);
		Render(*manager);
	}
	DestroyManager(manager);
	return 0;
}
