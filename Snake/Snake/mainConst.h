#pragma once
#include <SFML/System/String.hpp>

const int MAP_HEIGHT = 30;
const int MAP_WIDTH = 70;
const int spriteSize = 19;
const int maxLengthSnake = 60;

const sf::String TileMap[MAP_HEIGHT] = {

	"     11111     11111     11111     11111     11111      11111         ",
	"                                                                      ",
	"                                                                      ",
	"1                                 1                                  1",
	"1                 1               1               1                  1",
	"1                                 1                                  1",
	"1                                 1                                  1",
	"1                                                                    1",
	"1                                 1                                  1",
	"1                                 1                                  1",
	"1                 1               1               1                  1",
	"1                                 1                                  1",
	"                                                                      ",
	"                                                                      ",
	"                            1 1 1 1 1 1 1                             ",
	"                                                                      ",
	"                                                                      ",
	"1                                 1                                  1",
	"1                 1               1               1                  1",
	"1                                 1                                  1",
	"1                                 1                                  1",
	"1                                                                    1",
	"1                                 1                                  1",
	"1                                 1                                  1",
	"1                 1               1               1                  1",
	"1                                 1                                  1",
	"                                                                      ",
	"                                                                      ",
	"                                                                      ",
	"     11111     11111     11111     11111     11111      11111         "
};

struct mainConst
{
	int score;
	float timeCounter, speed;
};

void constsInit(mainConst * consts);