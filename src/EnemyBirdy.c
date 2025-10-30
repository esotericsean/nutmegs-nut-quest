#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Sfx.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
/* do not disable PlayFx while diagnosing */
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_birdy_fly[] = {8, 0, 0, 0, 1, 2, 2, 2, 1};

void Start_EnemyBirdy(void) {
	if (level.orientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (level.orientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_birdy_fly, 22);

	THIS->custom_data[0] = 0;
}

void Update_EnemyBirdy(void) {
	if (THIS->custom_data[0] < 30) {
		TranslateSprite(THIS, 0, 1);
	}
	else if (THIS->custom_data[0] >= 90 && THIS->custom_data[0] < 120) {
		TranslateSprite(THIS, 0, -1);
	}
	else
	{ 
		//stay still
	}

	THIS->custom_data[0]++;

	if (THIS->custom_data[0] >= 180) 
	{ 
		THIS->custom_data[0] = 0;
	}

	//kill birdy if jump on it
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg.isDying == false) {
		if (nutmeg.movestate == inair && nutmeg.speedY > 0)
		{
            PlayFx(CHANNEL_1, 6, 0x10, 0xC7, 0xE3, 0xAE, 0x86);
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
            gameStats.totalEnemyKills++;
		}
		else
		{
			//die if touch birdy
			nutmeg_hit();
		}
	}
}

void Destroy_EnemyBirdy(void) {
}