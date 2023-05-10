#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"

UINT8 shockline2counter;

const UINT8 anim_shock2_flash[] = {2, 0, 1};
const UINT8 anim_shock2_static[] = {1, 1};

void START() {
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_shock2_flash, 8);

	shockline2counter = 0;
}

void UPDATE() {
	if (shockline2counter < 100) shockline2counter++;

	if (shockline2counter >= 100) SetSpriteAnim(THIS, anim_shock2_static, 1);
}

void DESTROY() {
}