#include "Banks/SetBank1.h"
#include "BankManager.h"

#include "..\res\src\overworld1.h"
#include "..\res\src\overworld1map.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "..\res\src\nutmeg1.h"
#include "..\res\src\acorn.h"
#include "..\res\src\nutmegtiny.h"
#include "Palette.h"

#include "../src/GlobalVars.h"

/////////////////////////////////////////////////////
//												   //
//					 ~ World 1 ~				   //
//				  The Acorn Kingdom				   //
//												   //
/////////////////////////////////////////////////////

UINT8 f = 0;

//copied from SpriteNutmegTiny
	UINT8 e = 0;
	UINT8 bossflash = 0;
	UINT8 W1LevelSelection = 1; 	// nutmeg starts at level 1
									// level 0 is the tree
									// mushroom is level 4
	UINT8 direction = 0;
	UINT8 distance  = 0;
//end copied from SpriteNutmegTiny

//copied from SpriteNutmegTiny
	const unsigned char overworld1_tree[] = {
		0x36,0x00,0x5b,0x00,0xff,0x00,0xbb,0x00,
		0x6e,0x00,0x0c,0x1c,0x04,0x1c,0x26,0x3e
	};
	const unsigned char overworld1_mushroom[] = {
		0xff,0x00,0xff,0x3e,0xc1,0x6f,0xc1,0x7b,
		0xe1,0x7f,0xc3,0x22,0xeb,0x2a,0xef,0x3e
	};
	const unsigned char overworld1_boss1[] = {
		0x00,0x00,0x1c,0x1c,0x3e,0x22,0x73,0x4d,
		0x61,0x5f,0x61,0x5f,0x32,0x2e,0x1c,0x1c
	};
	const unsigned char overworld1_boss2[] = {
		0x00,0x00,0x1c,0x1c,0x22,0x3e,0x4d,0x73,
		0x5f,0x61,0x5f,0x61,0x2e,0x32,0x1c,0x1c
	};
	const unsigned char overworld1_num1[] = {
		0x00,0x00,0x18,0x18,0x08,0x08,0x08,0x08,
		0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00
	};
	const unsigned char overworld1_num2[] = {
		0x00,0x00,0x18,0x18,0x24,0x24,0x04,0x04,
		0x18,0x18,0x20,0x20,0x3c,0x3c,0x00,0x00
	};
	const unsigned char overworld1_num3[] = {
		0x00,0x00,0x18,0x18,0x24,0x24,0x08,0x08,
		0x04,0x04,0x24,0x24,0x18,0x18,0x00,0x00
	};
	const unsigned char overworld1_num4[] = {
		0x00,0x00,0x08,0x08,0x18,0x18,0x28,0x28,
		0x3c,0x3c,0x08,0x08,0x08,0x08,0x00,0x00
	};
	const unsigned char overworld1_num5[] = {
		0x00,0x00,0x3c,0x3c,0x20,0x20,0x38,0x38,
		0x04,0x04,0x24,0x24,0x18,0x18,0x00,0x00
	};
	const unsigned char overworld1_num6[] = {
		0x00,0x00,0x18,0x18,0x20,0x20,0x38,0x38,
		0x24,0x24,0x24,0x24,0x18,0x18,0x00,0x00
	};
	const unsigned char overworld1_num7[] = {
		0x00,0x00,0x3c,0x3c,0x04,0x04,0x08,0x08,
		0x08,0x08,0x10,0x10,0x10,0x10,0x00,0x00
	};
	const unsigned char overworld1_num8[] = {
		0x00,0x00,0x18,0x18,0x24,0x24,0x18,0x18,
		0x24,0x24,0x24,0x24,0x18,0x18,0x00,0x00
	};
	const unsigned char overworld1_num9[] = {
		0x00,0x00,0x18,0x18,0x24,0x24,0x24,0x24,
		0x1c,0x1c,0x04,0x04,0x18,0x18,0x00,0x00
	};

	const unsigned char current_level[] = {
	0x3F
};
//end copied from SpriteNutmegTiny

bool overworld1visited;

const UINT16 bg_palette_overworld1[] = {PALETTE_FROM_HEADER(overworld1)};

const UINT16 sprites_palette_overworld1[] = {
	PALETTE_INDEX (nutmeg1, 0),
	PALETTE_INDEX (acorn, 1)
};

UINT8 collision_tiles_overworld1[] = {0};

extern UINT8* acornkingdom_mod_Data[];

extern struct Sprite * spr_nutmegtiny;

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
//extern struct Sprite * spr_nutmeg1;
//extern struct Sprite * spr_nutmeg2;
//extern struct Sprite * spr_camera;

