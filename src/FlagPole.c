#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Music.h"
#include "SpriteManager.h"

#include "GlobalVars.h"
#include "Palette.h"

DECLARE_MUSIC (victorydance);

// pink color palette
static const UWORD pal_pink[] = { RGB(31, 31, 31), RGB(19, 26, 30), RGB(28, 19, 30), RGB(0,  0,  0) };
// water-friendly variant: replace color 1 with exact 0D 0E 1C (light blue)
static const UWORD pal_pink_water[] = { RGB(31, 31, 31), RGB(13, 14, 28), RGB(28, 19, 30), RGB(0,  0,  0) };

// special palette to use on stage 5
static const UWORD pal_pink5[] = { RGB(31, 31, 31), RGB(7,  8,  9), RGB(28, 19, 30), RGB(7,  7,  7) };

static const UWORD pal_pink3[] = { RGB(31, 31, 31), RGB(19, 26, 30), RGB(28, 19, 30), RGB(0,  0,  0) };

// Sideways pole - just 1 tile meant to run the full screen or between 2 walls
static const UINT8 sideways_1[] = {
 	0xFF,0xFF,0x00,0x38,0x00,0x38,0x00,0x70,
  	0x00,0x70,0x00,0xE0,0x00,0xE0,0xFF,0xFF
};

static const UINT8 sideways_2[] = {
	0xFF,0xFF,0x00,0xE0,0x00,0xE0,0x00,0xC1,
	0x00,0xC1,0x00,0x83,0x00,0x83,0xFF,0xFF
};

static const UINT8 sideways_3[] = {
  	0xFF,0xFF,0x00,0x83,0x00,0x83,0x00,0x07,
  	0x00,0x07,0x00,0x0E,0x00,0x0E,0xFF,0xFF
};
static const UINT8 sideways_4[] = {
	0xFF,0xFF,0x00,0x0E,0x00,0x0E,0x00,0x1C,
  	0x00,0x1C,0x00,0x38,0x00,0x38,0xFF,0xFF
};

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
#define FLAGPOLE_TILE_2 (0x22)

static UINT8 flagpole_pal_idx = 0xFF; // unknown until detected

// Scan upward from the bottom of the pole for our flagpole tiles to discover the palette index
static UINT8 FlagPole_DetectPaletteIndex(UINT8 tilex, UINT8 tiley)
{
#ifdef CGB
    UINT8 id = 0, attr = 0, y = 0;
    for (y = 0; y <= tiley; ++y) {
        get_bkg_tiles(tilex, tiley - y, 1, 1, &id); // tile ids live in VRAM bank 0
        if (id == FLAGPOLE_TILE_1 || id == FLAGPOLE_TILE_2) {
            VBK_REG = 1; // attributes
            get_bkg_tiles(tilex, tiley - y, 1, 1, &attr);
            VBK_REG = 0;
            return (attr & 0x07); // palette index 0..7
        }
    }
#endif
    // Fallback defaults by level if detection fails
    if (level_current == 5) return 5;
    if (level_current == 3) return 1; // this level used slot 1 originally
    return 1;
}

// Fallback detector: scan the visible BG for first pole tile to get its palette index
static UINT8 FlagPole_DetectPaletteIndex_ScanScreen(void)
{
#ifdef CGB
    UINT8 id = 0, attr = 0;
    UINT8 x, y;
    for (y = 0; y < 18; ++y) {
        for (x = 0; x < 20; ++x) {
            get_bkg_tiles(x, y, 1, 1, &id);
            if (id == FLAGPOLE_TILE_1 || id == FLAGPOLE_TILE_2) {
                VBK_REG = 1;
                get_bkg_tiles(x, y, 1, 1, &attr);
                VBK_REG = 0;
                return (attr & 0x07);
            }
        }
    }
#endif
    return 1;
}

// Force the top cap tile's attribute to use a specific BG palette index
static void FlagPole_ForceTopPalette(UINT8 tilex, UINT8 tiley, UINT8 pal_idx)
{
#ifdef CGB
    UINT8 id = 0;
    UINT8 y;
    for (y = 0; y <= tiley; ++y) {
        get_bkg_tiles(tilex, tiley - y, 1, 1, &id);
        if (id == FLAGPOLE_TILE_1) {
            UINT8 attr = pal_idx & 0x07; // palette index in low 3 bits
            VBK_REG = 1;
            set_bkg_tiles(tilex, tiley - y, 1, 1, &attr);
            VBK_REG = 0;
            return;
        }
    }
#endif
}

static UINT8 anim_flag_counter;
static UINT8 flagpole_activated;

static UINT8 finish_counter;
static int stars_x;
static int stars_y;

void FlagPole_Init (void) BANKED
{
	anim_flag_counter = 0;
    flagpole_activated = 0; 
    finish_counter = 0;

    stars_x = 0;
    stars_y = 0;

    // Do not touch global BG palettes here; will override map palettes.
}

