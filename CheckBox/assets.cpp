#include "assets.h"

void SAssets::Init()
{
	fontMain.loadFromFile(FONT_UBUNTU_TTF);
	markTexture.loadFromFile("mark.png");
}
