#include "../Headers/visual_components.h"

using namespace sf;

void VisualCompInit(VisualComponents & visual) {
	visual.texture = new Texture();
	visual.picture = new Sprite();
	visual.is_img_loaded = true;
	visual.arrow = new Arrow();
	ArrowInit(*visual.arrow);
	visual.zoom_buttons = new ZoomButtons();
	ZoomButtonsInit(*visual.zoom_buttons);
	visual.pic_increase = false;
	visual.pic_decrease = false;
	visual.pic_less_than_win = true;
}

void DestroyVisComp(VisualComponents*& visual) {
	delete visual->texture;
	delete visual->picture;
	DestroyArrow(visual->arrow);
	delete visual;
}
