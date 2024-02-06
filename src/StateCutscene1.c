#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Palette.h"
#include "Sound.h"
#include "Keys.h"

#include "../src/GlobalVars.h"
#include "../src/Font.h"

IMPORT_MAP (cutscene1map);

UINT16 cutscene1counter;

//health system
UINT8 acorncounter;
INT8 nutmeglives;

const UINT8 collision_tiles_cutscene1[] = {0};

//extern UINT8* oaktree_mod_Data[];
DECLARE_MUSIC(oaktree);

const unsigned char font_upper_WW[] = {
0x00,0x00,0x44,0x44,0x44,0x44,0x44,0x44,
0x44,0x44,0x54,0x54,0x54,0x54,0x28,0x28
};
const unsigned char font_lower_ee[] = {
0x00,0x00,0x00,0x00,0x18,0x18,0x24,0x24,
0x24,0x24,0x38,0x38,0x20,0x20,0x1c,0x1c
};
const unsigned char font_apostrophee[] = {
0x00,0x00,0x10,0x10,0x10,0x10,0x20,0x20,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
const unsigned char font_lower_rr[] = {
0x00,0x00,0x00,0x00,0x18,0x18,0x24,0x24,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20
};
const unsigned char font_lower_hh[] = {
0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,
0x38,0x38,0x24,0x24,0x24,0x24,0x24,0x24
};
const unsigned char font_lower_uu[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x44,
0x44,0x44,0x44,0x44,0x44,0x44,0x38,0x38
};
const unsigned char font_lower_nn[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x2c,0x2c,
0x32,0x32,0x22,0x22,0x22,0x22,0x22,0x22
};
const unsigned char font_lower_gg[] = {
0x00,0x00,0x00,0x00,0x18,0x18,0x24,0x24,
0x24,0x24,0x1c,0x1c,0x04,0x04,0x38,0x38
};
const unsigned char font_lower_yy[] = {
0x00,0x00,0x00,0x00,0x22,0x22,0x22,0x22,
0x22,0x22,0x1a,0x1a,0x04,0x04,0x38,0x38
};
const unsigned char font_commaa[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x10,0x10,0x10,0x10,0x20,0x20
};
const unsigned char font_lower_mm[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x28,0x28,
0x54,0x54,0x54,0x54,0x44,0x44,0x44,0x44
};
const unsigned char font_lower_aa[] = {
0x00,0x00,0x00,0x00,0x18,0x18,0x24,0x24,
0x04,0x04,0x1c,0x1c,0x24,0x24,0x1a,0x1a
};
const unsigned char font_periodd[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20
};
const unsigned char font_arroww[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x7c,0x7c,0x38,0x38,0x10,0x10
};
const unsigned char font_blankk[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

void Start_StateCutscene1() {
    SPRITES_8x16;

    stop_music_on_new_state = 0;
	PlayMusic(oaktree, 1);

    SpriteManagerAdd(SpriteBlinkCinnamon, 24, 78);
    SpriteManagerAdd(SpriteBlinkCinnamon, 24+10, 78);

    SpriteManagerAdd(SpriteBlinkRuby, 68, 73);
    SpriteManagerAdd(SpriteBlinkRuby, 68+10, 73);

    SpriteManagerAdd(SpriteBlinkMaple, 104, 78);
    SpriteManagerAdd(SpriteBlinkMaple, 104+10, 78);

    SpriteManagerAdd(SpriteBow, 75, 66);

    InitScrollTiles(0, &cutscene1tiles);
    InitScroll(BANK(cutscene1map), &cutscene1map, collision_tiles_cutscene1, 0);

    SHOW_SPRITES;
	SHOW_BKG;

    cutscene1counter = 0;

    //health system
    acorncounter = 0;
    nutmeglives = 99; //3
    health = full;
    lostbow = false;
    firstplay = true;

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

    if (cutscene1counter == 0) {
        //set_sprite_palette(1, 1, bowPalette); //worked
    }

    //We're
    if (cutscene1counter == 35) set_bkg_data (0x02, 1, font_upper_WW);
    else if (cutscene1counter == 40) set_bkg_data (0x03, 1, font_lower_ee);
    else if (cutscene1counter == 45) set_bkg_data (0x04, 1, font_apostrophee);
    else if (cutscene1counter == 50) set_bkg_data (0x05, 1, font_lower_rr);
    else if (cutscene1counter == 55) set_bkg_data (0x06, 1, font_lower_ee);

    //hungry,
    else if (cutscene1counter == 60) set_bkg_data (0x08, 1, font_lower_hh);
    else if (cutscene1counter == 65) set_bkg_data (0x09, 1, font_lower_uu);
    else if (cutscene1counter == 70) set_bkg_data (0x0A, 1, font_lower_nn);
    else if (cutscene1counter == 75) set_bkg_data (0x0B, 1, font_lower_gg);
    else if (cutscene1counter == 80) set_bkg_data (0x0C, 1, font_lower_rr);
    else if (cutscene1counter == 85) set_bkg_data (0x0D, 1, font_lower_yy);
    else if (cutscene1counter == 90) set_bkg_data (0x0E, 1, font_commaa);

    //mama...
    else if (cutscene1counter == 95 ) set_bkg_data (0x10, 1, font_lower_mm);
    else if (cutscene1counter == 100) set_bkg_data (0x11, 1, font_lower_aa);
    else if (cutscene1counter == 105) set_bkg_data (0x12, 1, font_lower_mm);
    else if (cutscene1counter == 110) set_bkg_data (0x13, 1, font_lower_aa);
    else if (cutscene1counter == 115) set_bkg_data (0x14, 1, font_periodd);
    else if (cutscene1counter == 120) set_bkg_data (0x15, 1, font_periodd);
    else if (cutscene1counter == 125) set_bkg_data (0x16, 1, font_periodd);
    //▼
    else if (cutscene1counter == 135) set_bkg_data (0x6E, 1, font_arroww);
    else if (cutscene1counter == 155) set_bkg_data (0x6E, 1, font_blankk);

    cutscene1counter++;

    if (KEY_PRESSED(J_A) && cutscene1counter >= 135) {
        //CHANGE THIS TO CUTSCENE 2, then CUTSCENE 3, then Gordon Cutscene, then Overworld1
        //and set variable for first time visiting overworld
        SetState(StateCutscene2);
    }

    if (cutscene1counter >= 175)
    {
         cutscene1counter = 135;
    }
}