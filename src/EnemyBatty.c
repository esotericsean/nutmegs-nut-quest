#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_batty_fly[] = {8, 0, 0, 0, 1, 2, 2, 2, 1};

static UINT8 battycounter;

void Start_EnemyBatty(void) {
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

void Update_EnemyBatty(void) {
	if (battycounter < 30) {
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
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg_death == false) {
		if (movestate == inair && accelY > 0)
		{
			PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
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
		else
		{
			//die if touch batty
			nutmeg_hit();
		}
	}
}

void Destroy_EnemyBatty(void) {
}