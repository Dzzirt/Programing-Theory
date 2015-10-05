#pragma once
#include "methods.h"
#include "sstream"
#include "Game.h"
#define HEAD snake[0]



std::string toString(int val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

void newMap(Game * game)
{
	game->map = new Map();
	mapInit(game->map);
}
void newApple(Game * game)
{
	game->apple = new Apple();
	appleInit(game->apple);
}
void newSnake(Game * game)
{
	game->snake = new SnakeParts[50];
	snakeInit(game->snake);
	headInit(game->snake);
}
void newText(Game * game)
{
	game->gameText = new GameText;
	textInit(game->gameText);
}
void initGame(Game * game)
{
	newApple(game);
	newMap(game);
	newSnake(game);
	newText(game);
	game->score = 0;
	game->timeCounter = 0.f;
	game->speed = 0.2f;
	game->state = STARTGAME;
}

void newGame(Game * &game)
{
	game = new Game;
	initGame(game);
}

void destroyGame(Game * game)
{
	destroyApple(game->apple);
	destroyMap(game->map);
	destroySnake(game->snake);
	destroyText(game->gameText);
	delete game;
}
void destroySnake(SnakeParts * snake)
{
	delete[] snake;
}
void destroyApple(Apple * apple)
{
	delete apple;
}
void destroyMap(Map * map)
{
	delete map;
}
void destroyText(GameText * text)
{
	delete text;
}

void appleSpawn(int snakeDrawCounter, Game * game)
{
	Apple * apple = game->apple;
	SnakeParts * snake = game->snake;

	bool safe = true;
	do
	{
		appleDraw(apple);
		for (int i = 0; i < snakeDrawCounter; i++)
		{
			if (snake[i].xPos == apple->xPos && snake[i].yPos == apple->yPos)
			{
				safe = false;
				break;
			}
			safe = true;
		}
	}
	while (safe != true);

	apple->sprite.setPosition(apple->xPos, apple->yPos);
}

void eatApple(int snakeDrawCounter, Game * game)
{
	SnakeParts * snake = game->snake;
	game->score += 9;
	game->speed -= 0.005f;
	snake[snakeDrawCounter].draw = true;
	snake[snakeDrawCounter].sprite.setPosition(snake[snakeDrawCounter - 1].xStore, snake[snakeDrawCounter - 1].yStore);
}

int snakeLength(SnakeParts * snake)
{
	int snakeDrawCounter = 0;
	for (int i = 0; i < 50; i++)
	{
		if (snake[i].draw == true)
		{
			snakeDrawCounter++;
		}
	}
	return snakeDrawCounter;
}

void step(SnakeParts * snake)
{
	storeXY(snake);

	if ((HEAD.dir == 3) && (HEAD.yPos == 0))
	{
		HEAD.yPos = (MAP_HEIGHT - 1) * 19;
		HEAD.sprite.setPosition(HEAD.xPos, HEAD.yPos);
	}
	else if (HEAD.dir == 2 && HEAD.yPos == (MAP_HEIGHT - 1) * 19)
	{
		HEAD.yPos = 0;
		HEAD.sprite.setPosition(HEAD.xPos, HEAD.yPos);
	}
	else if (HEAD.dir == 1 && HEAD.xPos == 0)
	{
		HEAD.xPos = (MAP_WIDTH - 1) * 19;
		HEAD.sprite.setPosition(HEAD.xPos, HEAD.yPos);
	}
	else if (HEAD.dir == 0 && HEAD.xPos == (MAP_WIDTH - 1) * 19)
	{
		HEAD.xPos = 0;
		HEAD.sprite.setPosition(HEAD.xPos, HEAD.yPos);
	}
	else snakeUpdate(snake);

	for (int i = 1; i < 50; i++)
	{
		if (snake[i].draw == 1)
		{
			storeXY(snake + i);
			snake[i].xPos = snake[i - 1].xStore;
			snake[i].yPos = snake[i - 1].yStore;
			snake[i].sprite.setPosition(snake[i].xPos, snake[i].yPos);
		}
	}
}

void processEvents(RenderWindow & window, Game * game)
{
	SnakeParts * snake = game->snake;
	Event event;
	while (window.pollEvent(event))
	{
		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::W) && HEAD.dir != 2)
		{
			HEAD.dir = 3;
		}
		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::S) && HEAD.dir != 3)
		{
			HEAD.dir = 2;
		}
		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::A) && HEAD.dir != 0)
		{
			HEAD.dir = 1;
		}
		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::D) && HEAD.dir != 1)
		{
			HEAD.dir = 0;
		}

		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::P))
		{
			game->state = PAUSE;
		}
		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::U))
		{
			game->state = PLAY;
		}
		if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::R) && game->state == ENDGAME)
		{
			
			game->state = RESTART;
		}
		if (event.type == Event::Closed || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape) && game->state == ENDGAME))
			window.close();
	}
}

