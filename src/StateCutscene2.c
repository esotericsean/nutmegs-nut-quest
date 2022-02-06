#include "Banks/SetBank5.h"

#include "..\res\src\cutscene2tiles.h"
#include "..\res\src\cutscene2map.h"

#include "..\res\src\incube8G.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Palette.h"
#include "Sound.h"
#include "Keys.h"

#include "../src/GlobalVars.h"
#include "../src/Font.h"

UINT16 cutscene2counter;

const UINT8 collision_tiles_cutscene2[] = {0};

const UWORD pal_cut3[] = {
	RGB(28, 23, 18),
	RGB(16, 10, 7),
	RGB(11, 6,  6),
	RGB(0,  0,  0)
};
const UWORD pal_cut4[] = {
	RGB(28, 23, 18),
    RGB(27, 13, 6),
	RGB(16, 10, 7),
	RGB(0,  0,  0)
};

const UINT16 bg_palette_cutscene2[] = {
    PALETTE_FROM_HEADER (cutscene2tiles)
};

const UINT16 sprites_palette_cutscene2[] = {
    PALETTE_INDEX (incube8G, 0)
};

extern UINT8* oaktree_mod_Data[];

//need to specify a param when loading bg
//SetPalette only has 2 options: BG_PAL and SPRITES_PAL
//PALETTE_FROM_HEADER I don't think is it
//void InitScrollTiles(UINT8 first_tile, UINT8 n_tiles, UINT8* tile_data, UINT8 tile_bank);

void Start_StateCutscene2() {
    SPRITES_8x16;

    PlayMusic(oaktree_mod_Data, 4, 1);

    SetPalette (BG_PALETTE, 0, 2, bg_palette_cutscene2, bank_StateCutscene2);
	SetPalette (SPRITES_PALETTE, 0, 1, sprites_palette_cutscene2, bank_StateCutscene2);

    //SpriteManagerLoad(22); //Cinnamon
    //SpriteManagerLoad(23); //Maple

    //SpriteManagerAdd(SpriteBlinkCinnamon, 32, 72);
    //SpriteManagerAdd(SpriteBlinkCinnamon, 32+15, 72);

    //SpriteManagerAdd(SpriteBlinkMaple, 80, 72);
    //SpriteManagerAdd(SpriteBlinkMaple, 80+15, 72);

    InitScrollTiles(0, &cutscene2tiles);
    InitScroll(&cutscene2map, collision_tiles_cutscene2, 0);

    SHOW_SPRITES;
	SHOW_BKG;
    cutscene2counter = 0;
}

void Update_StateCutscene2() {
    set_bkg_palette (0, 1, pal_cut3); //first pal, num of pals, pal name
    set_bkg_palette (1, 1, pal_cut4);

    //cutscene2counter++;

    if (KEY_PRESSED(J_A) || KEY_PRESSED(J_START)) {
        SetState(StateCutscene3);
    }
}