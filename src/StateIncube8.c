#include "Banks/SetAutoBank.h"
#include "SGB.h"
//#include <gb/cgb.h>
#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "Sound.h"
#include "Keys.h"

IMPORT_MAP (gb_border);
IMPORT_MAP (incube8map);

UINT8 incube8counter;

const UINT8 collision_tiles_incube8[] = {0};

const UWORD pal_games[] =       { 0, RGB(30, 16, 16), RGB(28,  3,  4), 0 };
const UWORD pal_gamespale[] =   { 0, RGB(30, 24, 24), RGB(29, 17, 19), 0 };
const UWORD pal_gamespalest[] = { 0, RGB(30, 28, 28), RGB(30, 25, 26), 0 };

DECLARE_MUSIC (incube8);

void Start_StateIncube8() {
    SPRITES_8x8;

    PlayMusic(incube8, 1);

    SpriteManagerAdd(SpriteIncube8G, 97, 84+8);
    SpriteManagerAdd(SpriteIncube8A, 97+11, 84+8);
    SpriteManagerAdd(SpriteIncube8M, 97+22, 84+8);
    SpriteManagerAdd(SpriteIncube8E, 97+33, 84+8);
    SpriteManagerAdd(SpriteIncube8S, 97+43, 84+8);

    LOAD_SGB_BORDER(gb_border);

    InitScrollTiles(0, &incube8tiles);
    InitScroll(BANK(incube8map), &incube8map, collision_tiles_incube8, 0);

    SHOW_SPRITES;
	SHOW_BKG;
    incube8counter = 0;
}

void Update_StateIncube8() {
    if (incube8counter >= 5 && incube8counter < 10) {
        SetPalette(SPRITES_PALETTE, 0, 1, pal_gamespalest, _current_bank);
    }
    else if (incube8counter >= 10 && incube8counter < 20) {
        SetPalette(SPRITES_PALETTE, 0, 1, pal_gamespale, _current_bank);
    }
    else if (incube8counter >= 20) {
        SetPalette(SPRITES_PALETTE, 0, 1, pal_games, _current_bank);
    }

    incube8counter++;

    if (incube8counter >= 150 || KEY_PRESSED(J_A) || KEY_PRESSED(J_START)) SetState(StateLogo);
}