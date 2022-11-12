#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "../src/GlobalVars.h"

const UINT8 anim_lightning_fall1[] = {1, 1};
const UINT8 anim_lightning_fall2[] = {1, 2};

const UINT8 anim_lightning_strike1[] = {1, 3};
const UINT8 anim_lightning_strike2[] = {1, 4};
const UINT8 anim_lightning_strike3[] = {1, 5};

const UINT8 anim_lightning_empty[] = {1, 0};

UINT8 lightningcounter;

const UWORD pal_sky_original[] = { RGB(24,24,24), RGB(16,20,22), RGB(20,20,20), RGB(7, 7, 7) };
const UWORD pal_sky_flash1[] =   { RGB(24,24,24), RGB(31,31,31), RGB(20,20,20), RGB(7, 7, 7) };
const UWORD pal_sky_flash2[] =   { RGB(24,24,24), RGB(23,25,26), RGB(20,20,20), RGB(7, 7, 7) };

void Start_EnemyLightning() {
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

void Update_EnemyLightning() {
	if (lightningcounter >= 0 && lightningcounter < 10) {
		SetSpriteAnim(THIS, anim_lightning_fall1, 1);
		TranslateSprite(THIS, 0, 6);
	}
	else if (lightningcounter >= 10 && lightningcounter < 15) {
		SetSpriteAnim(THIS, anim_lightning_fall2, 1);
		TranslateSprite(THIS, 0, 6);
	}
	else if (lightningcounter >= 15 && lightningcounter < 20) {
		SetPalette(BG_PALETTE, 1, 1, pal_sky_flash1, _current_bank);
		SetSpriteAnim(THIS, anim_lightning_strike1, 1);
	}
	else if (lightningcounter >= 20 && lightningcounter < 25) {
		SetPalette(BG_PALETTE, 1, 1, pal_sky_flash2, _current_bank);
		SetSpriteAnim(THIS, anim_lightning_strike2, 1);
	}
	else if (lightningcounter >= 25 && lightningcounter < 30) {
		SetPalette(BG_PALETTE, 1, 1, pal_sky_original, _current_bank);
		SetSpriteAnim(THIS, anim_lightning_strike3, 1);
	}

	lightningcounter++;

	if (lightningcounter >= 30) {
		lightningcounter = 31;
		SetSpriteAnim(THIS, anim_lightning_empty, 1);
		SpriteManagerRemoveSprite (THIS);
	}
}

void Destroy_EnemyLightning() {
}