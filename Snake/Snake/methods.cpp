#pragma once
#include "methods.h"
#include "sstream"
#include "Game.h"
#include "mainConst.h"


//Так и не разобрался как заменить имя snake[0] на что то более понятное

std::string toString(int val) {
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

void newMap(Game* game) {
	game->map = new Map();
	mapInit(game->map);
}

void newApple(Game* game) {
	game->apple = new Apple();
	appleInit(game->apple);
}

void newSnake(Game* game) {
	game->snake = new SnakeParts[maxLengthSnake];
	snakeInit(game->snake);
	headInit(game->snake);
}

void newText(Game* game) {
	game->gameText = new GameText;
	textInit(game->gameText);
}

void newConsts(Game* game) {
	game->consts = new mainConst;
	constsInit(game->consts);
}

void initGame(Game* game) {
	newApple(game);
	newMap(game);
	newSnake(game);
	newText(game);
	newConsts(game);
	game->state = STARTGAME;
}

void newGame(Game* & game) // 
{
	game = new Game();
	initGame(game);
}

void destroyGame(Game* game) {
	destroyApple(game->apple);
	destroyMap(game->map);
	destroySnake(game->snake);
	destroyText(game->gameText);
	destroyConsts(game->consts);
	delete game;
}

void destroySnake(SnakeParts* snake) {
	delete[] snake;
}

void destroyApple(Apple* apple) {
	delete apple;
}

void destroyMap(Map* map) {
	delete map;
}

void destroyText(GameText* text) {
	delete text;
}

void destroyConsts(mainConst* consts) {
	delete consts;
}

void appleSpawn(int snakeDrawCounter, Game* game) {
	Apple* apple = game->apple;
	SnakeParts* snake = game->snake;

	bool safe = false;

	while (safe != true) {
		appleDraw(apple);
		for (int i = 0; i < snakeDrawCounter; i++) {
			if (snake[i].xPos == apple->xPos && snake[i].yPos == apple->yPos) {
				safe = false;
				break;
			}
			safe = true;
		}
	}
	apple->sprite.setPosition(apple->xPos, apple->yPos);
}

void eatApple(int snakeDrawCounter, Game* game) {
	SnakeParts* snake = game->snake;
	mainConst* consts = game->consts;
	float prevPartX = snake[snakeDrawCounter - 1].xStore;
	float prevPartY = snake[snakeDrawCounter - 1].yStore;

	consts->score += 9;
	consts->speed -= 0.005f;
	snake[snakeDrawCounter].draw = true;
	snake[snakeDrawCounter].sprite.setPosition(prevPartX, prevPartY);
}

int snakeLength(SnakeParts* snake) {
	int snakeDrawCounter = 0;
	for (int i = 0; i < maxLengthSnake; i++) {
		if (snake[i].draw == true) {
			snakeDrawCounter++;
		}
	}
	return snakeDrawCounter;
}

void step(SnakeParts* snake) {
	storeXY(snake);
	if ((snake[0].dir == 3) && (snake[0].yPos == 0)) {
		snake[0].yPos = (MAP_HEIGHT - 1) * spriteSize;
		snake[0].sprite.setPosition(snake[0].xPos, snake[0].yPos);
	}
	else if (snake[0].dir == 2 && snake[0].yPos == (MAP_HEIGHT - 1) * spriteSize) {
		snake[0].yPos = 0;
		snake[0].sprite.setPosition(snake[0].xPos, snake[0].yPos);
	}
	else if (snake[0].dir == 1 && snake[0].xPos == 0) {
		snake[0].xPos = (MAP_WIDTH - 1) * spriteSize;
		snake[0].sprite.setPosition(snake[0].xPos, snake[0].yPos);
	}
	else if (snake[0].dir == 0 && snake[0].xPos == (MAP_WIDTH - 1) * spriteSize) {
		snake[0].xPos = 0;
		snake[0].sprite.setPosition(snake[0].xPos, snake[0].yPos);
	}
	else snakeUpdate(snake);

	for (int i = 1; i < maxLengthSnake; i++) {
		if (snake[i].draw == 1) {
			storeXY(snake + i);
			snake[i].xPos = snake[i - 1].xStore;
			snake[i].yPos = snake[i - 1].yStore;
			snake[i].sprite.setPosition(snake[i].xPos, snake[i].yPos);
		}
	}
}

void processEvents(RenderWindow& window, Game* game) {
	SnakeParts* snake = game->snake;
	Event event;


	while (window.pollEvent(event)) {
		Keyboard::Key PRESSED;
		if (event.type == Event::KeyPressed) {
			PRESSED = event.key.code;

			if ((PRESSED == Keyboard::W) && snake[0].dir != DOWN) {
				snake[0].dir = UP;
			}
			else if ((PRESSED == Keyboard::S) && snake[0].dir != UP) {
				snake[0].dir = DOWN;
			}
			else if ((PRESSED == Keyboard::A) && snake[0].dir != LEFT) {
				snake[0].dir = RIGHT;
			}
			else if ((PRESSED == Keyboard::D) && snake[0].dir != RIGHT) {
				snake[0].dir = LEFT;
			}
			else if ((PRESSED == Keyboard::P)) {
				game->state = PAUSE;
			}
			else if ((PRESSED == Keyboard::U)) {
				game->state = PLAY;
			}
			else if ((PRESSED == Keyboard::R) && game->state == ENDGAME) {
				game->state = RESTART;
			}
		}
		if (event.type == Event::Closed || ((event.type == Event::KeyPressed) && (PRESSED == Keyboard::Escape) && game->state == ENDGAME))
			window.close();
	}
}

void headInit(SnakeParts* snake) {
	snake[0].xPos = 190;
	snake[0].yPos = 95;
	snake[0].sprite.setPosition(190, 95);
	snake[0].draw = true;
}

void render(RenderWindow& window, Game* game) {
	SnakeParts* snake = game->snake;
	Map* map = game->map;
	Apple* apple = game->apple;
	window.clear();

	//Map draw

	IntRect earth = IntRect(0, 0, spriteSize, spriteSize);
	IntRect wall = IntRect(spriteSize, 0, spriteSize, spriteSize);
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (TileMap[i][j] == ' ') map->sprite.setTextureRect(earth);
			if (TileMap[i][j] == '1') map->sprite.setTextureRect(wall);
			map->sprite.setPosition((float)(j * spriteSize), (float)(i * spriteSize));
			window.draw(map->sprite);
		}

	//Snake draw

	for (int i = 0; i < maxLengthSnake; ++i) {
		if (snake[i].draw == true) {
			window.draw(snake[i].sprite);
		}
	}

	//Apple draw

	window.draw(apple->sprite);
}

