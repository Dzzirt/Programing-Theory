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

void Update(ImageManager& manager);

void Render(ImageManager& manager);

void ProcessEvents(ImageManager& manager);

void ChangeImage(Directory & dir, VisualComponents & visual);

void InterractWithArrow(ImageManager & manager, bool clicked);

void InterractWithZoom(ManagerWindow & man_window, ZoomButtons & zoom, bool clicked);

void DestroyManager(ImageManager *& manager);

void MovePicture(VisualComponents & visual, ManagerWindow & man_window);

void CheckCollisionWithBorders(VisualComponents & visual, ManagerWindow & man_window);