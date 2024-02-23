#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_mushroom_moving[] = {4, 0, 0, 1, 1};

void Start_SpriteMushroom(void) 
{
	THIS->lim_x = 500;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_mushroom_moving, 10);
}

void Update_SpriteMushroom(void) 
{
	//mushroom bounce
	if (CheckCollision(THIS, spr_nutmeg)) {
		PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
		accelY = -600;
		jumpPeak = 0;
		movestate = inair;
	}
}

void Destroy_SpriteMushroom(void) {
}