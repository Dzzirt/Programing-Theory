#include "../Headers/image_manager.h"
#include "../Headers/consts_and_enums.h"
#include "../Headers/arrow.h"

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

void Update(ImageManager& manager) {
	VisualComponents& visual = *manager.visual;
	Message& message = *manager.message;
	Directory& directory = *manager.directory;
	ManagerWindow& man_window = *manager.man_window;
	RenderWindow& window = *man_window.window;
	const FloatRect& g_pic_bounds = visual.picture->getGlobalBounds();
	float& w_scale_x = man_window.win_scale.x;
	float& w_scale_y = man_window.win_scale.y;
	ArrowUpdate(window.getSize(), man_window.win_scale, *visual.arrow);
	ZoomButtonsUpdate(window.getSize(), man_window.win_scale, *visual.zoom_buttons);
	if (!visual.is_img_loaded) {
		message.text.setString("Wrong format of image!");
		const FloatRect& text_bounds = message.text.getLocalBounds();
		visual.picture->setTextureRect(IntRect(0, 0, 0, 0));
		message.text.setOrigin(text_bounds.width / 2.f, text_bounds.height / 2.f);
		message.text.setPosition(window.getSize().x / 2.f * w_scale_x, window.getSize().y / 2.f * w_scale_y);
		window.setTitle("Failed to open image!");
	}
	else {
		message.text.setString("");
		window.setTitle(directory.filenames[0][directory.current_image]);
		visual.picture->setTexture(*visual.texture);
		float texture_x = float(visual.texture->getSize().x);
		float texture_y = float(visual.texture->getSize().y);
		visual.picture->setTextureRect(IntRect(0, 0, visual.texture->getSize().x, visual.texture->getSize().y));

		if (visual.pic_increase && man_window.zoom <= MaxZoom) {
			man_window.zoom *= 2.f;
			visual.pic_increase = false;
		}

		if (visual.pic_decrease && man_window.zoom >= MinZoom && man_window.zoom != 1.f) {
			man_window.zoom /= 2.f;
			visual.pic_decrease = false;
		}
		if (man_window.zoom == 1.f) {
			man_window.drag = Vector2f(0, 0);
		}
		if (texture_x > window.getSize().x || texture_y > window.getSize().y) {
			float x_scale = window.getSize().x / texture_x;
			float y_scale = window.getSize().y / texture_y;

			if (x_scale < y_scale) {
				visual.picture->setScale(w_scale_x * x_scale * man_window.zoom, w_scale_y * x_scale * man_window.zoom);
			}
			else {
				visual.picture->setScale(w_scale_x * y_scale * man_window.zoom, w_scale_y * y_scale * man_window.zoom);
			}
		}
		else {
			visual.picture->setScale(w_scale_x * man_window.zoom, w_scale_y * man_window.zoom);
		}
		if (g_pic_bounds.width > window.getSize().x || g_pic_bounds.height > window.getSize().y) {
			visual.pic_less_than_win = false;
		}
		else {
			visual.pic_less_than_win = true;
		}
		float pic_texture_x = float(visual.picture->getTexture()->getSize().x);
		float pic_texture_y = float(visual.picture->getTexture()->getSize().y);
		visual.picture->setOrigin(pic_texture_x / 2.f, pic_texture_y / 2.f);
		MovePicture(visual, man_window);
		float x_pos = window.getSize().x / 2.f * w_scale_x - man_window.drag.x;
		float y_pos = window.getSize().y / 2.f * w_scale_y - man_window.drag.y;
		visual.picture->setPosition(x_pos, y_pos);
		CheckCollisionWithBorders(visual, man_window);
		}
	}



	

void MovePicture(VisualComponents& visual, ManagerWindow& man_window) {
	float mouse_x = Mouse::getPosition(*man_window.window).x * man_window.win_scale.x;
	float mouse_y = Mouse::getPosition(*man_window.window).y * man_window.win_scale.y;
	Vector2f mouse(mouse_x, mouse_y);
	if (man_window.drag_and_drop) {
		man_window.drag = man_window.last_pos_before_click - mouse ;
		man_window.last_drag = man_window.drag;
	}
}

void CheckCollisionWithBorders(VisualComponents & visual, ManagerWindow & man_window) {
	RenderWindow & window = *man_window.window;
	if (man_window.zoom > 1.f && !visual.pic_less_than_win) {
		const FloatRect & pic_bounds = visual.picture->getGlobalBounds();
		float x = pic_bounds.left;
		float y = pic_bounds.top;
		cout << pic_bounds.left << endl;
		if (pic_bounds.left > 0) {
			x = 0;
		}
		if (pic_bounds.top > 0) {
			y = 0;
		}
		if (pic_bounds.left + pic_bounds.width < window.getSize().x) {
			x = window.getSize().x - pic_bounds.width;
		}
		if (pic_bounds.top + pic_bounds.height < window.getSize().y) {
			y = window.getSize().y - pic_bounds.height;
		}
		visual.picture->setPosition(x, y);
		visual.picture->setOrigin(0, 0);
	}
}

