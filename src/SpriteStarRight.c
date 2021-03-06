#include "Banks/SetBank4.h"
#include "SpriteManager.h"

const UINT8 anim_star_1[] = {6, 0, 1, 2, 2, 2, 2};

UINT8 deathtimer = 0;

void Start_SpriteStarRight() {
	THIS->coll_x = 4;
	THIS->coll_y = 4;
	THIS->coll_w = 0;
	THIS->coll_h = 0;

	THIS->lim_x = 2000;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_star_1, 12);

	deathtimer = 0;
}

void Update_SpriteStarRight() {
	if (deathtimer >= 30) SpriteManagerRemoveSprite(THIS);
	else deathtimer++;

	TranslateSprite(THIS, 1, 0);
}

void Destroy_SpriteStarRight() {
}