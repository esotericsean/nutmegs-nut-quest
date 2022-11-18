#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "../src/GlobalVars.h"

UINT16 earthycounter = 0;
UINT8 earthydirection = 0;

const UINT8 anim_earthy_walk[] = {6, 1, 1, 2, 3, 3, 2};

void Start_EnemyEarthy() {
	if (levelorientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_earthy_walk, 10);
	THIS->mirror = NO_MIRROR;
	earthydirection = 0;
}

void Update_EnemyEarthy() {
	if (earthycounter % 5 == 0) {
		if (earthydirection == 0) TranslateSprite (THIS, -1, 0);
		else if (earthydirection == 1) TranslateSprite (THIS, 1, 0);
	}

	if (earthycounter >= 0 && earthycounter < 350) {
		if (earthydirection == 1) TranslateSprite (THIS, 4, 0);

		earthydirection = 0; //left
		THIS->mirror = NO_MIRROR;
	}
	else if (earthycounter >= 350 && earthycounter < 700) {
		if (earthydirection == 0) TranslateSprite (THIS, -4, 0);

		earthydirection = 1; //right
		THIS->mirror = V_MIRROR;
	}

	earthycounter++;
	
	if (earthycounter >= 700) earthycounter = 0;
}

void Destroy_EnemyEarthy() {
}