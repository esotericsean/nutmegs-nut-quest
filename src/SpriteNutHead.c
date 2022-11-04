#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
#include "Scroll.h"
#include "Keys.h"

const UINT8 anim_nuthead_idle[] = {33,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
									0, 0, 0, 0, 0, 0, 1};

void Start_SpriteNutHead() {
	/*THIS->coll_x = 1;
	THIS->coll_y = 1;
	THIS->coll_w = 1;
	THIS->coll_h = 1;*/

	THIS->lim_x = 9999;
	THIS->lim_y = 999;

	SetSpriteAnim(THIS, anim_nuthead_idle, 9);
}

void Update_SpriteNutHead() {
}

void Destroy_SpriteNutHead() {
}