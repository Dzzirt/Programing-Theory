#pragma once
#include <SFML/Graphics.hpp>
#include "apple.h"
#include "SnakeParts.h"
#include "map.h"
#include "Game.h"

void gameStart();
void newApple(Game * game);
void initGame(Game * game);
void newSnake(Game * game);
void newMap(Game * game);
void newText(Game * game);
void newGame(Game * &game);
void headInit(SnakeParts * snake);
void processEvents(RenderWindow & window, Game * game);
int snakeLength(SnakeParts * snake);
void processCollisions(int snakeDrawCounter, Game * game);
void step(SnakeParts * snake);
void eatApple(int snakeDrawCounter, Game * game);
void appleSpawn(int snakeDrawCounter, Game * game);
void render(sf::RenderWindow & window, Game * game);
std::string toString(int val);
void destroyGame(Game * game);
void destroySnake(SnakeParts * snake);
void destroyMap(Map * map);
void destroyApple(Apple * apple);
void destroyText(GameText * text);