#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

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
	THIS->custom_data[2] = 0;
	THIS->custom_data[3] = 0;
}


void Update_EnemyButterfly() {
	//up and down
	UINT8 ystep = THIS->custom_data[2];
	UINT8 xstep = THIS->custom_data[3];

	ystep ++;
	if (ystep == 5) 
	{  
		ystep = 0;

		UINT8 ycnt = THIS->custom_data[0];
		ycnt ++;
		if (ycnt < 10)
		{
			TranslateSprite(THIS, 0, -1);
		} else if (ycnt >= 11 && ycnt < 21)
		{
			TranslateSprite(THIS, 0, 1);
		}
		if (ycnt == 22)
		{
			ycnt = 0;
		}
		THIS->custom_data[0] = ycnt;
	}
	THIS->custom_data[2] = ystep;

	xstep ++;
	if (xstep == 10) 
	{ 
		xstep = 0; 
		UINT8 xcnt = THIS->custom_data[1];
		xcnt ++;
		//left and right
		if (xcnt < 20) {
			THIS->mirror = NO_MIRROR;
			TranslateSprite(THIS, 1, 0);
		}
		else if (xcnt >= 22 && xcnt < 42) {
			THIS->mirror = V_MIRROR;
			TranslateSprite(THIS, -1, 0);
		}
		if (xcnt == 43) { xcnt = 0;}
		THIS->custom_data[1] =  xcnt;
	}
	THIS->custom_data[3] = xstep;

	//kill butterfly if jump on it
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg_death == false) {
		if (movestate == inair && accelY > 0)
		{
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
		else
		{
			nutmeg_hit();
		}
	}
}

void Destroy_EnemyButterfly() {
}