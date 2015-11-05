#include "../Headers/message.h"

using namespace sf;

void MessageInit(Message & message) {
	message.font.loadFromFile("Resourses/font.otf");
	message.text.setFont(message.font);
	message.text.setCharacterSize(60);
	message.text.setColor(Color(52, 73, 94));
	message.text.setString("");
}

void DestroyMessage(Message *& message) {
	delete message;
}