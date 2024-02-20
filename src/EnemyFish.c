#include "Banks/SetAutoBank.h"
#include <gb/cgb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Palette.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

static UINT8 c = 0; // counter

static const UINT8 anim_fish_idle[] = {1, 0};

//fish color palettes
static const UWORD pal_fishgreen4[] = { RGB(31, 31, 31), RGB(5,  24, 14), RGB(5,  19, 12), RGB(0,  0,  0) };
static const UWORD pal_fishblue4[] =  { RGB(31, 31, 31), RGB(19, 22, 30), RGB(12, 13, 28), RGB(8,  8, 27) };

void Start_EnemyFish (void) 
{
	THIS->lim_x = 500;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_fish_idle, 1);
	THIS->mirror = V_MIRROR;

	THIS->custom_data[0] = 0;
}

void Update_EnemyFish (void) 
{
	UINT8 c = THIS->custom_data[0];
	if (c < 30) TranslateSprite(THIS, 0, -2);
	if (c >= 30 && c < 40) TranslateSprite(THIS, 0, -1);
	if (c >= 42 && c < 52) TranslateSprite(THIS, 0, 1);
	if (c >= 52 && c < 82) TranslateSprite(THIS, 0, 2);

	if (c < 20) THIS->mirror = V_MIRROR;
	if (c >= 20 && c < 40) THIS->mirror = NO_MIRROR;
	if (c >= 40 && c < 60) THIS->mirror = V_MIRROR;
	if (c >= 60 && c < 80) THIS->mirror = NO_MIRROR;
	if (c >= 80 && c < 100) THIS->mirror = V_MIRROR;
	if (c >= 100 && c < 120) THIS->mirror = NO_MIRROR;
	if (c >= 120 && c < 140) THIS->mirror = V_MIRROR;
	if (c >= 140 && c < 156) THIS->mirror = NO_MIRROR;

	if (THIS->y > 112) 
	{
			SetPalette(SPRITES_PALETTE, SPRITE_GET_CGB_PALETTE(THIS), 1, pal_fishblue4, _current_bank);
	}
	else if (THIS->y <= 112) 
	{
		SetPalette(SPRITES_PALETTE, SPRITE_GET_CGB_PALETTE(THIS), 1, pal_fishgreen4, _current_bank);
	}

	c++;
	if (c >= 156) c = 0;
	THIS->custom_data[0] = c;

	if (CheckCollision(THIS, spr_nutmeg) && (nutmeg_death == false)){
		if (movestate == inair && accelY > 0) 
		{
			PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
			accelY = -600;
			jumpPeak = 0;
			movestate = inair;

			SpriteManagerAdd(SpriteStarLeft, THIS->x, THIS->y+2);
			SpriteManagerAdd(SpriteStarRight, THIS->x+8, THIS->y+2);

			SpriteManagerRemoveSprite (THIS);
		}
		else
		{
			nutmeg_hit();
		}
	}
	
}

void Destroy_EnemyFish (void) 
{
}