#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Music.h"
#include "SpriteManager.h"

#include "GlobalVars.h"
#include "Palette.h"

#define WATER_TILE_1 (0x1A)
#define WATER_TILE_2 (0x1B)
#define WATER_TILE_3 (0x1C)

void FlagPole_Animate (void) BANKED
{
	if (flagpole_activated == 0) {
        //animate grey flagpole
		if (anim_flag_counter < 12) {
			set_bkg_data (WATER_TILE_1, 1, grey_33);
			set_bkg_data (WATER_TILE_2, 1, grey_41);
			set_bkg_data (WATER_TILE_3, 1, grey_41);
		}
		else if (anim_flag_counter >= 12 && anim_flag_counter < 24) {
			set_bkg_data (WATER_TILE_1, 1, grey_34);
			set_bkg_data (WATER_TILE_2, 1, grey_42);
			set_bkg_data (WATER_TILE_3, 1, grey_42);
		}
		else if (anim_flag_counter >= 24 && anim_flag_counter < 36) {
			set_bkg_data (WATER_TILE_1, 1, grey_35);
			set_bkg_data (WATER_TILE_2, 1, grey_43);
			set_bkg_data (WATER_TILE_3, 1, grey_43);
		}
		else if (anim_flag_counter >= 36 && anim_flag_counter < 48) {
			set_bkg_data (WATER_TILE_1, 1, grey_36);
			set_bkg_data (WATER_TILE_2, 1, grey_44);
			set_bkg_data (WATER_TILE_3, 1, grey_44);
		}
		anim_flag_counter++;
		if (anim_flag_counter >= 48) anim_flag_counter = 0;
	}
    else
    {
        //animate pink flagpole
        if (anim_flag_counter < 5) {
			set_bkg_data (WATER_TILE_1, 1, pink_37);
			set_bkg_data (WATER_TILE_2, 1, pink_45);
			set_bkg_data (WATER_TILE_3, 1, pink_45);
		}
		else if (anim_flag_counter >= 5 && anim_flag_counter < 10) {
			set_bkg_data (WATER_TILE_1, 1, pink_38);
			set_bkg_data (WATER_TILE_2, 1, pink_46);
			set_bkg_data (WATER_TILE_3, 1, pink_46);
		}
		else if (anim_flag_counter >= 10 && anim_flag_counter < 15) {
			set_bkg_data (WATER_TILE_1, 1, pink_39);
			set_bkg_data (WATER_TILE_2, 1, pink_47);
			set_bkg_data (WATER_TILE_3, 1, pink_47);
		}
		else if (anim_flag_counter >= 15 && anim_flag_counter < 20) {
			set_bkg_data (WATER_TILE_1, 1, pink_40);
			set_bkg_data (WATER_TILE_2, 1, pink_48);
			set_bkg_data (WATER_TILE_3, 1, pink_48);
		}
		anim_flag_counter++;
		if (anim_flag_counter >= 20) anim_flag_counter = 0;

        finish_counter++;

        if (finish_counter == 10) {
			SpriteManagerAdd(SpriteStarLeft, stars_x, stars_y);
			SpriteManagerAdd(SpriteStarRight, stars_x+8, 96);
		}
		else if (finish_counter == 30) {
			SpriteManagerAdd(SpriteStarLeft, stars_x, stars_y-16);
			SpriteManagerAdd(SpriteStarRight, stars_x+8, stars_y-16);
		}
		else if (finish_counter == 50) {
			SpriteManagerAdd(SpriteStarLeft, stars_x, stars_y-32);
			SpriteManagerAdd(SpriteStarRight, stars_x+8, stars_y-32);
		}
    }
}