//List of tiles that will be animated
const unsigned char overworld1_water1[] = {
	0xff,0x00,0xff,0x00,0x9f,0x00,0x6f,0x00,
	0xff,0x00,0xf9,0x00,0xf6,0x00,0xff,0x00
};
const unsigned char overworld1_water2[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0x9f,0x00,
	0x69,0x00,0xf6,0x00,0xff,0x00,0xff,0x00
};

//This is a map of a single water tile located in data location 3E
//Use a separate map for things that you want to animate separately
const unsigned char water_anim[] = {
	0x3E
};

//copied from SpriteNutmegTiny
//Need to update THIS to spr_nutmegtiny
	void Move (UINT8 dir, UINT8 dis) {
		if (dis > 0) {
			if (e >= 0 && e <= dis) {
				if (dir == 0) TranslateSprite (spr_nutmegtiny, -1, 0);
				if (dir == 1) TranslateSprite (spr_nutmegtiny, 1, 0);
				if (dir == 2) TranslateSprite (spr_nutmegtiny, 0, -1);
				if (dir == 3) TranslateSprite (spr_nutmegtiny, 0, 1);
			}

			e++;

			if (e > dis) {
				e = 0;
				distance = 0;
			}
		}
	}
//end copied from SpriteNutmegTiny

//MoveSpriteNutmegTiny

