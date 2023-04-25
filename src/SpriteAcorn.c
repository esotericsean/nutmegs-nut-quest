#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

#include "GlobalVars.h"

bool isAcornMoving;

const UINT8 anim_acorn_moving[] = {8, 0, 0, 0, 1, 2, 2, 2, 1};
const UINT8 anim_acorn_static[] = {1, 0};

void Start_SpriteAcorn() {
	/*THIS->coll_x = -1;
	THIS->coll_y = -1;
	THIS->coll_w = 10;
	THIS->coll_h = 10;*/

	if (levelorientation == horizontal) {
		THIS->lim_x = 350;
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}
}

void Update_SpriteAcorn() {
	if (isAcornMoving == true) SetSpriteAnim(THIS, anim_acorn_moving, 10);
	else if (isAcornMoving == false) SetSpriteAnim(THIS, anim_acorn_static, 1);
}

void Destroy_SpriteAcorn() {
}