// x = tile x of bottom of flagpole
// y = tile y of bottom of flagpole
void FlagPole_Activate(int tilex, int tiley) BANKED
{
    flagpole_activated = 1;

    stars_x = tilex * 8;
    stars_y = tiley * 8;
	
	// start a bit up the pole.
	stars_y -= 26;

    // Detect palette index used by pole top cap then set palette accordingly
    flagpole_pal_idx = FlagPole_DetectPaletteIndex((UINT8)tilex, (UINT8)(tiley-1));
    if (flagpole_pal_idx == 0xFF) {
        flagpole_pal_idx = FlagPole_DetectPaletteIndex_ScanScreen();
    }
    // If still unknown and user reported BG2, use that as a final fallback
    if (flagpole_pal_idx == 0xFF) flagpole_pal_idx = 2;

    // Force the cap top to use the detected (or BG2) palette to avoid white corners
    FlagPole_ForceTopPalette((UINT8)tilex, (UINT8)(tiley-1), flagpole_pal_idx);

    //change flagpole color palette (use water variant if underwater level)
    if (level_current == 5) 
	{
		SetPalette(BG_PALETTE, 5, 1, pal_pink5, _current_bank);
	}
	else if (level_current == 3) 
	{
        SetPalette(BG_PALETTE, flagpole_pal_idx, 1, pal_pink3, _current_bank);
	}
    else
	{
        if (level.isWaterLevel) {
            SetPalette(BG_PALETTE, flagpole_pal_idx, 1, pal_pink_water, _current_bank);
            // Ensure BG2 (observed in BGB) is also water-friendly
            SetPalette(BG_PALETTE, 2, 1, pal_pink_water, _current_bank);
        }
        else SetPalette(BG_PALETTE, flagpole_pal_idx, 1, pal_pink, _current_bank);
	}
    __critical { PlayMusic(victorydance, 1); }
}

void FlagPole_Animate (void) BANKED
{
    // Enforce water-friendly palette each frame for BG2 in water levels
    if (level.isWaterLevel == true) {
        SetPalette(BG_PALETTE, 2, 1, pal_pink_water, _current_bank);
    }

	if (level.isHorizontalGoalpost == true)
	{
		if (anim_flag_counter == 12)
		{
			set_bkg_data (FLAGPOLE_TILE_1, 1, sideways_1);
		}
		else if (anim_flag_counter == 24)
		{
			set_bkg_data (FLAGPOLE_TILE_1, 1, sideways_2);
		}
		else if (anim_flag_counter == 36)
		{
			set_bkg_data (FLAGPOLE_TILE_1, 1, sideways_3);
		}
		else if (anim_flag_counter == 48)
		{
			set_bkg_data (FLAGPOLE_TILE_1, 1, sideways_4);
		}

		anim_flag_counter++;
		if (anim_flag_counter == 49) anim_flag_counter = 0;
	}
	else if (flagpole_activated == 0) {
        //animate grey flagpole
        if (anim_flag_counter == 12) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, grey_33);
			set_bkg_data (FLAGPOLE_TILE_2, 1, grey_41);
		}
        else if (anim_flag_counter == 24) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, grey_34);
			set_bkg_data (FLAGPOLE_TILE_2, 1, grey_42);
		}
        else if (anim_flag_counter == 36) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, grey_35);
			set_bkg_data (FLAGPOLE_TILE_2, 1, grey_43);
		}
        else if (anim_flag_counter == 48) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, grey_36);
			set_bkg_data (FLAGPOLE_TILE_2, 1, grey_44);
		}
		anim_flag_counter++;
		if (anim_flag_counter == 49) anim_flag_counter = 0;
	}
    else
    {
        //animate pink flagpole
        if (anim_flag_counter < 5) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, pink_37);
			set_bkg_data (FLAGPOLE_TILE_2, 1, pink_45);
            if (level.isWaterLevel == true) SetPalette(BG_PALETTE, flagpole_pal_idx, 1, pal_pink_water, _current_bank);
            if (level.isWaterLevel == true) SetPalette(BG_PALETTE, 2, 1, pal_pink_water, _current_bank);
        }
        else if (anim_flag_counter >= 5 && anim_flag_counter < 10) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, pink_38);
			set_bkg_data (FLAGPOLE_TILE_2, 1, pink_46);
            if (level.isWaterLevel == true) SetPalette(BG_PALETTE, flagpole_pal_idx, 1, pal_pink_water, _current_bank);
            if (level.isWaterLevel == true) SetPalette(BG_PALETTE, 2, 1, pal_pink_water, _current_bank);
		}
        else if (anim_flag_counter >= 10 && anim_flag_counter < 15) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, pink_39);
			set_bkg_data (FLAGPOLE_TILE_2, 1, pink_47);
            if (level.isWaterLevel == true) SetPalette(BG_PALETTE, flagpole_pal_idx, 1, pal_pink_water, _current_bank);
            if (level.isWaterLevel == true) SetPalette(BG_PALETTE, 2, 1, pal_pink_water, _current_bank);
		}
        else if (anim_flag_counter >= 15 && anim_flag_counter < 20) {
			set_bkg_data (FLAGPOLE_TILE_1, 1, pink_40);
			set_bkg_data (FLAGPOLE_TILE_2, 1, pink_48);
            if (level.isWaterLevel == true) SetPalette(BG_PALETTE, flagpole_pal_idx, 1, pal_pink_water, _current_bank);
            if (level.isWaterLevel == true) SetPalette(BG_PALETTE, 2, 1, pal_pink_water, _current_bank);
		}
		anim_flag_counter++;
		if (anim_flag_counter >= 20) anim_flag_counter = 0;

        finish_counter++;


		if (level_current == 11)
		{
			if (finish_counter == 10) {
				// these stars are all crampt into 3 tiles high
				stars_y += 26;
				AddStarPairWide (stars_x-4, stars_y);
			}
			else if (finish_counter == 30) {
				AddStarPairWide (stars_x-4, stars_y - 8);
			}
			else if (finish_counter == 50) {
				AddStarPairWide (stars_x-4, stars_y - 16);
			}
		}
		else
		{
			if (finish_counter == 10) {
				AddStarPairWide (stars_x-4, stars_y);
			}
			else if (finish_counter == 30) {
				AddStarPairWide (stars_x-4, stars_y - 16);
			}
			else if (finish_counter == 50) {
				AddStarPairWide (stars_x-4, stars_y - 32);
			}
		}
    }
}