void Start_StateOverworld1() {
	//UINT8 i;
	SPRITES_8x16;

	isAcornMoving = false;
	overworld1visited = false;

	f = 0;

	PlayMusic(acornkingdom_mod_Data, 4, 1);

	SetPalette (BG_PALETTE, 0, 8, bg_palette_overworld1, bank_StateOverworld1);
	SetPalette (SPRITES_PALETTE, 0, 8, sprites_palette_overworld1, bank_StateOverworld1);

	SpriteManagerLoad(2); //acorn
	SpriteManagerLoad(8); //nutmegtiny
	SpriteManagerLoad(9); //nuthead

	spr_nutmegtiny = SpriteManagerAdd(SpriteNutmegTiny, 47, 45);
	//SpriteManagerAdd(SpriteNutmegTiny, 47, 45);
	SpriteManagerAdd(SpriteNutHead, 16, 7);
	//SpriteManagerAdd(SpriteAcorn, 129, 5);

	InitScrollTiles(0, &overworld1);
	InitScroll(&overworld1map, collision_tiles_overworld1, 0);

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateOverworld1() {
	//use this to modify background tiles in static scenes
	//set_bkg_tiles (6, 8, 1, 1, overworld1_water1); //x, y, w, h, *tiles

	//water anim
	if (f >= 0 && f < 20) set_bkg_data (0x3E, 1, overworld1_water1);
	if (f >= 20 && f < 40) set_bkg_data (0x3E, 1, overworld1_water2);
	set_bkg_tiles ( 0,  2, 1, 1, water_anim);
	set_bkg_tiles (19,  1, 1, 1, water_anim);
	set_bkg_tiles ( 0,  8, 1, 1, water_anim);
	set_bkg_tiles (19,  4, 1, 1, water_anim);
	set_bkg_tiles (19,  9, 1, 1, water_anim);
	set_bkg_tiles ( 1, 16, 1, 1, water_anim);
	//set_bkg_tiles (19, 12, 1, 1, water_anim);
	set_bkg_tiles (11, 17, 1, 1, water_anim);
	set_bkg_tiles (17, 17, 1, 1, water_anim);

	f++;

	if (f >= 40) {
		f = 0;
	}

	//copied from SpriteNutmegTiny
	if (e == 0) {
		// LEVEL 0 - THE TREEHOUSE
		if (W1LevelSelection == 0) {
			if 		(KEY_PRESSED(J_RIGHT)) { direction = 1; distance = 23; W1LevelSelection = 1; }
		}

		// LEVEL 1
		else if (W1LevelSelection == 1) {
			if 		(KEY_PRESSED(J_LEFT))  { direction = 0; distance = 23; W1LevelSelection = 0; }
			else if (KEY_PRESSED(J_DOWN))  { direction = 3; distance = 15; W1LevelSelection = 2; }
		}

		// LEVEL 2
		else if (W1LevelSelection == 2) {
			if 		(KEY_PRESSED(J_UP))    { direction = 2; distance = 15; W1LevelSelection = 1; }
			else if (KEY_PRESSED(J_DOWN))  { direction = 3; distance = 23; W1LevelSelection = 3; }
			else if (KEY_PRESSED(J_RIGHT)) { direction = 1; distance = 23; W1LevelSelection = 5; }
		}

		// LEVEL 3
		else if (W1LevelSelection == 3) {
			if 		(KEY_PRESSED(J_UP))    { direction = 2; distance = 23; W1LevelSelection = 2; }
			else if (KEY_PRESSED(J_LEFT))  { direction = 0; distance = 23; W1LevelSelection = 4; }
		}

		// LEVEL 4 - MUSHROOM HOUSE
		else if (W1LevelSelection == 4) {
			if 		(KEY_PRESSED(J_RIGHT)) { direction = 1; distance = 23; W1LevelSelection = 3; }
		}

		// LEVEL 5
		else if (W1LevelSelection == 5) {
			if 		(KEY_PRESSED(J_LEFT))   { direction = 0; distance = 23; W1LevelSelection = 2; }
			else if (KEY_PRESSED(J_DOWN))   { direction = 3; distance = 15; W1LevelSelection = 6; }
		}

		// LEVEL 6
		else if (W1LevelSelection == 6) {
			if 		(KEY_PRESSED(J_UP))  	{ direction = 2; distance = 15; W1LevelSelection = 5; }
			else if (KEY_PRESSED(J_RIGHT))  { direction = 1; distance = 23; W1LevelSelection = 7; }
		}

		// LEVEL 7
		else if (W1LevelSelection == 7) {
			if 		(KEY_PRESSED(J_LEFT))  	{ direction = 0; distance = 23; W1LevelSelection = 6; }
			else if (KEY_PRESSED(J_UP))  	{ direction = 2; distance = 31; W1LevelSelection = 8; }
		}

		// LEVEL 8
		else if (W1LevelSelection == 8) {
			if 		(KEY_PRESSED(J_RIGHT))  { direction = 1; distance = 23; W1LevelSelection = 9; }
			else if (KEY_PRESSED(J_DOWN))  	{ direction = 3; distance = 31; W1LevelSelection = 7; }
		}

		// LEVEL 9
		else if (W1LevelSelection == 9) {
			if 		(KEY_PRESSED(J_LEFT))   { direction = 0; distance = 23; W1LevelSelection = 8;  }
			else if (KEY_PRESSED(J_DOWN))   { direction = 3; distance = 23; W1LevelSelection = 10; }
		}

		// LEVEL 10
		else if (W1LevelSelection == 10) {
			if 		(KEY_PRESSED(J_UP))     { direction = 2; distance = 23; W1LevelSelection = 9;  }
			else if (KEY_PRESSED(J_DOWN))   { direction = 3; distance = 23; W1LevelSelection = 11; }
		}

		// LEVEL 11 - PICNIC TABLE (MINI BOSS)
		else if (W1LevelSelection == 11) {
			if 		(KEY_PRESSED(J_UP)) 	{ direction = 2; distance = 23; W1LevelSelection = 10; }
			else if (KEY_PRESSED(J_RIGHT)) 	{ direction = 1; distance = 46; W1LevelSelection = 11; /*change world*/ }
		}
	}

	if (distance > 0) Move (direction, distance);

	//level display
	if (W1LevelSelection == 0) set_bkg_data (0x3F, 1, overworld1_tree);
	else if (W1LevelSelection == 1) set_bkg_data (0x3F, 1, overworld1_num1);
	else if (W1LevelSelection == 2) set_bkg_data (0x3F, 1, overworld1_num2);
	else if (W1LevelSelection == 3) set_bkg_data (0x3F, 1, overworld1_num3);
	else if (W1LevelSelection == 4) set_bkg_data (0x3F, 1, overworld1_mushroom);
	else if (W1LevelSelection == 5) set_bkg_data (0x3F, 1, overworld1_num4);
	else if (W1LevelSelection == 6) set_bkg_data (0x3F, 1, overworld1_num5);
	else if (W1LevelSelection == 7) set_bkg_data (0x3F, 1, overworld1_num6);
	else if (W1LevelSelection == 8) set_bkg_data (0x3F, 1, overworld1_num7);
	else if (W1LevelSelection == 9) set_bkg_data (0x3F, 1, overworld1_num8);
	else if (W1LevelSelection == 10) set_bkg_data (0x3F, 1, overworld1_num9);
	else if (W1LevelSelection == 11) {
		if 		(bossflash >= 0 && bossflash < 5)  set_bkg_data (0x3F, 1, overworld1_boss1);
		else if (bossflash >= 5 && bossflash < 10) set_bkg_data (0x3F, 1, overworld1_boss2);

		bossflash++;

		if (bossflash > 10) bossflash = 0;
	}
	set_bkg_tiles (7, 1, 1, 1, current_level);

	//level selection
	if (KEY_PRESSED(J_A) || KEY_PRESSED(J_START)) {
		if (W1LevelSelection == 0) SetState(StateTree);
        else if (W1LevelSelection == 1) SetState(StateLevel1);
    }
}