#include "game_text.h"

void TextInit(GameText* game_text) {
	game_text->font.loadFromFile("font/font.otf");
	game_text->text.setFont(game_text->font);
	game_text->color.r = 155;
	game_text->color.g = 89;
	game_text->color.b = 182;
	game_text->text.setColor(game_text->color);

}
