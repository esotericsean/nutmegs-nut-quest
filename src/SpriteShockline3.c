#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"

UINT8 shockline3counter;

const UINT8 anim_shock3_flash[] = {2, 0, 1};
const UINT8 anim_shock3_static[] = {1, 1};

void START() {
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_shock3_flash, 8);

	shockline3counter = 0;
}

void UPDATE() {
	if (shockline3counter < 100) shockline3counter++;

	if (shockline3counter >= 100) SetSpriteAnim(THIS, anim_shock3_static, 1);
}

void DESTROY() {
}