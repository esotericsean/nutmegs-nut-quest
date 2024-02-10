#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_bunny_idle[] = {1, 0};
static const UINT8 anim_bunny_jump[] = {6, 0, 1, 2, 3, 4, 5};
static const UINT8 anim_bunny_die[] = {1, 6};

void Start_EnemyBunny() {
	if (levelorientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_bunny_idle, 1);
	THIS->mirror = V_MIRROR;

	*((UINT16 *)THIS->custom_data) = 0;
}

void Update_EnemyBunny() {
	
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
	if (c >= 25 && c < 120) {
		SetSpriteAnim(THIS, anim_bunny_jump, 12);
		if (c % 5 == 0)
			TranslateSprite(THIS, 1, 0);
	}
	if (c >= 120 && c < 145) {
		SetSpriteAnim(THIS, anim_bunny_idle, 1);
	}
	if (c >= 145 && c < 171) {
		//SPRITE_SET_VMIRROR(THIS);
		THIS->mirror = V_MIRROR;
		SetSpriteAnim(THIS, anim_bunny_idle, 1);
	}
	if (c >= 171 && c < 267) {
		SetSpriteAnim(THIS, anim_bunny_jump, 12);
		if (c % 5 == 0)
			TranslateSprite(THIS, -1, 0);
	}
	if (c >= 267 && c < 292) {
		SetSpriteAnim(THIS, anim_bunny_idle, 1);
	}

	TranslateSprite (THIS, 0, 1);

	//kill bunny if jump on it
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg_death == false) {
		if (movestate == inair && accelY > 0)
		{
			PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
			isjumping = true;
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
			//die if touch bunny
			nutmeg_hit();
		}
	}
}

void Destroy_EnemyBunny() {
}