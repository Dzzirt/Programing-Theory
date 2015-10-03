#pragma once

enum State { STARTGAME, PAUSE, ENDGAME, PLAY };
Map * map = new Map();
Apple *  apple = new Apple();
SnakeParts * snake = new SnakeParts[50];
Font font;
Text text("", font, 40);
Text title("", font, 50);
Color color(155, 89, 182);

int score = 0;
float timeCounter = 0.f, speed = 0.2f;
State state = STARTGAME;