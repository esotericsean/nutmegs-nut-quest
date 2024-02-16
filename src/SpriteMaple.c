#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Sound.h"
#include "SpriteManager.h"

#include "../src/GlobalVars.h"

extern Sprite * spr_nutmeg;

static UINT8 maple_counter;
static const UINT8 anim_maple_idle[] = {2, 1, 2};
static const UINT8 anim_maple_jump[] = {9, 1, 2, 3, 4, 5, 6, 7, 0, 1};

void Start_SpriteMaple(void) {
	maple_counter = 0;

	SetSpriteAnim(THIS, anim_maple_idle, 10);

}

void Update_SpriteMaple(void) {
	if (maple_counter >= 0 && maple_counter < 80) {
		SetSpriteAnim(THIS, anim_maple_idle, 10);
	}
	else if (maple_counter >= 80 && maple_counter < 100) {
		SetSpriteAnim(THIS, anim_maple_jump, 10);
	}

	maple_counter++;

	if (maple_counter >= 100)
		maple_counter = 0;

	THIS->y +=7;
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg_death == false)
	{
		THIS->y -=7;
		if (movestate == inair && accelY > 0)
		{
			PlayFx(CHANNEL_1, 10, 0x00, 0x81, 0x83, 0xA3, 0x87);
			accelY = -400;
			jumpPeak = 0;
			movestate = inair;
			
			if (nutmeg_direction == right) {
				SpriteManagerAdd(SpritePuffLeft, THIS->x+0, THIS->y+2);
				SpriteManagerAdd(SpritePuffRight, THIS->x+8, THIS->y+2);
			}
			else if (nutmeg_direction == left) {
				SpriteManagerAdd(SpritePuffLeft, THIS->x+0, THIS->y+2);
				SpriteManagerAdd(SpritePuffRight, THIS->x+8, THIS->y+2);
			}

			// nutmeg can bounce as many times as they want
		}
	}
	else
	{
		THIS->y -=7;
	}
}

void Destroy_SpriteMaple(void) {
}