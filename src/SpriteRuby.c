#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Sound.h"
#include "SpriteManager.h"

#include "../src/GlobalVars.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_ruby_idle[] = {5, 0, 0, 0, 0, 1};

void Start_SpriteRuby(void) {
	SetSpriteAnim(THIS, anim_ruby_idle, 8);
}

void Update_SpriteRuby(void) {
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg_death == false)
	{
		if (movestate == inair && accelY > 0)
		{
			PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
			
			accelY = -600;
			jumpPeak = 0;
			movestate = inair;
			
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
}

void Destroy_SpriteRuby(void) {
}