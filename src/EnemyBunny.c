#include "Banks/SetBank2.h"
#include "SpriteManager.h"

UINT16 c = 0; // counter

const UINT8 anim_bunny_idle[] = {1, 0};
const UINT8 anim_bunny_jump[] = {6, 0, 1, 2, 3, 4, 5};
const UINT8 anim_bunny_die[] = {1, 6};

void Start_EnemyBunny() {
	THIS->coll_x = 5;
	THIS->coll_y = 10;
	THIS->coll_w = 9;
	THIS->coll_h = 5;

	THIS->lim_x = 400;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_bunny_idle, 1);
	SPRITE_SET_VMIRROR(THIS);
}

void Update_EnemyBunny() {
	if (c < 25) {
		SPRITE_UNSET_VMIRROR(THIS);
		SetSpriteAnim(THIS, anim_bunny_idle, 1);
	}
	if (c >= 25 && c < 120) {
		SetSpriteAnim(THIS, anim_bunny_jump, 12);
		if (c % 5 == 0)
			TranslateSprite(THIS, 1, 0);
	}
	if (c >= 120 && c < 145) {
		SetSpriteAnim(THIS, anim_bunny_idle, 1);
	}
	if (c >= 145 && c < 171) {
		SPRITE_SET_VMIRROR(THIS);
		SetSpriteAnim(THIS, anim_bunny_idle, 1);
	}
	if (c >= 171 && c < 267) {
		SetSpriteAnim(THIS, anim_bunny_jump, 12);
		if (c % 5 == 0)
			TranslateSprite(THIS, -1, 0);
	}
	if (c >= 267 && c < 292) {
		SetSpriteAnim(THIS, anim_bunny_idle, 1);
	}

	c++;

	if (c >= 292)
		c = 0;
}

void Destroy_EnemyBunny() {
}