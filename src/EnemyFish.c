#include "Banks/SetAutoBank.h"
#include <gb/cgb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Palette.h"
#include "../src/GlobalVars.h"

extern Sprite * nutmeg_sprite;

static UINT8 fishcounter = 0; // counter

static const UINT8 anim_fish_idle[] = {1, 0};

//fish color palettes
static const UWORD pal_fishgreen4[] = { RGB(31, 31, 31), RGB(5,  24, 14), RGB(5,  19, 12), RGB(0,  0,  0) };
static const UWORD pal_fishblue4[] =  { RGB(31, 31, 31), RGB(19, 22, 30), RGB(12, 13, 28), RGB(8,  8, 27) };

void Start_EnemyFish() {
	THIS->lim_x = 500;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_fish_idle, 1);
	THIS->mirror = V_MIRROR;

	fishcounter = 0;
}

void Update_EnemyFish() {
	if (fishcounter < 30) TranslateSprite(THIS, 0, -2);
	if (fishcounter >= 30 && fishcounter < 40) TranslateSprite(THIS, 0, -1);
	if (fishcounter >= 42 && fishcounter < 52) TranslateSprite(THIS, 0, 1);
	if (fishcounter >= 52 && fishcounter < 82) TranslateSprite(THIS, 0, 2);

	if (fishcounter < 20) THIS->mirror = V_MIRROR;
	if (fishcounter >= 20 && fishcounter < 40) THIS->mirror = NO_MIRROR;
	if (fishcounter >= 40 && fishcounter < 60) THIS->mirror = V_MIRROR;
	if (fishcounter >= 60 && fishcounter < 80) THIS->mirror = NO_MIRROR;
	if (fishcounter >= 80 && fishcounter < 100) THIS->mirror = V_MIRROR;
	if (fishcounter >= 100 && fishcounter < 120) THIS->mirror = NO_MIRROR;
	if (fishcounter >= 120 && fishcounter < 140) THIS->mirror = V_MIRROR;
	if (fishcounter >= 140 && fishcounter < 156) THIS->mirror = NO_MIRROR;

	if (THIS->y > 112) {
			SetPalette(SPRITES_PALETTE, fish_pal_loc, 1, pal_fishblue4, _current_bank);
	}
	else if (THIS->y <= 112) {
		SetPalette(SPRITES_PALETTE, fish_pal_loc, 1, pal_fishgreen4, _current_bank);
	}

	fishcounter++;

	if (fishcounter >= 156) fishcounter = 0;

	if (CheckCollision(THIS, nutmeg_sprite) && movestate == inair && accelY > 0) {
		PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
		isjumping = true;
		accelY = -600;
		jumpPeak = 0;
		movestate = inair;

		SpriteManagerAdd(SpriteStarLeft, THIS->x, THIS->y+2);
		SpriteManagerAdd(SpriteStarRight, THIS->x+8, THIS->y+2);

		SpriteManagerRemoveSprite (THIS);
	}
}

void Destroy_EnemyFish() {
}