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
	THIS->y +=7;
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg.isDying == false)
	{
		THIS->y -=7;
		if (nutmeg.movestate == inair && nutmeg.speedY > 0)
		{
			PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
			
			INT16 accly = (nutmeg.enemyBounceY >> 1);
			accly += (nutmeg.enemyBounceY >> 2);
			accly += (nutmeg.enemyBounceY >> 3);
			nutmeg.speedY = -accly;
			nutmeg.jumpPeak = 0;
			
			AddPuffPair (THIS->x+8, THIS->y+2);
		
			// nutmeg can bounce as many times as they want
		}
	}
	else {THIS->y -=7;}
}

void Destroy_SpriteRuby(void) {
}