#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

const UINT8 anim_topspike_idle[] = {1, 0};

void Start_EnemyTopSpike() {
	/*THIS->coll_x = 0;
	THIS->coll_y = 3;
	THIS->coll_w = 8;
	THIS->coll_h = 5;*/

	THIS->lim_x = 400;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_topspike_idle, 1);
	//SPRITE_UNSET_VMIRROR(THIS);
	THIS->mirror = NO_MIRROR;
}

void Update_EnemyTopSpike() {
}

void Destroy_EnemyTopSpike() {
}