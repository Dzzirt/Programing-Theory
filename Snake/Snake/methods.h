#pragma once
#include <SFML/Graphics.hpp>
#include "apple.h"
#include "snake_parts.h"
#include "map.h"
#include "Game.h"

enum Dir {
	LEFT,
	RIGHT,
	DOWN,
	UP
};

void NewConsts(Game* game);
void GameStart();
void NewApple(Game* game);
void InitGame(Game* game);
void NewSnake(Game* game);
void NewMap(Game* game);
void NewText(Game* game);
void NewGame(Game* & game);
void HeadInit(SnakeParts* snake);
void ProcessEvents(RenderWindow& window, Game* game);
int SnakeLength(SnakeParts* snake);
void ProcessCollisions(int snake_draw_counter, Game* game);
void Step(SnakeParts* snake);
void EatApple(int snake_draw_counter, Game* game);
void AppleSpawn(int snake_draw_counter, Game* game);
void Render(RenderWindow& window, Game* game);
std::string ToString(int val);
void DestroyGame(Game* game);
void DestroySnake(SnakeParts* snake);
void DestroyMap(Map* map);
void DestroyApple(Apple* apple);
void DestroyText(GameText* text);
void DestroyConsts(MainConst* consts);
