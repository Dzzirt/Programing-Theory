#include "../Headers/arrow.h"
#include "../Headers/consts_and_enums.h"

using namespace sf;

void ArrowInit(Arrow & arrow) {
	arrow.left_arrow_texture = new Texture();
	arrow.right_arrow_texture = new Texture();
	arrow.left_arrow = new Sprite();
	arrow.right_arrow = new Sprite();

	arrow.left_arrow_texture->loadFromFile("Resourses/arrow_semi_t.png");
	arrow.right_arrow_texture->loadFromFile("Resourses/arrow_semi_t.png");
	arrow.left_arrow->setTexture(*arrow.left_arrow_texture);
	arrow.right_arrow->setTexture(*arrow.right_arrow_texture);
}

void DestroyArrow(Arrow*& arrow) {
	delete arrow->left_arrow;
	delete arrow->right_arrow;
	delete arrow->right_arrow_texture;
	delete arrow->left_arrow_texture;
	delete arrow;
}

void ArrowUpdate(Vector2u win_size, Vector2f win_scale, Arrow & arrow) {
	Vector2u left_arrow_texture_size = arrow.left_arrow->getTexture()->getSize();
	Vector2u right_arrow_texture_size = arrow.right_arrow->getTexture()->getSize();
	float w_scale_x = win_scale.x;
	float w_scale_y = win_scale.y;
	float l_arr_x = ArrowMarg * w_scale_x;
	float l_arr_y = (win_size.y / 2.f) * w_scale_y;
	float r_arr_x = (win_size.x - right_arrow_texture_size.x - ArrowMarg) * w_scale_x;
	float r_arr_y = win_size.y / 2.f * w_scale_y;

	arrow.left_arrow_texture->setSmooth(true);
	arrow.left_arrow->setOrigin(0, left_arrow_texture_size.y / 2.f);
	arrow.left_arrow->setPosition(l_arr_x, l_arr_y);
	arrow.left_arrow->setTextureRect(IntRect(ArrowWidth, 0, -ArrowWidth, ArrowhHeight));
	arrow.left_arrow->setScale(w_scale_x, w_scale_y);

	arrow.right_arrow_texture->setSmooth(true);
	arrow.right_arrow->setOrigin(0, right_arrow_texture_size.y / 2.f);
	arrow.right_arrow->setPosition(r_arr_x, r_arr_y);
	arrow.right_arrow->setTextureRect(IntRect(0, 0, ArrowWidth, ArrowhHeight));
	arrow.right_arrow->setScale(w_scale_x, w_scale_y);
}