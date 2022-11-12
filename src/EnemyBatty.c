#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "../src/GlobalVars.h"

const UINT8 anim_batty_fly[] = {8, 0, 0, 0, 1, 2, 2, 2, 1};

UINT8 battycounter;

void Start_EnemyBatty() {
	if (levelorientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_batty_fly, 22);

	battycounter = 0;
}

void Update_EnemyBatty() {
	if (battycounter >= 0 && battycounter < 30) {
		TranslateSprite(THIS, 0, 1);
	}
	else if (battycounter >= 30 && battycounter < 90) {
		//stay still
	}
	else if (battycounter >= 90 && battycounter < 120) {
		TranslateSprite(THIS, 0, -1);
	}
	else if (battycounter >= 120 && battycounter < 180) {
		//stay still
	}

	battycounter++;

	if (battycounter >= 180) battycounter = 0;
}

void Destroy_EnemyBatty() {
}