#include "Banks/SetBank6.h"
#include "SpriteManager.h"

UINT8 ruby_counter;
const UINT8 anim_ruby_idle[] = {5, 0, 0, 0, 0, 1};

void Start_SpriteRuby() {
	THIS->coll_x = 8;
	THIS->coll_y = 8;
	THIS->coll_w = 8;
	THIS->coll_h = 8;

	ruby_counter = 0;

	SetSpriteAnim(THIS, anim_ruby_idle, 8);
}

void Update_SpriteRuby() {
	/*
	if (ruby_counter >= 0 && ruby_counter < 128) {
		SetSpriteAnim(THIS, anim_ruby_idle, 10);
	}
	else if (ruby_counter >= 128 && ruby_counter < 208) {
		SetSpriteAnim(THIS, anim_cinnamon_jump, 10);
	}

	ruby_counter++;

	if (ruby_counter >= 208)
		ruby_counter = 0;
	*/
}

void Destroy_SpriteRuby() {
}