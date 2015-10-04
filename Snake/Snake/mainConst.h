#pragma once
#include "apple.h"
#include "SnakeParts.h"
#include "map.h"

enum State { STARTGAME, PAUSE, ENDGAME, PLAY };

Map * map;
Apple *  apple;
SnakeParts * snake;
Font font;
Text text("", font, 40);
Text title("", font, 50);
Color color(155, 89, 182);
State state = STARTGAME;

int score = 0;
float timeCounter = 0.f, speed = 0.2f;
