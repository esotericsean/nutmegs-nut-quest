#include "Banks/SetBank6.h"

#include "..\res\src\titletiles.h"
#include "..\res\src\titlemap.h"
#include "..\res\src\leaf.h"

#include "ZGBMain.h"
#include "Keys.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Palette.h"
#include "Sound.h"

#include "../src/GlobalVars.h"

//UINT8 backgroundoffset;

UINT8 title_counter;
UINT8 acorn_position;
//UINT8 backgroundoffset1x;
//UINT8 backgroundoffset2x;

// BG1 //
const UWORD pal_titleyellow[] = {
    RGB(31, 31, 31), RGB(9, 23, 27), RGB(28, 27, 9), RGB(22, 21, 5)
};
const UWORD pal_titleyellowpale[] = {
    RGB(31, 31, 31), RGB(21, 29, 30), RGB(30, 30, 22), RGB(28, 27, 19)
};
const UWORD pal_titleyellowpalest[] = {
    RGB(31, 31, 31), RGB(27, 30, 30), RGB(30, 30, 28), RGB(30, 29, 27)
};

// BG 2 //
const UWORD pal_titlelogo[] = {
	RGB(9, 23, 27), RGB(23, 14, 11), RGB(17, 10, 7), RGB(13, 6, 5)
};
const UWORD pal_titlelogopale[] = {
	RGB(21, 29, 30), RGB(29, 23, 20), RGB(26, 21, 19), RGB(23, 19, 18)
};
const UWORD pal_titlelogopalest[] = {
	RGB(27, 30, 30), RGB(30, 27, 25), RGB(29, 26, 25), RGB(28, 25, 23)
};

// BG 3 //
const UWORD pal_titlefont[] = {
    RGB(31, 31, 31), RGB(9, 23, 27), RGB(7, 7, 7), 0
};
const UWORD pal_titlefontpale[] = {
    RGB(31, 31, 31), RGB(21, 29, 30), RGB(21, 21, 21), RGB(15, 15, 15)
};
const UWORD pal_titlefontpalest[] = {
    RGB(31, 31, 31), RGB(27, 31, 31), RGB(27, 27, 27), RGB(24, 24, 24)
};

// BG 4 //
const UWORD pal_titleacorn[] = {
	RGB(31, 31, 31), RGB(25, 19, 11), RGB(13, 6, 5), 0
};
const UWORD pal_titleacornpale[] = {
	RGB(31, 31, 31), RGB(29, 26, 21), RGB(23, 19, 18), RGB(15, 15, 15)
};
const UWORD pal_titleacornpalest[] = {
	RGB(31, 31, 31), RGB(30, 29, 27), RGB(29, 27, 26), RGB(24, 24, 24)
};

