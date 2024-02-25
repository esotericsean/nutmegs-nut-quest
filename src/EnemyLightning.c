#include "Banks/SetAutoBank.h"
#include <gb/cgb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_lightning_fall1[] = {1, 1};
static const UINT8 anim_lightning_fall2[] = {1, 2};

static const UINT8 anim_lightning_strike1[] = {1, 3};
static const UINT8 anim_lightning_strike2[] = {1, 4};
static const UINT8 anim_lightning_strike3[] = {1, 5};

static const UINT8 anim_lightning_empty[] = {1, 0};

static const UWORD pal_sky_original[] = { RGB(11,11,11), RGB(7, 8, 9), RGB(20,20,20), RGB(7, 7, 7) };
static const UWORD pal_sky_flash1[] =   { RGB(11,11,11), RGB(31,31,31), RGB(20,20,20), RGB(7, 7, 7) };
static const UWORD pal_sky_flash2[] =   { RGB(11,11,11), RGB(23,25,26), RGB(20,20,20), RGB(7, 7, 7) };

static const UWORD pal_wood_original[] = { RGB(7, 8, 9),  RGB(21, 17, 14), RGB(17, 13, 12), RGB(7, 7, 7) };
static const UWORD pal_wood_flash1[] = { RGB(31, 31, 31), RGB(21, 17, 14), RGB(17, 13, 12), RGB(7, 7, 7) };
static const UWORD pal_wood_flash2[] = { RGB(23, 25, 26), RGB(21, 17, 14), RGB(17, 13, 12), RGB(7, 7, 7) };

static const UWORD pal_flag_original[] = { RGB(31, 31, 31), RGB(7,  8,  9),  RGB(14, 14, 14), RGB(7, 7, 7) };
static const UWORD pal_flag_flash1[] = {   RGB(31, 31, 31), RGB(31, 31, 31), RGB(14, 14, 14), RGB(7, 7, 7) };
static const UWORD pal_flag_flash2[] = {   RGB(31, 31, 31), RGB(23, 25, 26), RGB(14, 14, 14), RGB(7, 7, 7) };

static UINT8 lightningcounter;


void Start_EnemyLightning (void) 
{
	if (levelorientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_lightning_fall1, 1);

	lightningcounter = 0;
}

void Update_EnemyLightning (void) 
{
	if (lightningcounter < 10) {
		SetSpriteAnim(THIS, anim_lightning_fall1, 1);
		TranslateSprite(THIS, 0, 6);
	}
	else if (lightningcounter >= 10 && lightningcounter < 15) {
		SetSpriteAnim(THIS, anim_lightning_fall2, 1);
		TranslateSprite(THIS, 0, 6);
	}
	else if (lightningcounter >= 15 && lightningcounter < 20) {
		SetPalette(BG_PALETTE, 1, 1, pal_sky_flash1, _current_bank);
		SetPalette(BG_PALETTE, 6, 1, pal_wood_flash1, _current_bank);
		if (levelbeat == false)
		{
			SetPalette(BG_PALETTE, 5, 1, pal_flag_flash1, _current_bank);
		}
		PlayFx(CHANNEL_4, 60, 0x3a, 0xf2, 0x62, 0x80);
		SetSpriteAnim(THIS, anim_lightning_strike1, 1);
	}
	else if (lightningcounter >= 20 && lightningcounter < 25) {
		SetPalette(BG_PALETTE, 1, 1, pal_sky_flash2, _current_bank);
		SetPalette(BG_PALETTE, 6, 1, pal_wood_flash2, _current_bank);
		if (levelbeat == false)
		{
			SetPalette(BG_PALETTE, 5, 1, pal_flag_flash2, _current_bank);
		}
		SetSpriteAnim(THIS, anim_lightning_strike2, 1);
	}
	else if (lightningcounter >= 25 && lightningcounter < 30) {
		SetPalette(BG_PALETTE, 1, 1, pal_sky_original, _current_bank);
		SetPalette(BG_PALETTE, 6, 1, pal_wood_original, _current_bank);
		if (levelbeat == false)
		{
			SetPalette(BG_PALETTE, 5, 1, pal_flag_original, _current_bank);
		}
		SetSpriteAnim(THIS, anim_lightning_strike3, 1);
	}

	lightningcounter++;

	if (lightningcounter >= 30) {
		lightningcounter = 31;
		SetSpriteAnim(THIS, anim_lightning_empty, 1);
		SpriteManagerRemoveSprite (THIS);
	}

	//die if get struck by lightning
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg_death == false) {
		nutmeg_hit();
	}
}

void Destroy_EnemyLightning (void) 
{
}