#include "Banks/SetBank4.h"
#include "SpriteManager.h"

const UINT8 anim_puff_1[] = {7, 0, 1, 2, 3, 4, 5, 6};

UINT8 deathtimer = 0;

void Start_SpritePuffRight() {
	THIS->coll_x = 4;
	THIS->coll_y = 4;
	THIS->coll_w = 0;
	THIS->coll_h = 0;

	THIS->lim_x = 9999;
	THIS->lim_y = 999;

	SPRITE_SET_VMIRROR(THIS);

	SetSpriteAnim(THIS, anim_puff_1, 32);

	deathtimer = 0;
}

void Update_SpritePuffRight() {
	if (deathtimer >= 20) SpriteManagerRemoveSprite(THIS);
	else deathtimer++;

	TranslateSprite(THIS, 1, 0);
}

void Destroy_SpritePuffRight() {
}