void headInit(SnakeParts * snake)
{
	HEAD.xPos = 190;
	HEAD.yPos = 95;
	HEAD.sprite.setPosition(190, 95);
	HEAD.draw = true;
}

void render(RenderWindow & window, Game * game)
{
	SnakeParts * snake = game->snake;
	Map * map = game->map;
	Apple * apple = game->apple;
	window.clear();

	//Map draw

	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (TileMap[i][j] == ' ') map->sprite.setTextureRect(IntRect(0, 0, 19, 19));
			if (TileMap[i][j] == '1') map->sprite.setTextureRect(IntRect(19, 0, 19, 19));
			map->sprite.setPosition(j * 19.f, i * 19.f);
			window.draw(map->sprite);
		}

	//Snake draw

	for (int i = 0; i < 50; ++i)
	{
		if (snake[i].draw == true)
		{
			window.draw(snake[i].sprite);
		}
	}

	//Apple draw

	window.draw(apple->sprite);
}

void processCollisions(int snakeDrawCounter, Game * game)
{
	SnakeParts * snake = game->snake;
	Apple * apple = game->apple;
	//Collision with Walls

	
	if (TileMap[(int)(HEAD.yPos / 19)][(int)(HEAD.xPos / 19)] == '1')
	{
		game->state = ENDGAME;
	}
	
	

	//Collision with itself

	for (int i = 1; i < snakeDrawCounter; i++)
	{
		if (snake[i].xPos == HEAD.xPos && snake[i].yPos == HEAD.yPos)
		{
			game->state = ENDGAME;
		}
	}


	//Interact with Apple

	if (apple->xPos == HEAD.xPos && apple->yPos == HEAD.yPos)
	{
		eatApple(snakeDrawCounter, game);
		appleSpawn(snakeDrawCounter, game);
	}
}

void gameStart()
{
	RenderWindow window(VideoMode(MAP_WIDTH * 19, MAP_HEIGHT * 19), "Snake");
	Clock clock;
	Game * game;
	newGame(game);
	Text text = game->gameText->text;

	while (window.isOpen()) //разбить на 3 метода
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		game->timeCounter += time;

		processEvents(window, game);

		if (game->state == STARTGAME)
		{
			window.clear();
			text.setCharacterSize(50);
			text.setString("       Snake!\nPress 'U' to start!");
			text.setPosition(4, 10);
			window.draw(text);
		}

		if (game->state == RESTART)
		{
			destroyGame(game);
			newGame(game);
			text = game->gameText->text;
			game->state = PLAY;
		}
		if (game->state == PAUSE)
		{
			window.clear();
			render(window, game);
			text.setCharacterSize(50);
			text.setString("Pause");
			text.setPosition(122, 50);
			window.draw(text);
		
		}

		if (game->state == PLAY)
		{
			if (game->timeCounter > game->speed)
			{
				game->timeCounter = 0;

				//Snake movement

				step(game->snake);

				int snakeDrawCounter = snakeLength(game->snake);

				processCollisions(snakeDrawCounter, game);
			}
			render(window, game);
			
		}

		if (game->state == ENDGAME)
		{
			window.clear();
			text.setCharacterSize(40);
			text.setString(" Score: " + toString(game->score) + "\n Press 'Esc' to exit\n Press 'R' to restart");
			text.setPosition(14, 28);
			window.draw(text);
		}

		window.display();
	}
	destroyGame(game);
}
