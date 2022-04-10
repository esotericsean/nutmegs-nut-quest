#include "Banks/SetBank2.h"
#include "SpriteManager.h"

#include "GlobalVars.h"

//bool isAcornMoving;

const UINT8 anim_mushroom_moving[] = {4, 0, 0, 1, 1};

void Start_SpriteMushroom() {
	THIS->coll_x = -1;
	THIS->coll_y = -1;
	THIS->coll_w = 10;
	THIS->coll_h = 10;

	THIS->lim_x = 9999;
	THIS->lim_y = 999;
}

void Update_SpriteMushroom() {
	SetSpriteAnim(THIS, anim_mushroom_moving, 10);
}

void Destroy_SpriteMushroom() {
}