//List of tiles that will be animated
const unsigned char whitespace[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
const unsigned char titleacorn[] = {
	0x00,0x00,0x00,0x00,0x0d,0x0d,0x0a,0x1e,
	0x1d,0x17,0x1f,0x23,0x3c,0x26,0x10,0x38
};

const UINT16 bg_palette_title[] = {PALETTE_FROM_HEADER(titletiles)};

const UINT16 sprites_palette_title[] = {
    PALETTE_INDEX (leaf, 0)
};

UINT8 collision_tiles_title[] = {1, 0};

extern UINT8* chase_mod_Data[];

UWORD leafPalette[] = {
	0, RGB(8, 23, 8), RGB(5, 19, 12), 0
};

void performantdelay (UINT8 numloops) {
    UINT8 ii;
    for (ii = 0; ii < numloops; ii++) {
        wait_vbl_done();
    }     
}

/*
void interruptLCD () {
    switch (LYC_REG)
    {
    case 0x00:
        //scroll bkg doesn't work, have to give it exact location
        move_bkg(backgroundoffset1x, 0);
        LYC_REG = 0x35;
        break;
    case 0x35:
        move_bkg(backgroundoffset2x, 0);
        LYC_REG = 0x00;
        break;
    }
}
*/

void Start_StateTitle() {
    SPRITES_8x8;

    title_counter = 0;
    acorn_position = 1;

    //backgroundoffset1x = 0;
    //backgroundoffset2x = 0;

    PlayMusic(chase_mod_Data, 3, 1);

    SetPalette (BG_PALETTE, 0, 4, bg_palette_title, bank_StateTitle);
	SetPalette (SPRITES_PALETTE, 0, 2, sprites_palette_title, bank_StateTitle);

    SpriteManagerLoad(1); //leaf
    SpriteManagerAdd (SpriteLeaf, 117, 0);

    SHOW_SPRITES;

    InitScrollTiles (0, &titletiles);
	InitScroll (&titlemap, collision_tiles_title, 0);

    //STAT_REG = 0x45;
    //LYC_REG = 0x00;

    //disable_interrupts();
    //add_LCD (interruptLCD);
    //enable_interrupts();

    //set_interrupts (VBL_IFLAG | LCD_IFLAG);

    SHOW_BKG;

    //RESET SO NUTMEG DOESN'T FLY OFF SCREEN
    accelY = 0;
    accelX = 0;
    jumpPeak = 0;
    runJump = 0;
    nutmeg_direction = right;
    movestate = grounded;
    isjumping = false;

    W1LevelSelection = 0;
    overworld1visited = false;
}

void Update_StateTitle() {
    if (title_counter >= 0 && title_counter < 1) set_sprite_palette(1, 1, leafPalette);

    if (title_counter > 170 && title_counter <= 180) {
        set_bkg_palette (0, 1, pal_titleyellowpalest);
        set_bkg_palette (1, 1, pal_titlelogopalest);
        set_bkg_palette (2, 1, pal_titlefontpalest);
        set_bkg_palette (3, 1, pal_titleacornpalest);
    }
    else if (title_counter > 180 && title_counter <= 190) {
        set_bkg_palette (0, 1, pal_titleyellowpale);
        set_bkg_palette (1, 1, pal_titlelogopale);
        set_bkg_palette (2, 1, pal_titlefontpale);
        set_bkg_palette (3, 1, pal_titleacornpale);
    }
    else if (title_counter > 190) {
        set_bkg_palette (0, 1, pal_titleyellow);
        set_bkg_palette (1, 1, pal_titlelogo);
        set_bkg_palette (2, 1, pal_titlefont);
        set_bkg_palette (3, 1, pal_titleacorn);
    }

    if (title_counter >= 191 && title_counter < 201) set_bkg_palette (3, 1, pal_titleacornpale);
    else if (title_counter >= 201 && title_counter < 211) set_bkg_palette (3, 1, pal_titleacornpalest);
    else if (title_counter >= 211 && title_counter < 225) set_bkg_palette (3, 1, pal_titleacornpale);
    else if (title_counter >= 225 && title_counter < 245) set_bkg_palette (3, 1, pal_titleacorn);

   if (acorn_position == 1 && KEY_PRESSED(J_DOWN)) acorn_position = 2;
   else if (acorn_position == 2 && KEY_PRESSED(J_UP)) acorn_position = 1;

    if (acorn_position == 1) {
        //set position to START
        set_bkg_data (0x4E, 1, titleacorn);
        set_bkg_data (0x7E, 1, whitespace);
    }
    else if (acorn_position == 2) {
        //set position to CREDITS
        set_bkg_data (0x4E, 1, whitespace);
        set_bkg_data (0x7E, 1, titleacorn);
    }

    if (acorn_position == 1 && KEY_PRESSED(J_START)) SetState (StateTreeCutscene);
    else if (acorn_position == 2 && KEY_PRESSED(J_START)) SetState (StateTreeCutscene);

    /*
    backgroundoffset += 1;
    if (backgroundoffset >= 320) backgroundoffset = 0;
    */

    //backgroundoffset1x = 0; //amount to scroll the top (none)
    //backgroundoffset2x = 2; //amount to scroll the clouds

    title_counter++;

    if (title_counter >= 245) title_counter = 191;

    //scroll_bkg (backgroundoffset, 0);

    //performantdelay(1);
    //wait_vbl_done();
}