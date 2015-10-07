#pragma once
#include "map.h"
#include "snake_parts.h"
#include "apple.h"
#include "game_text.h"
#include "main_fields.h"


enum State {
	STARTGAME,
	PAUSE, 
	ENDGAME, 
	PLAY, 
	RESTART 
};

struct Game {
	Map* map;
	Apple* apple;
	SnakeParts* snake;
	GameText* game_text;
	MainConst* consts;
	State state;


};
