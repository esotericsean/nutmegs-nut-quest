#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * nutmeg_sprite;

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

	//kill earthy if jump on it
	if (CheckCollision(THIS, nutmeg_sprite) && movestate == inair && accelY > 0 && nutmeg_death == false) {
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
	//die if touch earthy
	else if (CheckCollision(THIS, nutmeg_sprite) && movestate == grounded && nutmeg_death == false) {
		nutmeg_hit();
	}
}

void Destroy_EnemyEarthy() {
}