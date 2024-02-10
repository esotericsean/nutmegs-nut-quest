#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * nutmeg_sprite;

static const UINT8 anim_butterfly_fly[] = {4, 1, 2, 3, 2};

void Start_EnemyButterfly() {
	if (levelorientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_butterfly_fly, 6);
	THIS->mirror = V_MIRROR;
	THIS->custom_data[0] = 0;
	THIS->custom_data[1] = 0;
}

void Update_EnemyButterfly() {
	//up and down
	UINT8 a = THIS->custom_data[0];
	UINT8 b = THIS->custom_data[1];

	if (a < 100 && a % 5 == 0)
		TranslateSprite(THIS, 0, -1);

	if (a >= 110 && a < 210 && a % 5 == 0)
		TranslateSprite(THIS, 0, 1);

	//left and right
	if (b < 200 && b % 10 == 0) {
		THIS->mirror = NO_MIRROR;
		TranslateSprite(THIS, 1, 0);
	}

	if (b >= 210 && b % 10 == 0) {
		THIS->mirror = V_MIRROR;
		TranslateSprite(THIS, -1, 0);
	}

	THIS->custom_data[0]++;
	THIS->custom_data[1]++;

	if (THIS->custom_data[0] >= 220)
	{
		THIS->custom_data[0] = 0;
	}
	
	//kill butterfly if jump on it
	if (CheckCollision(THIS, nutmeg_sprite) && movestate == inair && accelY > 0 && nutmeg_death == false) {
		PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
		isjumping = true; 
		accelY = -600;
		jumpPeak = 0;
		movestate = inair;
		
		if (nutmeg_direction == right) {
			SpriteManagerAdd(SpriteStarLeft, THIS->x-4, THIS->y);
			SpriteManagerAdd(SpriteStarRight, THIS->x+4, THIS->y);
		}
		else if (nutmeg_direction == left) {
			SpriteManagerAdd(SpriteStarLeft, THIS->x-4, THIS->y);
			SpriteManagerAdd(SpriteStarRight, THIS->x+4, THIS->y);
		}

		SpriteManagerRemoveSprite (THIS);
	}
	
	//die if touch butterfly
	else if (CheckCollision(THIS, nutmeg_sprite) && accelY <= 0 && nutmeg_death == false) {
		nutmeg_hit();
	}
}

void Destroy_EnemyButterfly() {
}