void processCollisions(int snakeDrawCounter, Game* game) {
	SnakeParts* snake = game->snake;
	Apple* apple = game->apple;

	//Collision with Walls

	float X = snake[0].yPos / spriteSize;
	float Y = snake[0].xPos / spriteSize;
	if (TileMap[(int)(X)][(int)(Y)] == '1') {
		game->state = ENDGAME;
	}


	//Collision with itself

	for (int i = 1; i < snakeDrawCounter; i++) {
		if ((snake[i].xPos == snake[0].xPos) && (snake[i].yPos == snake[0].yPos)) {
			game->state = ENDGAME;
		}
	}


	//Interact with Apple

	if ((apple->xPos == snake[0].xPos) && (apple->yPos == snake[0].yPos)) {
		eatApple(snakeDrawCounter, game);
		appleSpawn(snakeDrawCounter, game);
	}
}

void gameStart() {
	RenderWindow window(VideoMode(MAP_WIDTH * spriteSize, MAP_HEIGHT * spriteSize), "Snake");
	Clock clock;
	Game* game;
	newGame(game);
	Text text = game->gameText->text;

	while (window.isOpen()) //разбить на 3 метода
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		game->consts->timeCounter += time;

		processEvents(window, game);

		if (game->state == STARTGAME) {
			window.clear();
			text.setCharacterSize(120);
			text.setString("       Snake!\n\nPress 'U' to start!");
			text.setPosition(250, 50);
			window.draw(text);
		}
		else if (game->state == RESTART) {
			destroyGame(game);
			newGame(game);
			text = game->gameText->text;
			game->state = PLAY;
		}
		else if (game->state == PAUSE) {
			window.clear();
			render(window, game);
			text.setCharacterSize(150);
			text.setString("Pause");
			text.setPosition(455, 160);
			window.draw(text);
		}
		else if (game->state == PLAY) {
			while (game->consts->timeCounter > game->consts->speed) {
				game->consts->timeCounter = 0;

				//Snake movement

				step(game->snake);

				int snakeDrawCounter = snakeLength(game->snake);

				processCollisions(snakeDrawCounter, game);
			}
			render(window, game);
		}
		else if (game->state == ENDGAME) {
			window.clear();
			text.setCharacterSize(120);
			text.setString("        Score: " + toString(game->consts->score) + "\n Press 'Esc' to exit\n Press 'R' to restart");
			text.setPosition(170, 28);
			window.draw(text);
		}

		window.display();
	}
	destroyGame(game);
}
