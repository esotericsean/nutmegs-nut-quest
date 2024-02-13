#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>

#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "Palette.h"

#include "../src/GlobalVars.h"

IMPORT_MAP (gameovermap);

static const UWORD pal_white[] = {
	RGB(31, 31, 31),
	RGB(31, 31, 31),
	RGB(31, 31, 31),
	RGB(31, 31, 31)
};

static const UWORD pal_nutmegdark[] = {
	RGB(0, 0, 0),
	RGB(31, 27, 23),
	RGB(31, 17, 6),
	RGB(8, 8, 8)
};

static const UINT8 collision_tiles_gameover[] = {10,0};

DECLARE_MUSIC(gameover);

extern Sprite * spr_nutmeg;
extern Sprite * spr_camera;

void Start_StateGameOver() {
	SPRITES_8x16;

	PlayMusic(gameover, 1);

	spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 16, 49);
	
	SpriteManagerAdd(SpriteAcorn, 136, 72);

	InitScrollTiles(0, &gameovertiles);
	InitScroll(BANK(gameovermap), &gameovermap, collision_tiles_gameover, 0);

	cutscenemode = disabled;
	isAcornMoving = true; //yes, it is moving

	SHOW_SPRITES;
	SHOW_BKG;
	HIDE_WIN;
}

void Update_StateGameOver() {

	SetPalette(SPRITES_PALETTE, 0, 1, pal_nutmegdark, _current_bank);

	if (KEY_PRESSED(J_START)) {
		SetState(StateIncube8);
	}
}