#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Music.h"
#include "SpriteManager.h"

#include "GlobalVars.h"
#include "Palette.h"

DECLARE_MUSIC (flagpole);

// pink color palette
static const UWORD pal_pink[] = { RGB(31, 31, 31), RGB(19, 26, 30), RGB(28, 19, 30), RGB(0,  0,  0) };

// special palette to use on stage 5
static const UWORD pal_rainy_pink[] = { RGB(31, 31, 31), RGB(7,  8,  9), RGB(28, 19, 30), RGB(7,  7,  7) };

//grey top
static const unsigned char grey_33[] = {
	0xff,0x3c,0xc3,0x46,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};
static const unsigned char grey_34[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};
static const unsigned char grey_35[] = {
	0xff,0x3c,0xc3,0x7a,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};
static const unsigned char grey_36[] = {
	0xff,0x3c,0xc3,0x42,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink top
static const unsigned char pink_37[] = {
	0xff,0x3c,0xc3,0x42,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};

static const unsigned char pink_38[] = {
	0xff,0x3c,0xc3,0x5e,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};

static const unsigned char pink_39[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};

static const unsigned char pink_40[] = {
	0xff,0x3c,0xc3,0x62,0x81,0x81,0x81,0x81,
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff
};

//grey mid/bottom
static const unsigned char grey_41[] = {
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};

static const unsigned char grey_42[] = {
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};

static const unsigned char grey_43[] = {
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};

static const unsigned char grey_44[] = {
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink mid/bottom
static const unsigned char pink_45[] = {
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};

static const unsigned char pink_46[] = {
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};

static const unsigned char pink_47[] = {
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};

static const unsigned char pink_48[] = {
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81,
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff
};

#define FLAGPOLE_TILE_1 (0x21)
#define FLAGPOLE_TILE_2 (0x29)
#define FLAGPOLE_TILE_3 (0x2A)

static UINT8 anim_flag_counter = 0;
static UINT8 flagpole_activated = 0;

static UINT8 finish_counter = 0;
static int stars_x = 0;
static int stars_y = 0;

void FlagPole_Init (void) BANKED
{
    flagpole_activated = 0; 
    finish_counter = 0;

    stars_x = 0;
    stars_y = 0;
}

// x = first left star x, 
// y = first left star y
void FlagPole_Activate(int x, int y) BANKED
{
    flagpole_activated = 1;

    stars_x = x;
    stars_y = y;

    //change flagpole color palette to pink
	if (W1LevelSelection == 5)
	{
		SetPalette(BG_PALETTE, 1, 1, pal_rainy_pink, _current_bank);
	}
	else
	{
		SetPalette(BG_PALETTE, 1, 1, pal_pink, _current_bank);
		
	}
    __critical { PlayMusic(flagpole, 1); }
}

void FlagPole_Animate (void) BANKED
{
	if (flagpole_activated == 0) {
        //animate grey flagpole
		if (anim_flag_counter < 12) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, grey_33);
			set_bkg_data (FLAGPOLE_TILE_2, 1, grey_41);
			set_bkg_data (FLAGPOLE_TILE_3, 1, grey_41);
		}
		else if (anim_flag_counter >= 12 && anim_flag_counter < 24) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, grey_34);
			set_bkg_data (FLAGPOLE_TILE_2, 1, grey_42);
			set_bkg_data (FLAGPOLE_TILE_3, 1, grey_42);
		}
		else if (anim_flag_counter >= 24 && anim_flag_counter < 36) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, grey_35);
			set_bkg_data (FLAGPOLE_TILE_2, 1, grey_43);
			set_bkg_data (FLAGPOLE_TILE_3, 1, grey_43);
		}
		else if (anim_flag_counter >= 36 && anim_flag_counter < 48) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, grey_36);
			set_bkg_data (FLAGPOLE_TILE_2, 1, grey_44);
			set_bkg_data (FLAGPOLE_TILE_3, 1, grey_44);
		}
		anim_flag_counter++;
		if (anim_flag_counter >= 48) anim_flag_counter = 0;
	}
    else
    {
        //animate pink flagpole
        if (anim_flag_counter < 5) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, pink_37);
			set_bkg_data (FLAGPOLE_TILE_2, 1, pink_45);
			set_bkg_data (FLAGPOLE_TILE_3, 1, pink_45);
		}
		else if (anim_flag_counter >= 5 && anim_flag_counter < 10) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, pink_38);
			set_bkg_data (FLAGPOLE_TILE_2, 1, pink_46);
			set_bkg_data (FLAGPOLE_TILE_3, 1, pink_46);
		}
		else if (anim_flag_counter >= 10 && anim_flag_counter < 15) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, pink_39);
			set_bkg_data (FLAGPOLE_TILE_2, 1, pink_47);
			set_bkg_data (FLAGPOLE_TILE_3, 1, pink_47);
		}
		else if (anim_flag_counter >= 15 && anim_flag_counter < 20) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, pink_40);
			set_bkg_data (FLAGPOLE_TILE_2, 1, pink_48);
			set_bkg_data (FLAGPOLE_TILE_3, 1, pink_48);
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