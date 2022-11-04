#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

const UINT8 anim_puff_1[] = {7, 0, 1, 2, 3, 4, 5, 6};

UINT8 deathtimer3 = 0;

void Start_SpritePuffLeft() {
	/*THIS->coll_x = 4;
	THIS->coll_y = 4;
	THIS->coll_w = 0;
	THIS->coll_h = 0;*/

	THIS->lim_x = 9999;
	THIS->lim_y = 999;

	//SPRITE_UNSET_VMIRROR(THIS);
	THIS->mirror = NO_MIRROR;

	SetSpriteAnim(THIS, anim_puff_1, 32);

	deathtimer3 = 0;
}

void Update_SpritePuffLeft() {
	if (deathtimer3 >= 20) SpriteManagerRemoveSprite(THIS);
	else deathtimer3++;

	TranslateSprite(THIS, -1, 0);
}

void Destroy_SpritePuffLeft() {
}