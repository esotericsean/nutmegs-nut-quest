#include "Banks/SetAutoBank.h"
#include <gb/cgb.h>
#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Music.h"
#include "Keys.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

IMPORT_MAP (titlemap);

static UINT8 title_counter;
static UINT8 acorn_position;

// BG1 //
static const UWORD pal_titleyellow[] = { RGB(31, 31, 31), RGB(9, 23, 27), RGB(28, 27, 9), RGB(22, 21, 5) };
static const UWORD pal_titleyellowpale[] = { RGB(31, 31, 31), RGB(21, 29, 30), RGB(30, 30, 22), RGB(28, 27, 19) };
static const UWORD pal_titleyellowpalest[] = { RGB(31, 31, 31), RGB(27, 30, 30), RGB(30, 30, 28), RGB(30, 29, 27) };

// BG 2 //
static const UWORD pal_titlelogo[] = { RGB(9, 23, 27), RGB(23, 14, 11), RGB(17, 10, 7), RGB(13, 6, 5) };
static const UWORD pal_titlelogopale[] = { RGB(21, 29, 30), RGB(29, 23, 20), RGB(26, 21, 19), RGB(23, 19, 18) };
static const UWORD pal_titlelogopalest[] = { RGB(27, 30, 30), RGB(30, 27, 25), RGB(29, 26, 25), RGB(28, 25, 23) };

// BG 3 //
static const UWORD pal_titlefont[] = { RGB(31, 31, 31), RGB(9, 23, 27), RGB(7, 7, 7), 0 };
static const UWORD pal_titlefontpale[] = { RGB(31, 31, 31), RGB(21, 29, 30), RGB(21, 21, 21), RGB(15, 15, 15) };
static const UWORD pal_titlefontpalest[] = { RGB(31, 31, 31), RGB(27, 31, 31), RGB(27, 27, 27), RGB(24, 24, 24) };

// BG 4 //
static const UWORD pal_titleacorn[] = { RGB(31, 31, 31), RGB(25, 19, 11), RGB(13, 6, 5), 0 };
static const UWORD pal_titleacornpale[] = { RGB(31, 31, 31), RGB(29, 26, 21), RGB(23, 19, 18), RGB(15, 15, 15) };
static const UWORD pal_titleacornpalest[] = { RGB(31, 31, 31), RGB(30, 29, 27), RGB(29, 27, 26), RGB(24, 24, 24) };

//List of tiles that will be animated
static const unsigned char whitespace[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

static const unsigned char titleacorn[] = {
	0x00,0x00,0x00,0x00,0x0d,0x0d,0x0a,0x1e,
	0x1d,0x17,0x1f,0x23,0x3c,0x26,0x10,0x38
};

static const UINT8 collision_tiles_title[] = {1, 0};

DECLARE_MUSIC(chase);

static const UWORD leafPalette[] = { 0, RGB(8, 23, 8), RGB(5, 19, 12), 0 };

void Start_StateTitle (void) 
{
    PlayMusic(chase, 1);
    
    SPRITES_8x8;

    title_counter = 0;
    acorn_position = 1;

    SpriteManagerAdd (SpriteLeaf, 117, 0);

    SHOW_SPRITES;

    InitScrollTiles (0, &titletiles);
    InitScroll (BANK(titlemap), &titlemap, collision_tiles_title, 0);

    UINT8 i;
    for (i = 21; i < 32; ++i) {
		ScrollUpdateColumn (i, 0);
	}

    nutmeg_SetupGame();

    SHOW_BKG;
}

static UINT8 maintimer = 0;
extern UINT8 backgroundoffsetmain;

void Update_StateTitle (void) 
{

    maintimer++;
    if (maintimer == 4) {
        maintimer = 0;
        backgroundoffsetmain += 1;
    }

    if (title_counter < 1) {
        SetPalette(SPRITES_PALETTE, 0, 1, leafPalette, _current_bank);
    }

    if (title_counter > 170 && title_counter <= 180) {
        SetPalette(BG_PALETTE, 0, 1, pal_titleyellowpalest, _current_bank);
        SetPalette(BG_PALETTE, 1, 1, pal_titlelogopalest, _current_bank);
        SetPalette(BG_PALETTE, 2, 1, pal_titlefontpalest, _current_bank);
        SetPalette(BG_PALETTE, 3, 1, pal_titleacornpalest, _current_bank);
    }
    else if (title_counter > 180 && title_counter <= 190) {
        SetPalette(BG_PALETTE, 0, 1, pal_titleyellowpale, _current_bank);
        SetPalette(BG_PALETTE, 1, 1, pal_titlelogopale, _current_bank);
        SetPalette(BG_PALETTE, 2, 1, pal_titlefontpale, _current_bank);
        SetPalette(BG_PALETTE, 3, 1, pal_titleacornpale, _current_bank);
    }
    else if (title_counter > 190) {
        SetPalette(BG_PALETTE, 0, 1, pal_titleyellow, _current_bank);
        SetPalette(BG_PALETTE, 1, 1, pal_titlelogo, _current_bank);
        SetPalette(BG_PALETTE, 2, 1, pal_titlefont, _current_bank);
        SetPalette(BG_PALETTE, 3, 1, pal_titleacorn, _current_bank);
    }

    if (title_counter >= 191 && title_counter < 201) {
        SetPalette(BG_PALETTE, 3, 1, pal_titleacornpale, _current_bank);
    }
    else if (title_counter >= 201 && title_counter < 211) {
        SetPalette(BG_PALETTE, 3, 1, pal_titleacornpalest, _current_bank);
    }
    else if (title_counter >= 211 && title_counter < 225) {
        SetPalette(BG_PALETTE, 3, 1, pal_titleacornpale, _current_bank);
    }
    else if (title_counter >= 225 && title_counter < 245) {
        SetPalette(BG_PALETTE, 3, 1, pal_titleacorn, _current_bank);
    }

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
       
    if (acorn_position == 1 && KEY_PRESSED(J_START)) {
        SetState (StateTreeCutscene);
    }
    else if (acorn_position == 2 && KEY_PRESSED(J_START)) {
        SetState (StateCredits);
    }

    title_counter++;

    if (title_counter >= 245) title_counter = 191;
}