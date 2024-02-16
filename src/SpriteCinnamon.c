#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Sound.h"
#include "SpriteManager.h"

#include "../src/GlobalVars.h"

extern Sprite * spr_nutmeg;

static UINT8 cinnamon_counter;
static const UINT8 anim_cinnamon_idle[] = {7, 0, 0, 0, 0, 0, 0, 1};
static const UINT8 anim_cinnamon_jump[] = {7, 0, 1, 2, 3, 4, 5, 6};

void Start_SpriteCinnamon(void) {
	cinnamon_counter = 0;

	SetSpriteAnim(THIS, anim_cinnamon_idle, 10);
}

void Update_SpriteCinnamon(void) {

	if (cinnamon_counter < 128) {
		SetSpriteAnim(THIS, anim_cinnamon_idle, 10);
	}
	else if (cinnamon_counter >= 128 && cinnamon_counter < 208) {
		SetSpriteAnim(THIS, anim_cinnamon_jump, 10);
	}

	cinnamon_counter++;

	if (cinnamon_counter >= 208)
		cinnamon_counter = 0;

	THIS->y +=7;
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg_death == false)
	{
		THIS->y -=7;
		if (movestate == inair && accelY > 0)
		{
			PlayFx(CHANNEL_4, 60, 0x3a, 0xf2, 0x62, 0x80);
			accelY = -400;
			jumpPeak = 0;
			movestate = inair;
			
			SetSpriteAnim(THIS, anim_cinnamon_idle, 10);
			cinnamon_counter = 0;

			if (nutmeg_direction == right) {
				SpriteManagerAdd(SpritePuffLeft, THIS->x+8, THIS->y+2);
				SpriteManagerAdd(SpritePuffRight, THIS->x+16, THIS->y+2);
			}
			else if (nutmeg_direction == left) {
				SpriteManagerAdd(SpritePuffLeft, THIS->x+8, THIS->y+2);
				SpriteManagerAdd(SpritePuffRight, THIS->x+16, THIS->y+2);
			}

			// nutmeg can bounce as many times as they want
		}
	}
	else {THIS->y -=7;}
}

void Destroy_SpriteCinnamon(void) {
}