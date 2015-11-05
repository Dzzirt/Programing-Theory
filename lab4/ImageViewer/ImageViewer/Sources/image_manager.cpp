#include "../Headers/image_manager.h"
#include "../Headers/consts_and_enums.h"

using namespace std;
using namespace sf;

void ManagerInit(ImageManager& manager, char*& arg) {
	manager.directory = new Directory();
	manager.man_window = new ManagerWindow;
	manager.message = new Message();
	manager.visual = new VisualComponents();
	WindowInit(*manager.man_window);
	MessageInit(*manager.message);
	VisualCompInit(*manager.visual);
	DirectoryInit(*manager.directory, arg);
	string path = manager.directory->path + "\\";
	if (manager.directory->filenames->size() == 0) {
		cout << "This folder without images!" << endl;
		manager.man_window->window->close();
	}
	else {
		string first_img_name = manager.directory->filenames[0][0];
		manager.visual->texture->loadFromFile(path + first_img_name);
	}
}

void Update(ImageManager& manager, RenderWindow& window) {
	VisualComponents& visual = *manager.visual;
	Message& message = *manager.message;
	Directory& directory = *manager.directory;
	ManagerWindow& man_window = *manager.man_window;

	ArrowUpdate(*manager.man_window, *manager.visual);

	if (!visual.is_img_loaded) {
		visual.picture->setTextureRect(IntRect(0, 0, 0, 0));
		message.text.setString("Wrong format of image!");
		message.text.setOrigin(message.text.getLocalBounds().width / 2.f, message.text.getLocalBounds().height / 2.f);
		message.text.setPosition(window.getSize().x / 2.f * WindowWidth / window.getSize().x, window.getSize().y / 2.f * WindowHeight / window.getSize().y);
		window.setTitle("Failed to open image!");
	}
	else {
		message.text.setString("");
		window.setTitle(directory.filenames[0][directory.current_image]);
		visual.picture->setTexture(*visual.texture);
		float texture_x = float(visual.texture->getSize().x);
		float texture_y = float(visual.texture->getSize().y);
		float& w_scale_x = man_window.scale_x;
		float& w_scale_y = man_window.scale_y;
		visual.picture->setTextureRect(IntRect(0, 0, visual.texture->getSize().x, visual.texture->getSize().y));

		if (man_window.is_win_resized) {
			w_scale_x = WindowWidth / man_window.window->getSize().x;
			w_scale_y = WindowHeight / man_window.window->getSize().y;
		}

		if (texture_x > man_window.window->getSize().x || texture_y > man_window.window->getSize().y) {
			float x_scale = (man_window.window->getSize().x) / texture_x;
			float y_scale = (man_window.window->getSize().y) / texture_y;
			if (x_scale < y_scale) {
				visual.picture->setScale(w_scale_x * x_scale, w_scale_y * x_scale);
			}
			else {
				visual.picture->setScale(w_scale_x * y_scale, w_scale_y * y_scale);
			}
		}
		else {
			visual.picture->setScale(w_scale_x, w_scale_y);
		}

		visual.picture->setOrigin(visual.picture->getTexture()->getSize().x / 2.f, visual.picture->getTexture()->getSize().y / 2.f);
		visual.picture->setPosition(man_window.window->getSize().x / 2.f * w_scale_x, man_window.window->getSize().y / 2.f * w_scale_y);
	}


}

void ProcessEvents(RenderWindow& window, ImageManager& manager) {
	bool clicked = false;
	Directory& directory = *manager.directory;
	ManagerWindow& man_window = *manager.man_window;
	VisualComponents& visual = *manager.visual;
	Event event;
	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			directory.current_image--;
			directory.is_img_changed = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			directory.current_image++;
			directory.is_img_changed = true;
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			clicked = true;
		}
		if (event.type == Event::Resized) {
			man_window.is_win_resized = true;
			man_window.scale_x = WindowWidth / man_window.window->getSize().x;
			man_window.scale_y = WindowHeight / man_window.window->getSize().y;
		}
		if (event.type == Event::Closed) {
			window.close();
		}
	}
	InterractWithArrow(manager, clicked);
	if (directory.current_image < 0) {
		directory.current_image = 0;
		directory.is_img_changed = false;
	}
	else if (directory.current_image == directory.filenames->size()) {
		directory.current_image = directory.filenames->size() - 1;
		directory.is_img_changed = false;
	}
	if (directory.is_img_changed) {
		delete visual.texture;
		visual.texture = new Texture();
		ChangeImage(directory, visual);
	}
}

