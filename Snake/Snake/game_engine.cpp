#pragma once
#include "game_engine.h"
#include "sstream"
#include "Game.h"
#include "main_fields.h"


//Так и не разобрался как заменить имя snake[0] на что то более понятное

std::string ToString(int val) {
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

void NewMap(Game* game) {
	game->map = new Map();
	MapInit(game->map);
}

void NewApple(Game* game) {
	game->apple = new Apple();
	AppleInit(game->apple);
}

void NewSnake(Game* game) {
	game->snake = new SnakeParts[MaxLengthSnake];
	SnakeInit(game->snake);
	HeadInit(game->snake);
}

void NewText(Game* game) {
	game->game_text = new GameText;
	TextInit(game->game_text);
}

void NewConsts(Game* game) {
	game->consts = new MainConst;
	ConstsInit(game->consts);
}

void InitGame(Game* game) {
	NewApple(game);
	NewMap(game);
	NewSnake(game);
	NewText(game);
	NewConsts(game);
	game->state = STARTGAME;
}

void NewGame(Game* & game) // 
{
	game = new Game();
	InitGame(game);
}

void DestroyGame(Game* game) {
	DestroyApple(game->apple);
	DestroyMap(game->map);
	DestroySnake(game->snake);
	DestroyText(game->game_text);
	DestroyConsts(game->consts);
	delete game;
}

void DestroySnake(SnakeParts* snake) {
	delete[] snake;
}

void DestroyApple(Apple* apple) {
	delete apple;
}

void DestroyMap(Map* map) {
	delete map;
}

void DestroyText(GameText* text) {
	delete text;
}

void DestroyConsts(MainConst* consts) {
	delete consts;
}

void AppleSpawn(int snake_draw_counter, Game* game) {
	Apple* apple = game->apple;
	SnakeParts* snake = game->snake;

	bool safe = false;

	while (safe != true) {
		AppleDraw(apple);
		for (int i = 0; i < snake_draw_counter; i++) {
			if (snake[i].x_pos == apple->x_pos && snake[i].y_pos == apple->y_pos) {
				safe = false;
				break;
			}
			safe = true;
		}
	}
	apple->sprite.setPosition(apple->x_pos, apple->y_pos);
}

void EatApple(int snake_draw_counter, Game* game) {
	SnakeParts* snake = game->snake;
	MainConst* consts = game->consts;
	float prev_part_x = snake[snake_draw_counter - 1].x_store;
	float prev_part_y = snake[snake_draw_counter - 1].y_store;

	consts->score += ScorePerApple;
	consts->speed -= SpeedIncreasePerApple;
	snake[snake_draw_counter].draw = true;
	snake[snake_draw_counter].sprite.setPosition(prev_part_x, prev_part_y);
}

int SnakeLength(SnakeParts* snake) {
	int snake_draw_counter = 0;
	for (int i = 0; i < MaxLengthSnake; i++) {
		if (snake[i].draw == true) {
			snake_draw_counter++;
		}
	}
	return snake_draw_counter;
}

void Step(SnakeParts* snake) {
	StoreXY(snake);
	if ((snake[0].dir == UP) && (snake[0].y_pos == 0)) {
		snake[0].y_pos = (MapHeight - 1) * SpriteSize;
		snake[0].sprite.setPosition(snake[0].x_pos, snake[0].y_pos);
	}
	else if (snake[0].dir == DOWN && snake[0].y_pos == (MapHeight - 1) * SpriteSize) {
		snake[0].y_pos = 0;
		snake[0].sprite.setPosition(snake[0].x_pos, snake[0].y_pos);
	}
	else if (snake[0].dir == RIGHT && snake[0].x_pos == 0) {
		snake[0].x_pos = (MapWidth - 1) * SpriteSize;
		snake[0].sprite.setPosition(snake[0].x_pos, snake[0].y_pos);
	}
	else if (snake[0].dir == LEFT && snake[0].x_pos == (MapWidth - 1) * SpriteSize) {
		snake[0].x_pos = 0;
		snake[0].sprite.setPosition(snake[0].x_pos, snake[0].y_pos);
	}
	else SnakeUpdate(snake);

	for (int i = 1; i < MaxLengthSnake; i++) {
		if (snake[i].draw == 1) {
			StoreXY(snake + i);
			snake[i].x_pos = snake[i - 1].x_store;
			snake[i].y_pos = snake[i - 1].y_store;
			snake[i].sprite.setPosition(snake[i].x_pos, snake[i].y_pos);
		}
	}
}

void ProcessEvents(RenderWindow& window, Game* game) {
	SnakeParts* snake = game->snake;
	Event event;

	while (window.pollEvent(event)) {
		Keyboard::Key pressed;
		if (event.type == Event::KeyPressed) {
			pressed = event.key.code;

			if ((pressed == Keyboard::W) && snake[0].dir != DOWN) {
				snake[0].dir = UP;
			}
			else if ((pressed == Keyboard::S) && snake[0].dir != UP) {
				snake[0].dir = DOWN;
			}
			else if ((pressed == Keyboard::A) && snake[0].dir != LEFT) {
				snake[0].dir = RIGHT;
			}
			else if ((pressed == Keyboard::D) && snake[0].dir != RIGHT) {
				snake[0].dir = LEFT;
			}
			else if ((pressed == Keyboard::P)) {
				game->state = PAUSE;
			}
			else if ((pressed == Keyboard::U)) {
				game->state = PLAY;
			}
			else if ((pressed == Keyboard::R) && game->state == ENDGAME) {
				game->state = RESTART;
			}
		}
		if (event.type == Event::Closed || ((event.type == Event::KeyPressed) && (pressed == Keyboard::Escape) && game->state == ENDGAME))
			window.close();
	}
}

void HeadInit(SnakeParts* snake) {
	snake[0].x_pos = 190;
	snake[0].y_pos = 95;
	snake[0].sprite.setPosition(190, 95);
	snake[0].draw = true;
}

void Render(RenderWindow& window, Game* game) {
	SnakeParts* snake = game->snake;
	Map* map = game->map;
	Apple* apple = game->apple;
	window.clear();

	//Map draw

	IntRect earth = IntRect(0, 0, SpriteSize, SpriteSize);
	IntRect wall = IntRect(SpriteSize, 0, SpriteSize, SpriteSize);
	for (int i = 0; i < MapHeight; i++)
		for (int j = 0; j < MapWidth; j++) {
			if (TileMap[i][j] == ' ') map->sprite.setTextureRect(earth);
			if (TileMap[i][j] == '1') map->sprite.setTextureRect(wall);
			map->sprite.setPosition((float)(j * SpriteSize), (float)(i * SpriteSize));
			window.draw(map->sprite);
		}

	//Snake draw

	for (int i = 0; i < MaxLengthSnake; ++i) {
		if (snake[i].draw == true) {
			window.draw(snake[i].sprite);
		}
	}

	//Apple draw

	window.draw(apple->sprite);
}

void ProcessCollisions(int snake_draw_counter, Game* game) {
	SnakeParts* snake = game->snake;
	Apple* apple = game->apple;

	//Collision with Walls

	float X = snake[0].y_pos / SpriteSize;
	float Y = snake[0].x_pos / SpriteSize;
	if (TileMap[(int)(X)][(int)(Y)] == '1') {
		game->state = ENDGAME;
	}


	//Collision with itself

	for (int i = 1; i < snake_draw_counter; i++) {
		if ((snake[i].x_pos == snake[0].x_pos) && (snake[i].y_pos == snake[0].y_pos)) {
			game->state = ENDGAME;
		}
	}


	//Interact with Apple

	if ((apple->x_pos == snake[0].x_pos) && (apple->y_pos == snake[0].y_pos)) {
		EatApple(snake_draw_counter, game);
		AppleSpawn(snake_draw_counter, game);
	}
}

void GameStart() {
	RenderWindow window(VideoMode(MapWidth * SpriteSize, MapHeight * SpriteSize), "Snake");
	Clock clock;
	Game* game;
	NewGame(game);
	Text text = game->game_text->text;

	while (window.isOpen()) //разбить на 3 метода
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		game->consts->time_counter += time;

		ProcessEvents(window, game);

		if (game->state == STARTGAME) {
			window.clear();
			text.setCharacterSize(120);
			text.setString("       Snake!\n\nPress 'U' to start!");
			text.setPosition(250, 50);
			window.draw(text);
		}
		else if (game->state == RESTART) {
			DestroyGame(game);
			NewGame(game);
			text = game->game_text->text;
			game->state = PLAY;
		}
		else if (game->state == PAUSE) {
			window.clear();
			Render(window, game);
			text.setCharacterSize(150);
			text.setString("Pause");
			text.setPosition(455, 160);
			window.draw(text);
		}
		else if (game->state == PLAY) {
			while (game->consts->time_counter > game->consts->speed) {
				game->consts->time_counter = 0;

				//Snake movement

				Step(game->snake);

				int snake_draw_counter = SnakeLength(game->snake);

				ProcessCollisions(snake_draw_counter, game);
			}
			Render(window, game);
		}
		else if (game->state == ENDGAME) {
			window.clear();
			text.setCharacterSize(120);
			text.setString("       Score: " + ToString(game->consts->score) + "\n Press 'Esc' to exit\n Press 'R' to restart");
			text.setPosition(170, 28);
			window.draw(text);
		}

		window.display();
	}
	DestroyGame(game);
}
