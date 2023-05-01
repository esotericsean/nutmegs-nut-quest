#include "Banks/SetAutoBank.h"

#include <gb/cgb.h>
#include <gbdk/platform.h>
#include "Palette.h"

#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "../src/GlobalVars.h"

UINT8 fishcounter = 0; // counter

const UINT8 anim_fish_idle[] = {1, 0};

//fish color palettes
const UWORD pal_fishgreen4[] = { RGB(31, 31, 31), RGB(5,  24, 14), RGB(5,  19, 12), RGB(0,  0,  0) };
const UWORD pal_fishblue4[] =  { RGB(31, 31, 31), RGB(19, 22, 30), RGB(12, 13, 28), RGB(8,  8, 27) };

void Start_EnemyFish() {
	/*THIS->coll_x = 3;
	THIS->coll_y = 3;
	THIS->coll_w = 13;
	THIS->coll_h = 12;*/

	THIS->lim_x = 500;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_fish_idle, 1);
	//SPRITE_SET_VMIRROR(THIS);
	THIS->mirror = V_MIRROR;

	fishcounter = 0;
}

void Update_EnemyFish() {
	if (fishcounter >=  0 && fishcounter < 30) TranslateSprite(THIS, 0, -2);
	if (fishcounter >= 30 && fishcounter < 40) TranslateSprite(THIS, 0, -1);
	if (fishcounter >= 42 && fishcounter < 52) TranslateSprite(THIS, 0, 1);
	if (fishcounter >= 52 && fishcounter < 82) TranslateSprite(THIS, 0, 2);

	if (fishcounter >=  0 && fishcounter < 20) THIS->mirror = V_MIRROR;
	if (fishcounter >= 20 && fishcounter < 40) THIS->mirror = NO_MIRROR;
	if (fishcounter >= 40 && fishcounter < 60) THIS->mirror = V_MIRROR;
	if (fishcounter >= 60 && fishcounter < 80) THIS->mirror = NO_MIRROR;
	if (fishcounter >= 80 && fishcounter < 100) THIS->mirror = V_MIRROR;
	if (fishcounter >= 100 && fishcounter < 120) THIS->mirror = NO_MIRROR;
	if (fishcounter >= 120 && fishcounter < 140) THIS->mirror = V_MIRROR;
	if (fishcounter >= 140 && fishcounter < 156) THIS->mirror = NO_MIRROR;

	/*
	if (fish_pal_loc == 3) {
		if (THIS->y > 112) {
			SetPalette(SPRITES_PALETTE, 3, 1, pal_fishblue4, _current_bank);
		}
		else if (THIS->y <= 112) {
			SetPalette(SPRITES_PALETTE, 3, 1, pal_fishgreen4, _current_bank);
		}
	}
	else if (fish_pal_loc == 4) {
		if (THIS->y > 112) {
			SetPalette(SPRITES_PALETTE, 2, 1, pal_fishblue4, _current_bank);
		}
		else if (THIS->y <= 112) {
			SetPalette(SPRITES_PALETTE, 2, 1, pal_fishgreen4, _current_bank);
		}
	}
	else if (fish_pal_loc == 7) {
		if (THIS->y > 112) {
			SetPalette(SPRITES_PALETTE, 4, 1, pal_fishblue4, _current_bank);
		}
		else if (THIS->y <= 112) {
			SetPalette(SPRITES_PALETTE, 4, 1, pal_fishgreen4, _current_bank);
		}
	}
	*/

	if (THIS->y > 112) {
			SetPalette(SPRITES_PALETTE, fish_pal_loc, 1, pal_fishblue4, _current_bank);
	}
	else if (THIS->y <= 112) {
		SetPalette(SPRITES_PALETTE, fish_pal_loc, 1, pal_fishgreen4, _current_bank);
	}

	fishcounter++;

	if (fishcounter >= 156) fishcounter = 0;
}

void Destroy_EnemyFish() {
}