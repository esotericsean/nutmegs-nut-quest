#include "Banks/SetBank2.h"
#include "SpriteManager.h"

UINT8 a = 0; //up and down
UINT8 b = 0; //left and right

const UINT8 anim_butterfly_fly[] = {4, 1, 2, 3, 2};

void Start_EnemyButterfly() {
	THIS->coll_x = 0;
	THIS->coll_y = 1;
	THIS->coll_w = 8;
	THIS->coll_h = 6;

	THIS->lim_x = 9999;
	THIS->lim_y = 999;

	SetSpriteAnim(THIS, anim_butterfly_fly, 6);
	SPRITE_SET_VMIRROR(THIS);
}

void Update_EnemyButterfly() {
	//up and down
	if (a < 100 && a % 5 == 0)
		TranslateSprite(THIS, 0, -1);

	if (a >= 110 && a < 210 && a % 5 == 0)
		TranslateSprite(THIS, 0, 1);

	//left and right
	if (b < 200 && b % 10 == 0) {
		SPRITE_UNSET_VMIRROR(THIS);
		TranslateSprite(THIS, 1, 0);
	}

	if (b >= 210 && b < 310 && b % 10 == 0) {
		SPRITE_SET_VMIRROR(THIS);
		TranslateSprite(THIS, -1, 0);
	}

	a++;
	b++;

	if (a >= 220)
		a = 0;
	
	if (b >= 320)
		b = 0;

	/*
	if (updown == 0 && a < 5) {
		TranslateSprite(THIS, 0, -1);
	}

	if (updown == 1 && a )

	if (a <= 5) {
		a = a + 1;
	}
	else if (a >= 6) {
		a = 0;
		updown = 1;
	}
	*/
}

void Destroy_EnemyButterfly() {
}