#pragma once



struct Apple;



struct Apple
{
	int xPos, yPos;
	String fileName;
	Image image;
	Texture texture;
	Sprite sprite;

	Apple()
	{
		draw();
		sprite.setPosition(xPos, yPos);
		image.loadFromFile("images/apple.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 19, 19));
	}

	void draw()
	{
		xPos = (rand() % MAP_WIDTH) * 19;
		yPos = (rand() % MAP_HEIGHT) * 19;
		while (TileMap[yPos / 19][xPos / 19] != ' ')
		{
			xPos = (rand() % MAP_WIDTH) * 19;
			yPos = (rand() % MAP_HEIGHT) * 19;
		}
	}
};