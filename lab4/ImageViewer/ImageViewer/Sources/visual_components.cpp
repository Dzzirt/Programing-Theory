#include "../Headers/visual_components.h"

using namespace sf;

void VisualCompInit(VisualComponents & visual) {
	visual.texture = new Texture();
	visual.picture = new Sprite();
	visual.left_arrow_texture = new Texture();
	visual.right_arrow_texture = new Texture();
	visual.left_arrow = new Sprite();
	visual.right_arrow = new Sprite();

	visual.left_arrow_texture->loadFromFile("Resourses/arrow_semi_t.png");
	visual.right_arrow_texture->loadFromFile("Resourses/arrow_semi_t.png");
	visual.left_arrow->setTexture(*visual.left_arrow_texture);
	visual.right_arrow->setTexture(*visual.right_arrow_texture);
	visual.is_img_loaded = true;
}

void DestroyVisComp(VisualComponents*& visual) {
	delete visual->texture;
	delete visual->left_arrow;
	delete visual->right_arrow;
	delete visual->right_arrow_texture;
	delete visual->left_arrow_texture;
	delete visual->picture;
	delete visual;
}
