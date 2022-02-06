#include "Banks/SetBank2.h"

#include "SpriteManager.h"

const UINT8 anim_fire[] = {3, 7, 8, 9}; //The first number indicates the number of frames
const UINT8 anim_fireburst[] = {16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5};

BYTE fireburst;
UINT8 i;

void Start_SpriteFire() {
	fireburst = 0;
	i = 1;
}

void Update_SpriteFire() {
	if (fireburst == 0) {
		SetSpriteAnim(THIS, anim_fireburst, 15);
	} else {
		SetSpriteAnim(THIS, anim_fire, 15);
	}

	if (i < 105) {
		i = i + 1;
	} else {
		fireburst = 1;
	}
}

void Destroy_SpriteFire() {
}