void Render(RenderWindow& window, ImageManager manager) {
	Message& message = *manager.message;
	VisualComponents& visual = *manager.visual;
	window.clear(sf::Color(224, 224, 224));
	window.draw(*visual.picture);
	window.draw(message.text);
	window.draw(*visual.left_arrow);
	window.draw(*visual.right_arrow);
	window.display();

}

void ChangeImage(Directory& dir, VisualComponents& visual) {
	dir.is_img_changed = false;
	if (visual.texture->loadFromFile(dir.path + "\\" + dir.filenames[0][dir.current_image])) {
		visual.is_img_loaded = true;
	}
	else {
		visual.is_img_loaded = false;
	}
}

void InterractWithArrow(ImageManager& manager, bool clicked) {
	Directory& directory = *manager.directory;
	VisualComponents& visual = *manager.visual;
	ManagerWindow& man_window = *manager.man_window;

	float mouse_x = Mouse::getPosition(*man_window.window).x * man_window.scale_x;
	float mouse_y = Mouse::getPosition(*man_window.window).y * man_window.scale_y;
	Vector2f mouse(mouse_x, mouse_y);
	FloatRect left_arrow = visual.left_arrow->getGlobalBounds();
	FloatRect right_arrow = visual.right_arrow->getGlobalBounds();


	if (left_arrow.contains(mouse)) {
		visual.left_arrow_texture->loadFromFile("Resourses/arrow.png");
		if (clicked) {
			directory.current_image--;
			directory.is_img_changed = true;
		}
	}
	else if (right_arrow.contains(mouse)) {
		visual.right_arrow_texture->loadFromFile("Resourses/arrow.png");
		if (clicked) {
			directory.current_image++;
			directory.is_img_changed = true;
		}
	}
	else {
		visual.left_arrow_texture->loadFromFile("Resourses/arrow_semi_t.png");
		visual.right_arrow_texture->loadFromFile("Resourses/arrow_semi_t.png");
	}
}

void ArrowUpdate(ManagerWindow& man_window, VisualComponents& visual) {
	Vector2u w_size = man_window.window->getSize();
	Vector2u left_arrow_texture_size = visual.left_arrow->getTexture()->getSize();
	Vector2u right_arrow_texture_size = visual.right_arrow->getTexture()->getSize();
	float w_scale_x = man_window.scale_x;
	float w_scale_y = man_window.scale_y;
	float l_arr_x = ArrowMarg * w_scale_x;
	float l_arr_y = (w_size.y / 2.f) * w_scale_y;
	float r_arr_x = (w_size.x - right_arrow_texture_size.x - ArrowMarg) * w_scale_x;
	float r_arr_y = w_size.y / 2.f * w_scale_y;

	visual.left_arrow_texture->setSmooth(true);
	visual.left_arrow->setOrigin(0, left_arrow_texture_size.y / 2.f);
	visual.left_arrow->setPosition(l_arr_x, l_arr_y);
	visual.left_arrow->setTextureRect(IntRect(ArrowWidth, 0, -ArrowWidth, ArrowhHeight));
	visual.left_arrow->setScale(w_scale_x, w_scale_y);

	visual.right_arrow_texture->setSmooth(true);
	visual.right_arrow->setOrigin(0, right_arrow_texture_size.y / 2.f);
	visual.right_arrow->setPosition(r_arr_x, r_arr_y);
	visual.right_arrow->setTextureRect(IntRect(0, 0, ArrowWidth, ArrowhHeight));
	visual.right_arrow->setScale(w_scale_x, w_scale_y);
}

void DestroyManager(ImageManager*& manager) {
	DestroyDirectory(manager->directory);
	DestroyVisComp(manager->visual);
	DestroyMessage(manager->message);
	DestroyManWindow(manager->man_window);
	delete manager;
}
