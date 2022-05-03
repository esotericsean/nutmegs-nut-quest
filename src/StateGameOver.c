#include "Banks/SetBank6.h"
#include "..\res\src\gameovertiles.h"
#include "..\res\src\gameovermap.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "../res/src/nutmeg1.h"
#include "../res/src/acorn.h"
#include "../res/src/puff.h"
#include "Palette.h"

#include "../src/GlobalVars.h"

const UINT16 bg_palette_gameover[] = {
	PALETTE_FROM_HEADER(gameovertiles)
};

const UINT16 sprites_palette_gameover[] = {
	PALETTE_INDEX (nutmeg1, 0),
	PALETTE_INDEX (acorn, 1),
	PALETTE_INDEX (puff, 3)
};

const UWORD pal_white[] = {
	RGB(31, 31, 31),
	RGB(31, 31, 31),
	RGB(31, 31, 31),
	RGB(31, 31, 31)
};

const UWORD pal_nutmegdark[] = {
	RGB(0, 0, 0),
	RGB(31, 27, 17),
	RGB(31, 11, 6),
	RGB(8, 8, 8)
};

const UINT8 collision_tiles_gameover[] = {10};

extern UINT8* gameover_mod_Data[];

extern struct Sprite * spr_nutmeg1;
extern struct Sprite * spr_nutmeg2;
extern struct Sprite * spr_camera;

void Start_StateGameOver() {
	SPRITES_8x16;

	PlayMusic(gameover_mod_Data, 6, 1);

	SetPalette (BG_PALETTE, 0, 8, bg_palette_gameover, bank_StateGameOver);
	SetPalette (SPRITES_PALETTE, 0, 8, sprites_palette_gameover, bank_StateGameOver);

	SpriteManagerLoad(2);  //acorn
	SpriteManagerLoad(5);  //camera
	SpriteManagerLoad(6);  //nutmeg1
	SpriteManagerLoad(7);  //nutmeg2
	SpriteManagerLoad(12); //puff
	SpriteManagerLoad(13); //puff

	scroll_target = spr_camera = SpriteManagerAdd(SpriteCamera, 4, 49);
	spr_nutmeg1 = SpriteManagerAdd(SpriteNutmeg1, 4, 49);
	spr_nutmeg2 = SpriteManagerAdd(SpriteNutmeg2, 20, 49);
	
	SpriteManagerAdd(SpriteAcorn, 136, 72);

	InitScrollTiles(0, &gameovertiles);
	InitScroll(&gameovermap, collision_tiles_gameover, 0);

	cutscenemode = disabled;
	isAcornMoving = true; //yes, it is moving

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateGameOver() {
	//set_sprite_palette (0, 1, pal_nutmegdark);
	set_sprite_palette_entry (0, 3, RGB(8, 8, 8)); //nutmeg light outline
	set_sprite_palette_entry (1, 3, RGB(8, 8, 8)); //acorn light outline

	if (KEY_PRESSED(J_START)) {
		SetState(StateIncube8);
	}
}