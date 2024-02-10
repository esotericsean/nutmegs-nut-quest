#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

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
	//else if (battycounter >= 30 && battycounter < 90) {
		//stay still
	//}
	else if (battycounter >= 90 && battycounter < 120) {
		TranslateSprite(THIS, 0, -1);
	}
	//else if (battycounter >= 120 && battycounter < 180) {
		//stay still
	//}

	battycounter++;

	if (battycounter >= 180) battycounter = 0;

	//kill batty if jump on it
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
	//die if touch batty
	else if (CheckCollision(THIS, spr_nutmeg) && accelY <= 0 && nutmeg_death == false) {
		nutmeg_hit();
	}
}

void Destroy_EnemyBatty() {
}