#pragma once
#include <SFML/Graphics.hpp>

struct Apple;
void gameStart();
void reinitAll();
void headInit();
void textInit();
void processEvents(sf::RenderWindow & window);
int snakeLength();
void processCollisions(int snakeDrawCounter);
void step();
void eatApple(int snakeDrawCounter);
void appleSpawn(int snakeDrawCounter, Apple & apple);
void render(sf::RenderWindow & window);
std::string toString(int val);
void deleteAll();