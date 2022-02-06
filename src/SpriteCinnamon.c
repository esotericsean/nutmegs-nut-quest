#include "Banks/SetBank4.h"
#include "SpriteManager.h"

UINT8 cinnamon_counter;
const UINT8 anim_cinnamon_idle[] = {7, 0, 0, 0, 0, 0, 0, 1};
const UINT8 anim_cinnamon_jump[] = {7, 0, 1, 2, 3, 4, 5, 6};

void Start_SpriteCinnamon() {
	THIS->coll_x = 8;
	THIS->coll_y = 8;
	THIS->coll_w = 8;
	THIS->coll_h = 8;

	cinnamon_counter = 0;

	SetSpriteAnim(THIS, anim_cinnamon_idle, 10);
}

void Update_SpriteCinnamon() {
	if (cinnamon_counter >= 0 && cinnamon_counter < 128) {
		SetSpriteAnim(THIS, anim_cinnamon_idle, 10);
	}
	else if (cinnamon_counter >= 128 && cinnamon_counter < 208) {
		SetSpriteAnim(THIS, anim_cinnamon_jump, 10);
	}

	cinnamon_counter++;

	if (cinnamon_counter >= 208)
		cinnamon_counter = 0;
}

void Destroy_SpriteCinnamon() {
}