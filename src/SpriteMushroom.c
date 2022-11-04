#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

//#include "GlobalVars.h"

const UINT8 anim_mushroom_moving[] = {4, 0, 0, 1, 1};

void Start_SpriteMushroom() {
	/*THIS->coll_x = 0;
	THIS->coll_y = 4;
	THIS->coll_w = 8;
	THIS->coll_h = 4;*/

	THIS->lim_x = 500;
	THIS->lim_y = 144;
}

void Update_SpriteMushroom() {
	SetSpriteAnim(THIS, anim_mushroom_moving, 10);
}

void Destroy_SpriteMushroom() {
}