void ProcessEvents(ImageManager& manager) {
	bool clicked = false;
	Directory& directory = *manager.directory;
	ManagerWindow& man_window = *manager.man_window;
	RenderWindow& window = *man_window.window;
	VisualComponents& visual = *manager.visual;
	ZoomButtons& zoom = *manager.visual->zoom_buttons;
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
		if (Mouse::isButtonPressed(Mouse::Left) && !visual.pic_less_than_win) {
			man_window.drag_and_drop = true;
			
			
		}
		if (event.type == Event::Resized) {
			man_window.is_win_resized = true;
			man_window.win_scale.x = WindowWidth / man_window.window->getSize().x;
			man_window.win_scale.y = WindowHeight / man_window.window->getSize().y;
		}
		if (event.type == Event::Closed) {
			window.close();
		}
		if (!Mouse::isButtonPressed(Mouse::Left)) {
			man_window.drag_and_drop = false;
			float x = Mouse::getPosition(*man_window.window).x * man_window.win_scale.x;
			float y = Mouse::getPosition(*man_window.window).y * man_window.win_scale.y;
			man_window.last_pos_before_click = Vector2f(x, y) + man_window.last_drag;
		}
		if (event.type == Event::MouseWheelMoved) {
			if (event.mouseWheel.delta > 0)
				visual.pic_increase = true;
			else {
				visual.pic_decrease = true;
			}
		}
	}

	InterractWithArrow(manager, clicked);
	InterractWithZoom(man_window, zoom, clicked);
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
		man_window.zoom = 1.f;
		man_window.last_drag = man_window.drag = Vector2f(0.f, 0.f);
		visual.texture = new Texture();
		ChangeImage(directory, visual);
	}
}

void Render(ImageManager& manager) {
	Message& message = *manager.message;
	VisualComponents& visual = *manager.visual;
	Arrow& arrow = *manager.visual->arrow;
	ZoomButtons& zoom = *manager.visual->zoom_buttons;
	RenderWindow& window = *manager.man_window->window;
	window.clear(Color(224, 224, 224));
	window.draw(*visual.picture);
	window.draw(message.text);
	window.draw(*arrow.left_arrow);
	window.draw(*arrow.right_arrow);
	window.draw(*zoom.zoom_in);
	window.draw(*zoom.zoom_out);
	window.display();
}

void ChangeImage(Directory& dir, VisualComponents& visual) {
	dir.is_img_changed = false;
	visual.pic_decrease = false;
	visual.pic_increase = false;
	string path = dir.path + "\\" + dir.filenames[0][dir.current_image];
	if (visual.texture->loadFromFile(path)) {
		visual.is_img_loaded = true;
	}
	else {
		visual.is_img_loaded = false;
	}
}

void InterractWithArrow(ImageManager& manager, bool clicked) {
	Directory& directory = *manager.directory;
	Arrow& arrow = *manager.visual->arrow;
	ManagerWindow& man_window = *manager.man_window;

	float mouse_x = Mouse::getPosition(*man_window.window).x * man_window.win_scale.x;
	float mouse_y = Mouse::getPosition(*man_window.window).y * man_window.win_scale.y;
	Vector2f mouse(mouse_x, mouse_y);
	FloatRect left_arrow = arrow.left_arrow->getGlobalBounds();
	FloatRect right_arrow = arrow.right_arrow->getGlobalBounds();


	if (left_arrow.contains(mouse)) {
		man_window.drag_and_drop = false;
		arrow.left_arrow_texture->loadFromFile("Resourses/arrow.png");
		if (clicked) {
			directory.current_image--;
			directory.is_img_changed = true;
		}
	}
	else if (right_arrow.contains(mouse)) {
		man_window.drag_and_drop = false;
		arrow.right_arrow_texture->loadFromFile("Resourses/arrow.png");
		if (clicked) {
			directory.current_image++;
			directory.is_img_changed = true;
		}
	}
	else {
		arrow.left_arrow_texture->loadFromFile("Resourses/arrow_semi_t.png");
		arrow.right_arrow_texture->loadFromFile("Resourses/arrow_semi_t.png");
	}
}

void InterractWithZoom(ManagerWindow& man_window, ZoomButtons& zoom, bool clicked) {
	float mouse_x = Mouse::getPosition(*man_window.window).x * man_window.win_scale.x;
	float mouse_y = Mouse::getPosition(*man_window.window).y * man_window.win_scale.y;

	Vector2f mouse(mouse_x, mouse_y);
	FloatRect zoom_in = zoom.zoom_in->getGlobalBounds();
	FloatRect zoom_out = zoom.zoom_out->getGlobalBounds();


	if (zoom_in.contains(mouse) && man_window.zoom <= MaxZoom) {
		man_window.drag_and_drop = false;
		zoom.zoom_in_texture->loadFromFile("Resourses/zoom_in.png");
		if (clicked && man_window.zoom <= MaxZoom) {
			man_window.zoom *= 2.f;
		}
	}
	else {
		zoom.zoom_in_texture->loadFromFile("Resourses/zoom_in_semi_t.png");
	}
	if (zoom_out.contains(mouse) && man_window.zoom >= MinZoom && man_window.zoom != 1.f) {
		man_window.drag_and_drop = false;
		zoom.zoom_out_texture->loadFromFile("Resourses/zoom_out.png");
		if (clicked && man_window.zoom >= MinZoom) {
			man_window.zoom /= 2.f;
		}
	}
	else {
		zoom.zoom_out_texture->loadFromFile("Resourses/zoom_out_semi_t.png");
	}
}

void DestroyManager(ImageManager*& manager) {
	DestroyDirectory(manager->directory);
	DestroyVisComp(manager->visual);
	DestroyMessage(manager->message);
	DestroyManWindow(manager->man_window);
	delete manager;
}
