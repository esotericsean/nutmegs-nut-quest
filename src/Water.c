#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Music.h"
#include "SpriteManager.h"

#include "GlobalVars.h"
#include "Palette.h"

//water tiles are stored in 1A, 1B, and 1C
//in GBTD, water is 26, 27, 28
const unsigned char level_water1[] = {
	0x00,0x08,0x08,0x3c,0x3c,0xff,0xff,0xfb,
	0xff,0xdf,0xf7,0xff,0x7f,0xff,0xfd,0xff
};
const unsigned char level_water2[] = {
	0x00,0x20,0x20,0xf3,0xf3,0xff,0xff,0xff,
	0xdf,0xff,0xff,0xf7,0x7f,0xff,0xfd,0xff
};
const unsigned char level_water3[] = {
	0x00,0x82,0x82,0xcf,0xcf,0xff,0xff,0xfb,
	0xdf,0xff,0xff,0xf7,0x7f,0xff,0xfd,0xff
};

#define WATER_TILE_1 (0x1A)
#define WATER_TILE_2 (0x1B)
#define WATER_TILE_3 (0x1C)

UINT8 anim_water_counter = 0;

void Water_Animate (void) BANKED {
	//animate water
	if (anim_water_counter >= 0 && anim_water_counter < 10) {
		set_bkg_data (WATER_TILE_1, 1, level_water1);
		set_bkg_data (WATER_TILE_2, 1, level_water2);
		set_bkg_data (WATER_TILE_3, 1, level_water3);
	}
	else if (anim_water_counter >= 10 && anim_water_counter < 20) {
		set_bkg_data (WATER_TILE_1, 1, level_water2);
		set_bkg_data (WATER_TILE_2, 1, level_water3);
		set_bkg_data (WATER_TILE_3, 1, level_water1);
	}
	else if (anim_water_counter >= 20 && anim_water_counter < 30) {
		set_bkg_data (WATER_TILE_1, 1, level_water3);
		set_bkg_data (WATER_TILE_2, 1, level_water1);
		set_bkg_data (WATER_TILE_3, 1, level_water2);
	}
	anim_water_counter++;
	if (anim_water_counter >= 30) anim_water_counter = 0;
}