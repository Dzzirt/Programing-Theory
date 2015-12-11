#include "assets.h"

void SAssets::Init()
{
	fontMain.loadFromFile(FONT_UBUNTU_TTF);
	martTexture.loadFromFile("mark.png");
}
