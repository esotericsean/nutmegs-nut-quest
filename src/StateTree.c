#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "Palette.h"

#include "../src/GlobalVars.h"
#include "../src/Font.h"

IMPORT_MAP (treemap2);

UINT8 collision_tiles_tree2[] = {2,3,4,5,7,8,9,10,12,49,50,51,52,53,54,55,56,57,58, 0};

DECLARE_MUSIC(oaktree);

extern Sprite * spr_nutmeg;

UINT16 treecounter = 0;

void Start_StateTree() {
	SPRITES_8x16;

	treecounter = 0;

	PlayMusic(oaktree, 1);

	//SetPalette (BG_PALETTE, 0, 8, bg_palette_tree2, bank_StateTree);
	//SetPalette (SPRITES_PALETTE, 0, 8, sprites_palette_tree2, bank_StateTree);

	SpriteManagerLoad(35);  	//nutmeg
	SpriteManagerLoad(12); 	//puff1
	SpriteManagerLoad(13); 	//puff2
	SpriteManagerLoad(14); 	//cinnamon
	SpriteManagerLoad(15); 	//maple
	SpriteManagerLoad(28); 	//ruby

	spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 36+48, 96);
	
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