#include "Banks/SetAutoBank.h"

#include "..\res\src\esologotiles.h"
#include "..\res\src\esologomap.h"
#include "..\res\src\esofire.h"

#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Palette.h"
#include "Sound.h"
#include "Keys.h"

IMPORT_MAP (esologomap);

UINT8 counter;

//const UINT16 bg_palette_logo[] = {PALETTE_FROM_HEADER(esologotiles)};

/*
const UINT16 sprites_palette_logo[] = {
	PALETTE_INDEX (esofire, 0)
};
*/

UINT8 collision_tiles_logo[] = {1, 0};

//extern UINT8* esogames_mod_Data[];
DECLARE_MUSIC(esogames);

void Start_StateLogo() {
    UINT8 i = 0;
	SPRITES_8x8;

    PlayMusic(esogames, 1);

    //SetPalette (BG_PALETTE, 0, 1, bg_palette_logo, bank_StateLogo);
	//SetPalette (SPRITES_PALETTE, 0, 1, sprites_palette_logo, bank_StateLogo);

    SpriteManagerLoad(0); //esofire

    SpriteManagerAdd(SpriteFire, 88, 55);

    SHOW_SPRITES;

    InitScrollTiles(0, &esologotiles);
	InitScroll(BANK(esologomap), &esologomap, collision_tiles_logo, 0);

	SHOW_BKG;
    counter = 0;
}

void Update_StateLogo() {
    counter++;

    if (counter >= 250 || KEY_PRESSED(J_A) || KEY_PRESSED(J_START)) SetState(StateTitle);
}