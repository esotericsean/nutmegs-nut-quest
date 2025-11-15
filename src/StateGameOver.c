#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>

#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "SpriteNutmeg.h"

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

void Start_StateGameOver(void) 
{
	SPRITES_8x16;

	stop_music_on_new_state = 1;
	isPaused = false;

	nutmeg.isDying = false;
	nutmeg.pendingDeath = false;
	nutmeg.deathState = 0;
	nutmeg.deathFrames = 0;
	nutmeg.deathtimer = 0;
	nutmeg.speedX = 0;
	nutmeg.speedY = 0;
	nutmeg.offsetX = 0;
	nutmeg.offsetY = 0;
	nutmeg_allow_next_quickdeath();

	PlayMusic(gameover, 1);

	spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 16, 49);
	
	SpriteManagerAdd(SpriteAcorn, 136, 72);

	GameOver = true;

	InitScrollTiles(0, &gameovertiles);
	InitScroll(BANK(gameovermap), &gameovermap, collision_tiles_gameover, 0);

	cutscenemode = disabled;

	SHOW_SPRITES;
	SHOW_BKG;
	HIDE_WIN;
}

void Update_StateGameOver(void) 
{

	SetPalette(SPRITES_PALETTE, 0, 1, pal_nutmegdark, _current_bank);

	if (KEY_TICKED(J_START)) {
		SetState(StateInitGame);
	}
}