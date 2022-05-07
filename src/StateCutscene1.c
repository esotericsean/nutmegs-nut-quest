#include "Banks/SetBank5.h"

#include "..\res\src\cutscene1tiles.h"
#include "..\res\src\cutscene1map.h"

#include "..\res\src\blink.h"
#include "..\res\src\bow.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Palette.h"
#include "Sound.h"
#include "Keys.h"

#include "../src/GlobalVars.h"
#include "../src/Font.h"

UINT16 cutscene1counter;

//health system
UINT8 acorncounter;
INT8 nutmeglives;

const UINT8 collision_tiles_cutscene1[] = {0};

const UWORD pal_cut1[] = {
	RGB(28, 23, 18),
	RGB(16, 10, 7),
	RGB(11, 6,  6),
	RGB(0,  0,  0)
};
const UWORD pal_cut2[] = {
	RGB(28, 23, 18),
    RGB(27, 13, 6),
	RGB(16, 10, 7),
	RGB(0,  0,  0)
};

const UWORD bowPalette[] = {
	0,
    RGB(28, 15, 15),
    RGB(22, 5, 5),
    RGB(0, 0, 0)
};

const UINT16 bg_palette_cutscene1[] = {
    PALETTE_FROM_HEADER (cutscene1tiles)
};

const UINT16 sprites_palette_cutscene1[] = {
    PALETTE_INDEX (blink, 0),
    PALETTE_INDEX (bow, 1)
};

extern UINT8* oaktree_mod_Data[];

//need to specify a param when loading bg
//SetPalette only has 2 options: BG_PAL and SPRITES_PAL
//PALETTE_FROM_HEADER I don't think is it
//void InitScrollTiles(UINT8 first_tile, UINT8 n_tiles, UINT8* tile_data, UINT8 tile_bank);

void Start_StateCutscene1() {
    SPRITES_8x16;

    PlayMusic(oaktree_mod_Data, 4, 1);

    SetPalette (BG_PALETTE, 0, 2, bg_palette_cutscene1, bank_StateCutscene1);
	SetPalette (SPRITES_PALETTE, 0, 1, sprites_palette_cutscene1, bank_StateCutscene1);

    SpriteManagerLoad(22); //Cinnamon
    SpriteManagerLoad(23); //Maple
    SpriteManagerLoad(26); //Ruby
    SpriteManagerLoad(27); //Ruby's Bow

    SpriteManagerAdd(SpriteBlinkCinnamon, 24, 78);
    SpriteManagerAdd(SpriteBlinkCinnamon, 24+10, 78);

    SpriteManagerAdd(SpriteBlinkRuby, 68, 73);
    SpriteManagerAdd(SpriteBlinkRuby, 68+10, 73);

    SpriteManagerAdd(SpriteBlinkMaple, 104, 78);
    SpriteManagerAdd(SpriteBlinkMaple, 104+10, 78);

    SpriteManagerAdd(SpriteBow, 75, 66);

    InitScrollTiles(0, &cutscene1tiles);
    InitScroll(&cutscene1map, collision_tiles_cutscene1, 0);

    SHOW_SPRITES;
	SHOW_BKG;

    cutscene1counter = 0;

    //health system
    acorncounter = 0;
    nutmeglives = 3;

    //RESET SO NUTMEG DOESN'T FLY OFF SCREEN
    accelY = 0;
    accelX = 0;
    jumpPeak = 0;
    runJump = 0;
    nutmeg_direction = right;
    movestate = grounded;
    isjumping = false;
}

void Update_StateCutscene1() {
    if (KEY_PRESSED(J_START)) SetState(StateCutscene2);

    set_bkg_palette (0, 1, pal_cut1); //first pal, num of pals, pal name
    set_bkg_palette (1, 1, pal_cut2);

    if (cutscene1counter == 0) {
        set_sprite_palette(1, 1, bowPalette); //worked
    }

    //We're
    if (cutscene1counter >= 35 && cutscene1counter < 40) set_bkg_data (0x02, 1, font_upper_W);
    else if (cutscene1counter >= 40 && cutscene1counter < 45) set_bkg_data (0x03, 1, font_lower_e);
    else if (cutscene1counter >= 45 && cutscene1counter < 50) set_bkg_data (0x04, 1, font_apostrophe);
    else if (cutscene1counter >= 50 && cutscene1counter < 55) set_bkg_data (0x05, 1, font_lower_r);
    else if (cutscene1counter >= 55 && cutscene1counter < 60) set_bkg_data (0x06, 1, font_lower_e);

    //hungry,
    else if (cutscene1counter >= 60 && cutscene1counter < 65) set_bkg_data (0x08, 1, font_lower_h);
    else if (cutscene1counter >= 65 && cutscene1counter < 70) set_bkg_data (0x09, 1, font_lower_u);
    else if (cutscene1counter >= 70 && cutscene1counter < 75) set_bkg_data (0x0A, 1, font_lower_n);
    else if (cutscene1counter >= 75 && cutscene1counter < 80) set_bkg_data (0x0B, 1, font_lower_g);
    else if (cutscene1counter >= 80 && cutscene1counter < 85) set_bkg_data (0x0C, 1, font_lower_r);
    else if (cutscene1counter >= 85 && cutscene1counter < 90) set_bkg_data (0x0D, 1, font_lower_y);
    else if (cutscene1counter >= 90 && cutscene1counter < 95) set_bkg_data (0x0E, 1, font_comma);

    //mama...
    else if (cutscene1counter >= 95 && cutscene1counter < 100) set_bkg_data (0x10, 1, font_lower_m);
    else if (cutscene1counter >= 100 && cutscene1counter < 105) set_bkg_data (0x11, 1, font_lower_a);
    else if (cutscene1counter >= 105 && cutscene1counter < 110) set_bkg_data (0x12, 1, font_lower_m);
    else if (cutscene1counter >= 110 && cutscene1counter < 115) set_bkg_data (0x13, 1, font_lower_a);
    else if (cutscene1counter >= 115 && cutscene1counter < 120) set_bkg_data (0x14, 1, font_period);
    else if (cutscene1counter >= 120 && cutscene1counter < 125) set_bkg_data (0x15, 1, font_period);
    else if (cutscene1counter >= 125 && cutscene1counter < 130) set_bkg_data (0x16, 1, font_period);

    //▼
    else if (cutscene1counter >= 135 && cutscene1counter < 155) set_bkg_data (0x6E, 1, font_arrow);
    else if (cutscene1counter >= 155 && cutscene1counter < 175) set_bkg_data (0x6E, 1, font_blank);

    cutscene1counter++;

    if (KEY_PRESSED(J_A) && cutscene1counter >= 135 && cutscene1counter < 175) {
        //CHANGE THIS TO CUTSCENE 2, then CUTSCENE 3, then Gordon Cutscene, then Overworld1
        //and set variable for first time visiting overworld
        SetState(StateCutscene2);
    }

    if (cutscene1counter >= 175) cutscene1counter = 135;
}