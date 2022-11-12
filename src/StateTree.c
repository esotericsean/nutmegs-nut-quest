#include "Banks/SetAutoBank.h"

#include "..\res\src\treetiles.h"
#include "..\res\src\treemap2.h"

#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "../res/src/nutmeg.h"
#include "../res/src/nutmeg2.h"
#include "../res/src/cinnamon.h"
#include "../res/src/ruby.h"
#include "../res/src/maple.h"
#include "../res/src/puff.h"
#include "Palette.h"

#include "../src/GlobalVars.h"
#include "../src/Font.h"

IMPORT_MAP (treemap2);

const UINT16 bg_palette_tree2[] = {
	PALETTE_FROM_HEADER(treetiles)
};

const UINT16 sprites_palette_tree2[] = {
	PALETTE_INDEX (nutmeg, 0),
	PALETTE_INDEX (puff, 4)
};

/*
UWORD puffPalette[] = {
	RGB(31, 31, 31), RGB(31, 31, 31), RGB(31, 31, 31), RGB(31, 31, 31)
};
*/

/*
const unsigned char tree_blank[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00
};
*/

UINT8 collision_tiles_tree2[] = {2,3,4,5,7,8,9,10,12,49,50,51,52,53,54,55,56,57,58, 0};

//extern UINT8* oaktree_mod_Data[];
DECLARE_MUSIC(oaktree);

extern Sprite * spr_nutmeg;
//extern Sprite * spr_nutmeg2;

//struct Sprite * spr_cinnamon;
//struct Sprite * spr_maple;
//struct Sprite * spr_ruby;

//extern struct Sprite * spr_camera;

UINT16 treecounter = 0;

void Start_StateTree() {
	SPRITES_8x16;

	treecounter = 0;

	PlayMusic(oaktree, 1);

	//SetPalette (BG_PALETTE, 0, 8, bg_palette_tree2, bank_StateTree);
	//SetPalette (SPRITES_PALETTE, 0, 8, sprites_palette_tree2, bank_StateTree);

	SpriteManagerLoad(35);  	//nutmeg
	//SpriteManagerLoad(7);  	//nutmeg2
	SpriteManagerLoad(12); 	//puff1
	SpriteManagerLoad(13); 	//puff2
	SpriteManagerLoad(14); 	//cinnamon
	SpriteManagerLoad(15); 	//maple
	SpriteManagerLoad(28); 	//ruby

	spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 36+48, 96);
	//spr_nutmeg2 = SpriteManagerAdd(SpriteNutmeg2, 52+48, 96);

	//spr_cinnamon = SpriteManagerAdd(SpriteCinnamon, 36, 96);
	//spr_ruby = SpriteManagerAdd(SpriteRuby, 36+11, 96);
	//spr_maple = SpriteManagerAdd(SpriteMaple, 36+20, 96);

	SpriteManagerAdd(SpriteCinnamon, 36, 96);
	SpriteManagerAdd(SpriteRuby, 36+11, 96);
	SpriteManagerAdd(SpriteMaple, 36+20, 96);

	InitScrollTiles(0, &treetiles);
	InitScroll(BANK(treemap2), &treemap2, collision_tiles_tree2, 0);

	SHOW_SPRITES;
	SHOW_BKG;

	cutscenemode = enabled;
}

void Update_StateTree() {
	//if Nutmeg touches the Oak Tree Door, then leave
	if (spr_nutmeg->x >= 110 && spr_nutmeg->x < 118) SetState(StateOverworld1);

	if (treecounter == 0) {
		cutscenewalkleft = true;
		cutscenewalkright = false;
		//set_sprite_palette(3, 1, puffPalette);
	}
	else if (treecounter >= 2) {
		cutscenemode = disabled;
		cutscenewalkleft = false;
		cutscenewalkright = false;
	}

	if (treecounter < 3) treecounter++;
}