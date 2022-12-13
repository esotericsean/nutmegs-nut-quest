#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

const UINT8 anim_star_2[] = {6, 0, 1, 2, 2, 2, 2};

UINT8 deathtimer2 = 0;

void Start_SpriteStarRight() {
	/*THIS->coll_x = 4;
	THIS->coll_y = 4;
	THIS->coll_w = 0;
	THIS->coll_h = 0;*/

	THIS->lim_x = 2000;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_star_2, 12);

	deathtimer2 = 0;
}

void Update_SpriteStarRight() {
	if (deathtimer2 >= 30) SpriteManagerRemoveSprite(THIS);
	else deathtimer2++;

	//TranslateSprite(THIS, 1, 0);
	THIS->x++;
}

void Destroy_SpriteStarRight() {
}