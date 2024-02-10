#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

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

	//kill birdy if jump on it
	if (CheckCollision(THIS, spr_nutmeg) && movestate == inair && accelY > 0 && nutmeg_death == false) {
		PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
		isjumping = true;
		accelY = -600;
		jumpPeak = 0;
		movestate = inair;
		
		if (nutmeg_direction == right) {
			SpriteManagerAdd(SpriteStarLeft, THIS->x, THIS->y+1);
			SpriteManagerAdd(SpriteStarRight, THIS->x, THIS->y+1);
		}
		else if (nutmeg_direction == left) {
			SpriteManagerAdd(SpriteStarLeft, THIS->x-6, THIS->y+1);
			SpriteManagerAdd(SpriteStarRight, THIS->x-6, THIS->y+1);
		}

		SpriteManagerRemoveSprite (THIS);
	}
	//die if touch birdy
	else if (CheckCollision(THIS, spr_nutmeg) && accelY <= 0 && nutmeg_death == false) {
		nutmeg_hit();
	}
}

void Destroy_EnemyBirdy() {
}