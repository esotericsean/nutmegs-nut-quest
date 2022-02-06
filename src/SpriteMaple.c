#include "Banks/SetBank4.h"
#include "SpriteManager.h"

UINT8 maple_counter;
const UINT8 anim_maple_idle[] = {2, 1, 2};
const UINT8 anim_maple_jump[] = {9, 1, 2, 3, 4, 5, 6, 7, 0, 1};

void Start_SpriteMaple() {
	THIS->coll_x = 8;
	THIS->coll_y = 8;
	THIS->coll_w = 8;
	THIS->coll_h = 8;

	maple_counter = 0;

	SetSpriteAnim(THIS, anim_maple_idle, 10);
}

void Update_SpriteMaple() {
	if (maple_counter >= 0 && maple_counter < 80) {
		SetSpriteAnim(THIS, anim_maple_idle, 10);
	}
	else if (maple_counter >= 80 && maple_counter < 100) {
		SetSpriteAnim(THIS, anim_maple_jump, 10);
	}

	maple_counter++;

	if (maple_counter >= 100)
		maple_counter = 0;
}

void Destroy_SpriteMaple() {
}