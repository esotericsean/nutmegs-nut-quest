#include "Banks/SetBank6.h"
#include "SpriteManager.h"

const UINT8 powerleaf_bounce[] = {8, 0, 0, 0, 1, 2, 2, 2, 1};

void Start_SpritePowerLeaf() {
	THIS->coll_x = 0;
	THIS->coll_y = 0;
	THIS->coll_w = 8;
	THIS->coll_h = 8;

	THIS->lim_x = 9999;
	THIS->lim_y = 999;

	SetSpriteAnim(THIS, powerleaf_bounce, 16);
}

void Update_SpritePowerLeaf() {
}

void Destroy_SpritePowerLeaf() {
}