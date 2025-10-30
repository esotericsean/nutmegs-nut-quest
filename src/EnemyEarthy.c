#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
/* do not disable PlayFx while diagnosing */
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

static UINT16 earthycounter;
static UINT8 earthydirection;

static const UINT8 anim_earthy_walk[] = {6, 1, 1, 2, 3, 3, 2};

void Start_EnemyEarthy(void) {
	earthycounter = 0;
	earthydirection = 0;
	
	if (level.orientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (level.orientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_earthy_walk, 10);
	THIS->mirror = NO_MIRROR;
	earthydirection = 0;
}

void Update_EnemyEarthy(void) {
	if (earthycounter % 5 == 0) {
		if (earthydirection == 0) TranslateSprite (THIS, -1, 0);
		else if (earthydirection == 1) TranslateSprite (THIS, 1, 0);
	}

	if (earthycounter < 350) {
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
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg.isDying == false) {
		if (nutmeg.movestate == inair && nutmeg.speedY > 0)
		{
			PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
			nutmeg.speedY = -nutmeg.enemyBounceY;
			nutmeg.jumpPeak = 0;

			if (nutmeg.direction == right) 
			{
				AddStarPair (THIS->x, THIS->y+1);
			}
			else
			{
				AddStarPair (THIS->x - 6, THIS->y+1);
			}

			SpriteManagerRemoveSprite (THIS);
		}
		else
		{
			//die if touch earthy
			nutmeg_hit();
		}
	}
}

void Destroy_EnemyEarthy(void) {
}