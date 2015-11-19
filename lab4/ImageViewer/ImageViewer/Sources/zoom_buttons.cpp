#include "../Headers/zoom_buttons.h"
#include "../Headers/consts_and_enums.h"

using namespace sf;

void ZoomButtonsInit(ZoomButtons& zoom) {
	zoom.zoom_in_texture = new Texture();
	zoom.zoom_out_texture = new Texture();
	zoom.zoom_in = new Sprite();
	zoom.zoom_out = new Sprite();

	zoom.zoom_in_texture->loadFromFile("Resourses/zoom_in_semi_t.png");
	zoom.zoom_out_texture->loadFromFile("Resourses/zoom_out_semi_t.png");
	zoom.zoom_in->setTexture(*zoom.zoom_in_texture);
	zoom.zoom_out->setTexture(*zoom.zoom_out_texture);
}

void ZoomButtonsUpdate(Vector2u win_size, Vector2f win_scale, ZoomButtons& zoom) {
	Vector2u zoom_in_texture_size = zoom.zoom_in->getTexture()->getSize();
	Vector2u zoom_out_texture_size = zoom.zoom_out->getTexture()->getSize();
	float zoom_in_x = (win_size.x - 180) * win_scale.x;
	float zoom_in_y = (win_size.y - 80) * win_scale.y;
	float zoom_out_x = (win_size.x - 120) * win_scale.x;
	float zoom_out_y = (win_size.y - 80) * win_scale.y;

	zoom.zoom_in_texture->setSmooth(true);
	zoom.zoom_in->setPosition(zoom_in_x, zoom_in_y);
	zoom.zoom_in->setTextureRect(IntRect(0, 0, ZoomButtonsWidth, ZoomButtonsHeight));
	zoom.zoom_in->setScale(win_scale.x, win_scale.y);

	zoom.zoom_out_texture->setSmooth(true);
	zoom.zoom_out->setPosition(zoom_out_x, zoom_out_y);
	zoom.zoom_out->setTextureRect(IntRect(0, 0, ZoomButtonsWidth, ZoomButtonsHeight));
	zoom.zoom_out->setScale(win_scale.x, win_scale.y);
}

void DestroyZoomButtons(ZoomButtons*& zoom) {
	delete zoom->zoom_in;
	delete zoom->zoom_out;
	delete zoom->zoom_in_texture;
	delete zoom->zoom_out_texture;
	delete zoom;
}
