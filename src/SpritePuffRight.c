#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

const UINT8 anim_puff_2[] = {7, 0, 1, 2, 3, 4, 5, 6};

UINT8 deathtimer4 = 0;

void Start_SpritePuffRight() {
	/*THIS->coll_x = 4;
	THIS->coll_y = 4;
	THIS->coll_w = 0;
	THIS->coll_h = 0;*/

	THIS->lim_x = 9999;
	THIS->lim_y = 999;

	//SPRITE_SET_VMIRROR(THIS);
	THIS->mirror = V_MIRROR;

	SetSpriteAnim(THIS, anim_puff_2, 32);

	deathtimer4 = 0;
}

void Update_SpritePuffRight() {
	if (deathtimer4 >= 20) SpriteManagerRemoveSprite(THIS);
	else deathtimer4++;

	TranslateSprite(THIS, 1, 0);
}

void Destroy_SpritePuffRight() {
}