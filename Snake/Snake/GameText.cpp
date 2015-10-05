#include "GameText.h"

void textInit(GameText * gameText)
{
	gameText->font.loadFromFile("font/font.otf");
	gameText->text.setFont(gameText->font);
	gameText->color.r = 155;
	gameText->color.g = 89;
	gameText->color.b = 182;
	gameText->text.setColor(gameText->color);
	
}