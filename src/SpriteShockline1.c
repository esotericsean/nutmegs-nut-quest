#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"

UINT8 shockline1counter;

const UINT8 anim_shock1_flash[] = {2, 0, 1};
const UINT8 anim_shock1_static[] = {1, 1};

void START() {
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_shock1_flash, 8);

	shockline1counter = 0;
}

void UPDATE() {
	if (shockline1counter < 100) shockline1counter++;

	if (shockline1counter >= 100) SetSpriteAnim(THIS, anim_shock1_static, 1);
}

void DESTROY() {
}