#include "Banks/SetAutoBank.h"
#ifdef USE_CBT_FX
#include "Sound.h"
#undef PlayFx
#define PlayFx(...) do {} while(0)
#endif
#include "ZGBMain.h"
#include "Sfx.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_butterfly_fly[] = {4, 1, 2, 3, 2};

void Start_EnemyButterfly(void) {
	if (level.orientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (level.orientation == vertical) {
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


void Update_EnemyButterfly(void) {
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
		if (ycnt == 26)
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
		if (xcnt < 10) {
			THIS->mirror = NO_MIRROR;
			TranslateSprite(THIS, 1, 0);
		}
		else if (xcnt >= 11 && xcnt < 22) {
			THIS->mirror = V_MIRROR;
			TranslateSprite(THIS, -1, 0);
		}
		if (xcnt == 25) { xcnt = 0;}
		THIS->custom_data[1] =  xcnt;
	}
	THIS->custom_data[3] = xstep;

	//kill butterfly if jump on it
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg.isDying == false) {
		if (nutmeg.movestate == inair && nutmeg.speedY > 0)
		{
#ifndef USE_CBT_FX
            PlayFx(CHANNEL_1, 6, 0x10, 0xC7, 0xE3, 0xAE, 0x86);
#endif
			nutmeg.speedY = -nutmeg.enemyBounceY;
			nutmeg.jumpPeak = 0;

			AddStarPairWide (THIS->x-4, THIS->y);

			SpriteManagerRemoveSprite (THIS);
			gameStats.totalEnemyKills++;
		}
		else
		{
			nutmeg_hit();
		}
	}
}

void Destroy_EnemyButterfly(void) {
}