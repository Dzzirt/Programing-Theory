#pragma once

const int MAP_HEIGHT = 10;
const int MAP_WIDTH = 20;
struct Map;

struct Map
{
	Image image;
	Texture texture;
	Sprite sprite;

	Map()
	{
		image.loadFromFile("images/map.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};

String TileMap[MAP_HEIGHT] = {
	"     1111111111     ",
	"                    ",
	"                    ",
	"1                  1",
	"1                  1",
	"1                  1",
	"1                  1",
	"                    ",
	"                    ",
	"     1111111111     "
};