#pragma once
#include "message.h"
#include "visual_components.h"
#include "manager_window.h"
#include "directory.h"
#include <iostream>


struct ImageManager {
	Directory* directory;

	ManagerWindow* man_window;

	VisualComponents* visual;

	Message* message;

};

void ManagerInit(ImageManager & manager, char*& arg);

void Update(ImageManager& manager, sf::RenderWindow& window);

void Render(sf::RenderWindow& window, ImageManager manager);

void ProcessEvents(sf::RenderWindow& window, ImageManager& manager);

void ChangeImage(Directory & dir, VisualComponents & visual);

void InterractWithArrow(ImageManager & manager, bool clicked);

void ArrowUpdate(ManagerWindow & man_window, VisualComponents & visual);

void DestroyManager(ImageManager *& manager);