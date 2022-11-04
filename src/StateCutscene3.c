#include "Banks/SetAutoBank.h"

#include "..\res\src\cutscene3tiles.h"
#include "..\res\src\cutscene3map.h"

#include "..\res\src\incube8G.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Palette.h"
#include "Sound.h"
#include "Keys.h"

#include "../src/GlobalVars.h"
#include "../src/Font.h"

IMPORT_MAP (cutscene3map);

UINT16 cutscene3counter;

UINT8 collision_tiles_cutscene3[] = {0};

/*
const UWORD pal_cut5[] = {
	RGB(28, 23, 18),
	RGB(27, 13, 6),
	RGB(31, 31,  31),
	RGB(0,  0,  0)
};
const UWORD pal_cut6[] = {
	RGB(28, 23, 18),
    RGB(27, 13, 6),
	RGB(16, 10, 7),
	RGB(0,  0,  0)
};
const UWORD pal_cut7[] = {
	RGB(2, 23, 29),
    RGB(16, 10, 7),
	RGB(27, 13, 6),
	RGB(0,  0,  0)
};
const UWORD pal_cut8[] = {
	RGB(31, 31, 31),
    RGB(28, 23, 18),
	RGB(27, 13, 6),
	RGB(0,  0,  0)
};
const UWORD pal_cut9[] = {
	RGB(31, 31, 31),
    RGB(22, 29, 20),
	RGB(17, 26, 17),
	RGB(0,  0,  0)
};
const UWORD pal_cut10[] = {
	RGB(15, 27, 13),
    RGB(9, 24, 10),
	RGB(16, 10, 7),
	RGB(0,  0,  0)
};
const UWORD pal_cut11[] = {
	RGB(31, 31, 31),
    RGB(15, 27, 13),
	RGB(16, 10, 7),
	RGB(0,  0,  0)
};
const UWORD pal_cut12[] = {
	RGB(15, 27, 13),
    RGB(9, 24, 10),
	RGB(27, 13, 6),
	RGB(0,  0,  0)
};
*/

const UINT16 bg_palette_cutscene3[] = {
    PALETTE_FROM_HEADER (cutscene3tiles)
};

const UINT16 sprites_palette_cutscene3[] = {
    PALETTE_INDEX (incube8G, 0)
};

//extern UINT8* oaktree_mod_Data[];

//need to specify a param when loading bg
//SetPalette only has 2 options: BG_PAL and SPRITES_PAL
//PALETTE_FROM_HEADER I don't think is it
//void InitScrollTiles(UINT8 first_tile, UINT8 n_tiles, UINT8* tile_data, UINT8 tile_bank);

void Start_StateCutscene3() {
    SPRITES_8x16;

    //PlayMusic (oaktree, 1);

    //SetPalette (BG_PALETTE, 0, 8, bg_palette_cutscene3, bank_StateCutscene3);
	//SetPalette (SPRITES_PALETTE, 0, 1, sprites_palette_cutscene3, bank_StateCutscene3);

    //SpriteManagerLoad(22); //Cinnamon
    //SpriteManagerLoad(23); //Maple

    //SpriteManagerAdd(SpriteBlinkCinnamon, 32, 72);
    //SpriteManagerAdd(SpriteBlinkCinnamon, 32+15, 72);

    //SpriteManagerAdd(SpriteBlinkMaple, 80, 72);
    //SpriteManagerAdd(SpriteBlinkMaple, 80+15, 72);

    InitScrollTiles(0, &cutscene3tiles);
    //InitScroll(&cutscene3map, collision_tiles_cutscene3, 0);
    InitScroll(BANK(cutscene3map), &cutscene3map, collision_tiles_cutscene3, 0);

    SHOW_SPRITES;
	SHOW_BKG;
    cutscene3counter = 0;
}

void Update_StateCutscene3() {
    //set_bkg_palette (0, 1, pal_cut5); //first pal, num of pals, pal name
    //set_bkg_palette (1, 1, pal_cut6);
    //set_bkg_palette (2, 1, pal_cut7);
    //set_bkg_palette (3, 1, pal_cut8);
    //set_bkg_palette (4, 1, pal_cut9);
    //set_bkg_palette (5, 1, pal_cut10);
    //set_bkg_palette (6, 1, pal_cut11);
    //set_bkg_palette (7, 1, pal_cut12);

    //cutscene3counter++;

    if (KEY_PRESSED(J_A) || KEY_PRESSED(J_START)) {
        SetState(StateCutsceneGordon);
    }
}