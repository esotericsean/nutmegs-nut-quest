#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"
#include "Sfx.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_bunny_idle[] = {1, 0};
static const UINT8 anim_bunny_jump[] = {6, 0, 1, 2, 3, 4, 5};
static const UINT8 anim_bunny_die[] = {1, 6};

void Start_EnemyBunny(void) {
	if (level.orientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (level.orientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_bunny_idle, 1);
	THIS->mirror = V_MIRROR;

	*((UINT16 *)THIS->custom_data) = 0;
}

void Update_EnemyBunny(void) {
	
	UINT16 c = *(UINT16 *)THIS->custom_data;
	c++;
	if (c >= 292)
		c = 0;
	
	*((UINT16 *)THIS->custom_data) = c;

	if (c < 25) {
		//SPRITE_UNSET_VMIRROR(THIS);
		THIS->mirror = NO_MIRROR;
		SetSpriteAnim(THIS, anim_bunny_idle, 1);
	}
	else if (c >= 25 && c < 120) {
		SetSpriteAnim(THIS, anim_bunny_jump, 12);
		if (c % 5 == 0)
			TranslateSprite(THIS, 1, 0);
	}
	else if (c >= 120 && c < 145) {
		SetSpriteAnim(THIS, anim_bunny_idle, 1);
	}
	else if (c >= 145 && c < 171) {
		//SPRITE_SET_VMIRROR(THIS);
		THIS->mirror = V_MIRROR;
		SetSpriteAnim(THIS, anim_bunny_idle, 1);
	}
	else if (c >= 171 && c < 267) {
		SetSpriteAnim(THIS, anim_bunny_jump, 12);
		if (c % 5 == 0)
			TranslateSprite(THIS, -1, 0);
	}
	else if (c >= 267) {
		SetSpriteAnim(THIS, anim_bunny_idle, 1);
	}

	TranslateSprite (THIS, 0, 1);

	//kill bunny if jump on it
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg.isDying == false) {
		if (nutmeg.movestate == inair && nutmeg.speedY > 0)
		{
            // descending note on stomp
#ifndef USE_CBT_FX
            PlayFx(CHANNEL_1, 6, 0x10, 0xC7, 0xE3, 0xAE, 0x86);
#endif
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
			//die if touch bunny
			nutmeg_hit();
		}
	}
}

void Destroy_EnemyBunny(void) {
}