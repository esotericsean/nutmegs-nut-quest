#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "../src/GlobalVars.h"

const UINT8 anim_birdy_fly[] = {8, 0, 0, 0, 1, 2, 2, 2, 1};

UINT8 birdycounter;

void Start_EnemyBirdy() {
	if (levelorientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_birdy_fly, 22);

	birdycounter = 0;
}

void Update_EnemyBirdy() {
	if (birdycounter >= 0 && birdycounter < 30) {
		TranslateSprite(THIS, 0, 1);
	}
	else if (birdycounter >= 30 && birdycounter < 90) {
		//stay still
	}
	else if (birdycounter >= 90 && birdycounter < 120) {
		TranslateSprite(THIS, 0, -1);
	}
	else if (birdycounter >= 120 && birdycounter < 180) {
		//stay still
	}

	birdycounter++;

	if (birdycounter >= 180) birdycounter = 0;
}

void Destroy_EnemyBirdy() {
}