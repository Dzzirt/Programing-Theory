#pragma once
#include <SFML/System/String.hpp>

const int MapHeight = 30;
const int MapWidth = 70;
const int SpriteSize = 19;
const int MaxLengthSnake = 60;
const int ScorePerApple = 9;
const float SpeedIncreasePerApple = 0.005f;

const sf::String TileMap[MapHeight] = {

	"     11111     11111     11111     11111     11111      11111         ",
	"                                                                      ",
	"                                                                      ",
	"1                                 1                                  1",
	"1                 1               1               1                  1",
	"1                                 1                                  1",
	"1                                 1                                  1",
	"1              1111                               1111               1",
	"1                                 1                                  1",
	"1                                 1                                  1",
	"1                 1               1               1                  1",
	"1                                 1                                  1",
	"         1                                                 1          ",
	"         1                                                 1          ",
	"         1                  1 1 1 1 1 1 1                  1          ",
	"         1                                                 1          ",
	"         1                                                 1          ",
	"1                                 1                                  1",
	"1                 1               1               1                  1",
	"1                                 1                                  1",
	"1                                 1                                  1",
	"1              1111                               1111               1",
	"1                                 1                                  1",
	"1                                 1                                  1",
	"1                 1               1               1                  1",
	"1                                 1                                  1",
	"                                                                      ",
	"                                                                      ",
	"                                                                      ",
	"     11111     11111     11111     11111     11111      11111         "
};

struct MainConst {
	int score;
	float time_counter, speed;
};

void ConstsInit(MainConst* consts);
