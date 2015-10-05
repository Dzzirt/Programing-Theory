#pragma once
#include "map.h"
#include "SnakeParts.h"
#include "apple.h"
#include "GameText.h"
enum State { STARTGAME, PAUSE, ENDGAME, PLAY, RESTART };

struct Game
{
	Map * map;
	Apple *  apple;
	SnakeParts * snake;
	GameText * gameText;
	State state;

	int score;
	float timeCounter, speed;
};
