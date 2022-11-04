#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>

#include "..\res\src\level1tiles.h"
#include "..\res\src\level2map.h"

#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "../res/src/nutmeg1.h"
#include "../res/src/acorn.h"
#include "../res/src/butterfly.h"
#include "../res/src/bunny.h"
#include "../res/src/star.h"
#include "../res/src/puff.h"
#include "../res/src/mushroom.h"
//#include "../res/src/fish.h"
//#include "../res/src/powerleaf.h"
//#include "../res/src/nutmegbow.h"
#include "Palette.h"

#include "../src/GlobalVars.h"

IMPORT_MAP (level2map);

UINT16 level2counter = 0;

UINT8 anim_water_counter2 = 0;
UINT8 anim_flag_counter2 = 0;
UINT8 flagpole_activated2 = 0;
UINT8 flagpole_stars2 = 0;
UINT8 endlevel_counter2 = 0;
//UINT8 starshooter = 0;

//pink color palette
const UWORD pal_pink2[] = {
	RGB(31, 31, 31),
	RGB(19, 26, 30),
	RGB(28, 19, 30),
	RGB(0,  0,  0)
};

const UINT16 bg_palette_level2[] = {
	PALETTE_FROM_HEADER(level1tiles)
};

const UINT16 sprites_palette_level2[] = {
	PALETTE_INDEX (nutmeg1, 0),
	PALETTE_INDEX (acorn, 1),
	PALETTE_INDEX (butterfly, 2),
	PALETTE_INDEX (bunny, 3),
	PALETTE_INDEX (mushroom, 4),
	PALETTE_INDEX (star, 2),
	PALETTE_INDEX (puff, 3),
};

const UINT8 collision_tiles_level2[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,29,30,31,32,95,96,97,98, 0};

//extern UINT8* quickstart_mod_Data[];
//extern UINT8* mushrooms_mod_Data[];
//extern UINT8* flagpole_mod_Data[];
//extern UINT8* quickdeath_mod_Data[];
DECLARE_MUSIC(quickstart);
DECLARE_MUSIC(mushrooms);
DECLARE_MUSIC(flagpole);
DECLARE_MUSIC(quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg1;
extern Sprite * spr_nutmeg2;
extern Sprite * spr_camera;
//struct Sprite * spr_nutmegbow;

//water tiles are stored in 1A, 1B, and 1C
//in GBTD, water is 26, 27, 28
const unsigned char level2_water1[] = {
	0x00,0x08,0x08,0x3c,0x3c,0xff,0xff,0xfb,
	0xff,0xdf,0xf7,0xff,0x7f,0xff,0xfd,0xff
};
const unsigned char level2_water2[] = {
	0x00,0x20,0x20,0xf3,0xf3,0xff,0xff,0xff,
	0xdf,0xff,0xff,0xf7,0x7f,0xff,0xfd,0xff
};
const unsigned char level2_water3[] = {
	0x00,0x82,0x82,0xcf,0xcf,0xff,0xff,0xfb,
	0xdf,0xff,0xff,0xf7,0x7f,0xff,0xfd,0xff
};

/*
//water anim data locations
const unsigned char level_water_anim1[] = { 0x1A };
const unsigned char level_water_anim2[] = { 0x1B };
const unsigned char level_water_anim3[] = { 0x1C };
*/

//grey top
const unsigned char grey2_33[] = {
	0xff,0x3c,0xc3,0x46,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};
const unsigned char grey2_34[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};
const unsigned char grey2_35[] = {
	0xff,0x3c,0xc3,0x7a,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};
const unsigned char grey2_36[] = {
	0xff,0x3c,0xc3,0x42,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink top
const unsigned char pink2_37[] = {
	0xff,0x3c,0xc3,0x42,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};
const unsigned char pink2_38[] = {
	0xff,0x3c,0xc3,0x5e,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};
const unsigned char pink2_39[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};
const unsigned char pink2_40[] = {
	0xff,0x3c,0xc3,0x62,0x81,0x81,0x81,0x81,
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff
};

//grey mid/bottom
const unsigned char grey2_41[] = {
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};
const unsigned char grey2_42[] = {
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};
const unsigned char grey2_43[] = {
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};
const unsigned char grey2_44[] = {
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink mid/bottom
const unsigned char pink2_45[] = {
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};
const unsigned char pink2_46[] = {
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};
const unsigned char pink2_47[] = {
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};
const unsigned char pink2_48[] = {
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81,
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff
};

/*
//flagpole data locations
const unsigned char flagpole1[] = { 0x21 };
const unsigned char flagpole2[] = { 0x29 };
const unsigned char flagpole3[] = { 0x2A };
*/

//Level Start! Text
const unsigned char UpperL2[] = {
	0xff,0x00,0xff,0x20,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerE2[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x24,0xff,0x38,0xff,0x20,0xff,0x1c
};
const unsigned char LowerV2[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x44,
	0xff,0x44,0xff,0x28,0xff,0x28,0xff,0x10
};
const unsigned char LowerL2[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x38
};
const unsigned char UpperS2[] = {
	0xff,0x00,0xff,0x18,0xff,0x24,0xff,0x20,
	0xff,0x18,0xff,0x04,0xff,0x24,0xff,0x18
};
const unsigned char LowerT2[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x78,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerA2[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x04,0xff,0x1c,0xff,0x24,0xff,0x1a
};
const unsigned char LowerR2[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x20
};
const unsigned char Exclam2[] = {
	0xff,0x00,0xff,0x10,0xff,0x10,0xff,0x10,
	0xff,0x10,0xff,0x10,0xff,0x00,0xff,0x10
};
const unsigned char BlankSky2[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00
};

const unsigned char Letter1_2[]  = { 0x54 }; //54-5E
const unsigned char Letter2_2[]  = { 0x55 };
const unsigned char Letter3_2[]  = { 0x56 };
const unsigned char Letter4_2[]  = { 0x57 };
const unsigned char Letter5_2[]  = { 0x58 };
const unsigned char Letter6_2[]  = { 0x59 };
const unsigned char Letter7_2[]  = { 0x5A };
const unsigned char Letter8_2[]  = { 0x5B };
const unsigned char Letter9_2[]  = { 0x5C };
const unsigned char Letter10_2[] = { 0x5D };
const unsigned char Letter11_2[] = { 0x5E };

//nutmeg sprite region
//UINT8 nut_region;

//deathmusicplayed = false;

void Start_StateLevel2() {
	level2counter = 0;
	SPRITES_8x16;

	nut_region = 0;
	pitdeathactive = true;

	deathmusicplayed = false;

	PlayMusic(quickstart, 1);
	//PlayMusic(mushrooms_mod_Data, 3, 1);

	//SetPalette (BG_PALETTE, 0, 8, bg_palette_level2, bank_StateLevel2);
	//SetPalette (SPRITES_PALETTE, 0, 8, sprites_palette_level2, bank_StateLevel2);

	//for(i = 0; i != N_SPRITE_TYPES; ++ i) { SpriteManagerLoad(i); }

	SpriteManagerLoad(2);  //acorn
	SpriteManagerLoad(3);  //butterfly
	SpriteManagerLoad(4);  //bunny
	SpriteManagerLoad(5);  //camera
	SpriteManagerLoad(6);  //nutmeg1
	SpriteManagerLoad(7);  //nutmeg2
	SpriteManagerLoad(10); //star
	SpriteManagerLoad(11); //star
	SpriteManagerLoad(12); //puff
	SpriteManagerLoad(13); //puff
	SpriteManagerLoad(31); //mushroom
	//SpriteManagerLoad(32); //nutmegbow
	//SpriteManagerLoad(30); //power leaf

	scroll_target = spr_camera = SpriteManagerAdd(SpriteCamera, 4, 49); //36
	//spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, 56, 68);
	spr_nutmeg1 = SpriteManagerAdd(SpriteNutmeg1, 4, 49); //36
	spr_nutmeg2 = SpriteManagerAdd(SpriteNutmeg2, 20, 49); //52

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level2map), &level2map, collision_tiles_level2, 0);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	flagpole_activated2 = 0;
	endlevel_counter2 = 0;

	SHOW_SPRITES;
	SHOW_BKG;

	//WY_REG = 136;
	//SHOW_WIN;
}

void Update_StateLevel2() {
	if (nutmeg_death == true) {
		if (deathmusicplayed == false) {
			__critical { PlayMusic(quickdeath, 1); }
			deathmusicplayed = true;
		}

		if (nutmegdeathtimer >= 125) {
			if (GameOver == true) {
				SetState(StateGameOver);
			}
			else if (GameOver == false) {
				SetState(StateOverworld1); // change to correct world
			}
		}

		nutmegdeathtimer++;
	}
	
	if (cutscenemode == enabled) {
		//Level Start!
		//Make Nutmeg Walk In
		if (level2counter == 0) {
			cutscenewalkright = true;
		}
		else if (level2counter >= 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		if (level2counter >= 10 && level2counter < 40) {
			set_bkg_data (0x54, 1, UpperL2);
			set_bkg_data (0x55, 1, LowerE2);
			set_bkg_data (0x56, 1, LowerV2);
			set_bkg_data (0x57, 1, LowerE2);
			set_bkg_data (0x58, 1, LowerL2);
			set_bkg_data (0x59, 1, UpperS2);
			set_bkg_data (0x5A, 1, LowerT2);
			set_bkg_data (0x5B, 1, LowerA2);
			set_bkg_data (0x5C, 1, LowerR2);
			set_bkg_data (0x5D, 1, LowerT2);
			set_bkg_data (0x5E, 1, Exclam2);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_2); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_2);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_2);
			set_bkg_tiles (10, 5, 1, 1, Letter4_2);
			set_bkg_tiles (11, 5, 1, 1, Letter5_2);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_2);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_2);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_2);
			set_bkg_tiles (10, 6, 1, 1, Letter9_2);
			set_bkg_tiles (11, 6, 1, 1, Letter10_2);
			set_bkg_tiles (12, 6, 1, 1, Letter11_2);
		}
		else if (level2counter >= 40 && level2counter < 70) {
			set_bkg_data (0x54, 1, BlankSky2);
			set_bkg_data (0x55, 1, BlankSky2);
			set_bkg_data (0x56, 1, BlankSky2);
			set_bkg_data (0x57, 1, BlankSky2);
			set_bkg_data (0x58, 1, BlankSky2);
			set_bkg_data (0x59, 1, BlankSky2);
			set_bkg_data (0x5A, 1, BlankSky2);
			set_bkg_data (0x5B, 1, BlankSky2);
			set_bkg_data (0x5C, 1, BlankSky2);
			set_bkg_data (0x5D, 1, BlankSky2);
			set_bkg_data (0x5E, 1, BlankSky2);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_2); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_2);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_2);
			set_bkg_tiles (10, 5, 1, 1, Letter4_2);
			set_bkg_tiles (11, 5, 1, 1, Letter5_2);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_2);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_2);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_2);
			set_bkg_tiles (10, 6, 1, 1, Letter9_2);
			set_bkg_tiles (11, 6, 1, 1, Letter10_2);
			set_bkg_tiles (12, 6, 1, 1, Letter11_2);
		}
		else if (level2counter >= 70 && level2counter < 100) {
			set_bkg_data (0x54, 1, UpperL2);
			set_bkg_data (0x55, 1, LowerE2);
			set_bkg_data (0x56, 1, LowerV2);
			set_bkg_data (0x57, 1, LowerE2);
			set_bkg_data (0x58, 1, LowerL2);
			set_bkg_data (0x59, 1, UpperS2);
			set_bkg_data (0x5A, 1, LowerT2);
			set_bkg_data (0x5B, 1, LowerA2);
			set_bkg_data (0x5C, 1, LowerR2);
			set_bkg_data (0x5D, 1, LowerT2);
			set_bkg_data (0x5E, 1, Exclam2);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_2); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_2);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_2);
			set_bkg_tiles (10, 5, 1, 1, Letter4_2);
			set_bkg_tiles (11, 5, 1, 1, Letter5_2);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_2);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_2);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_2);
			set_bkg_tiles (10, 6, 1, 1, Letter9_2);
			set_bkg_tiles (11, 6, 1, 1, Letter10_2);
			set_bkg_tiles (12, 6, 1, 1, Letter11_2);
		}
		else if (level2counter >= 100 && level2counter < 101) {
			set_bkg_data (0x54, 1, BlankSky2);
			set_bkg_data (0x55, 1, BlankSky2);
			set_bkg_data (0x56, 1, BlankSky2);
			set_bkg_data (0x57, 1, BlankSky2);
			set_bkg_data (0x58, 1, BlankSky2);
			set_bkg_data (0x59, 1, BlankSky2);
			set_bkg_data (0x5A, 1, BlankSky2);
			set_bkg_data (0x5B, 1, BlankSky2);
			set_bkg_data (0x5C, 1, BlankSky2);
			set_bkg_data (0x5D, 1, BlankSky2);
			set_bkg_data (0x5E, 1, BlankSky2);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_2); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_2);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_2);
			set_bkg_tiles (10, 5, 1, 1, Letter4_2);
			set_bkg_tiles (11, 5, 1, 1, Letter5_2);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_2);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_2);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_2);
			set_bkg_tiles (10, 6, 1, 1, Letter9_2);
			set_bkg_tiles (11, 6, 1, 1, Letter10_2);
			set_bkg_tiles (12, 6, 1, 1, Letter11_2);

			cutscenemode = disabled;

			if (flagpole_activated2 == 0) {
				PlayMusic(mushrooms, 1);
			}
		}

		if (level2counter < 105) level2counter++;
	}

	//animate water
	if (anim_water_counter2 >= 0 && anim_water_counter2 < 10) {
		set_bkg_data (0x1A, 1, level2_water1);
		set_bkg_data (0x1B, 1, level2_water2);
		set_bkg_data (0x1C, 1, level2_water3);
	}
	else if (anim_water_counter2 >= 10 && anim_water_counter2 < 20) {
		set_bkg_data (0x1A, 1, level2_water2);
		set_bkg_data (0x1B, 1, level2_water3);
		set_bkg_data (0x1C, 1, level2_water1);
	}
	else if (anim_water_counter2 >= 20 && anim_water_counter2 < 30) {
		set_bkg_data (0x1A, 1, level2_water3);
		set_bkg_data (0x1B, 1, level2_water1);
		set_bkg_data (0x1C, 1, level2_water2);
	}
	anim_water_counter2++;
	if (anim_water_counter2 >= 30) anim_water_counter2 = 0;

	//animate grey flagpole
	if (flagpole_activated2 == 0) {
		if (anim_flag_counter2 >= 0 && anim_flag_counter2 < 12) {
			set_bkg_data (0x21, 1, grey2_33);
			set_bkg_data (0x29, 1, grey2_41);
			set_bkg_data (0x2A, 1, grey2_41);
		}
		else if (anim_flag_counter2 >= 12 && anim_flag_counter2 < 24) {
			set_bkg_data (0x21, 1, grey2_34);
			set_bkg_data (0x29, 1, grey2_42);
			set_bkg_data (0x2A, 1, grey2_42);
		}
		else if (anim_flag_counter2 >= 24 && anim_flag_counter2 < 36) {
			set_bkg_data (0x21, 1, grey2_35);
			set_bkg_data (0x29, 1, grey2_43);
			set_bkg_data (0x2A, 1, grey2_43);
		}
		else if (anim_flag_counter2 >= 36 && anim_flag_counter2 < 48) {
			set_bkg_data (0x21, 1, grey2_36);
			set_bkg_data (0x29, 1, grey2_44);
			set_bkg_data (0x2A, 1, grey2_44);
		}
		anim_flag_counter2++;
		if (anim_flag_counter2 >= 48) anim_flag_counter2 = 0;
	}
	//animate pink flagpole
	else if (flagpole_activated2 == 1) {
		cutscenemode = enabled;
		
		if (spr_nutmeg1->x > 1956) {
			cutscenewalkright = false;
			cutscenewalkleft = true;
		}
		else if (spr_nutmeg1->x < 1956) {
			cutscenewalkright = true;
			cutscenewalkleft = false;
		}
		else if (spr_nutmeg1->x == 1956) {
			cutscenewalkright = false;
			cutscenewalkleft = false;
		}

		if (endlevel_counter2 == 10) {
			SpriteManagerAdd(SpriteStarLeft, 1948, 96);
			SpriteManagerAdd(SpriteStarRight, 1956, 96);
		}
		else if (endlevel_counter2 == 30) {
			SpriteManagerAdd(SpriteStarLeft, 1948, 80);
			SpriteManagerAdd(SpriteStarRight, 1956, 80);
		}
		else if (endlevel_counter2 == 60) {
			SpriteManagerAdd(SpriteStarLeft, 1948, 64);
			SpriteManagerAdd(SpriteStarRight, 1956, 64);
		}
		else if (endlevel_counter2 >= 100) {
			//endlevel_counter2 = 0;
			//cutscenewalkleft = false;
			//cutscenewalkright = false;
			//cutscenemode = disabled;

			SetState(StateOverworld1);
		}

		if (endlevel_counter2 < 250) endlevel_counter2++;

		//spawn some stars
		/*
		if (flagpole_stars2 < 1) {
			SpriteManagerAdd(SpriteStarLeft, spr_nutmeg1->x, spr_nutmeg1->y);
			SpriteManagerAdd(SpriteStarRight, spr_nutmeg1->x, spr_nutmeg1->y);

			//SpriteManagerAdd(SpriteStarLeft, 244, 10);
			//SpriteManagerAdd(SpriteStarRight, 244, 10);
		}
		else if (flagpole_stars2 >= 5 && flagpole_stars2 < 10) {
			SpriteManagerAdd(SpriteStarLeft, 244, 10);
			SpriteManagerAdd(SpriteStarRight, 244, 10);
		}
		else if (flagpole_stars2 >= 10 && flagpole_stars2 < 20) {
			SpriteManagerAdd(SpriteStarLeft, 244, 7);
			SpriteManagerAdd(SpriteStarRight, 244, 7);
		}
		*/

		//change flagpole color palette to pink
		//set_bkg_palette (1, 1, pal_pink2);
		SetPalette(BG_PALETTE, 1, 1, pal_pink2, _current_bank);

		if (anim_flag_counter2 >= 0 && anim_flag_counter2 < 5) {
			set_bkg_data (0x21, 1, pink2_37);
			set_bkg_data (0x29, 1, pink2_45);
			set_bkg_data (0x2A, 1, pink2_45);
		}
		else if (anim_flag_counter2 >= 5 && anim_flag_counter2 < 10) {
			set_bkg_data (0x21, 1, pink2_38);
			set_bkg_data (0x29, 1, pink2_46);
			set_bkg_data (0x2A, 1, pink2_46);
		}
		else if (anim_flag_counter2 >= 10 && anim_flag_counter2 < 15) {
			set_bkg_data (0x21, 1, pink2_39);
			set_bkg_data (0x29, 1, pink2_47);
			set_bkg_data (0x2A, 1, pink2_47);
		}
		else if (anim_flag_counter2 >= 15 && anim_flag_counter2 < 20) {
			set_bkg_data (0x21, 1, pink2_40);
			set_bkg_data (0x29, 1, pink2_48);
			set_bkg_data (0x2A, 1, pink2_48);
		}
		anim_flag_counter2++;
		if (anim_flag_counter2 >= 20) anim_flag_counter2 = 0;

		if (flagpole_stars2 < 20) flagpole_stars2++;
	}

	if (spr_nutmeg1->x >= 1936 && spr_nutmeg1->x < 1944 && flagpole_activated2 == 0) {
		flagpole_activated2 = 1;
		levelbeat = true;
		endlevel_counter2 = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
		__critical { PlayMusic(flagpole, 1); }
		//distance = 0;
		//SetState(StateOverworld1);
	}

	/*
	//starshooter
	if (KEY_PRESSED(J_A)) {
		if (starshooter == 0) {
			SpriteManagerAdd(SpriteStarLeft, spr_nutmeg1->x, spr_nutmeg1->y);
			starshooter = 1;
		}
    }
	if (starshooter > 0) starshooter++;
	if (starshooter >= 5) starshooter = 0;
	*/
	
	/*
	if (KEY_PRESSED(J_START)) {
        SetState(StateOverworld1);
    }
	*/

	/*  REGIONS  */
	// 0 = 0-250
	// 1 = 251-500
	// 2 = 501-750
	// 3 = 751-1000
	// 4 = 1001-1250
	// 5 = 1251-1500
	// 6 = 1501-1750
	// 7 = 1751-2000

	// 0 = 0-32
	// 1 = 32-63
	// 2 = 63-94
	// 3 = 94-125
	// 4 = 125-156
	// 5 = 156-188
	// 6 = 188-219
	// 7 = 219-250

	// 0-63:
	if (spr_nutmeg1->x > 0 && spr_nutmeg1->x <= 250 && nut_region <= 0) {
		SpriteManagerAdd(SpriteAcorn, 27*8, 12*8);
		SpriteManagerAdd(EnemyBunny, 37*8, 13*8); //Bunny always 1 higher in y value
		SpriteManagerAdd(SpriteAcorn, 43*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 53*8, 4*8);
		SpriteManagerAdd(EnemyButterfly, 57*8, 3*8);
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_nutmeg1->x > 250 && spr_nutmeg1->x <= 500 && nut_region <= 1) {
		SpriteManagerAdd(SpriteAcorn, 68*8, 2*8);
		SpriteManagerAdd(SpriteAcorn, 77*8, 8*8);
		SpriteManagerAdd(SpriteAcorn, 91*8, 6*8);
    	nut_region = 2;
	}
	// Up to 125:
	else if (spr_nutmeg1->x > 500 && spr_nutmeg1->x <= 750 && nut_region <= 2) {
		SpriteManagerAdd(EnemyButterfly, 99*8, 10*8);
	    nut_region = 3;
	}
	// Up to 156:
	else if (spr_nutmeg1->x > 750 && spr_nutmeg1->x <= 1000 && nut_region <= 3) {
		SpriteManagerAdd(SpriteAcorn, 133*8, 9*8);
		SpriteManagerAdd(SpriteAcorn, 136*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 139*8, 9*8);
	    nut_region = 4;
	}
	// Up to 188:
	else if (spr_nutmeg1->x > 1000 && spr_nutmeg1->x <= 1250 && nut_region <= 4) {
		SpriteManagerAdd(EnemyBunny, 160*8, 12*8); //Bunny always 1 higher in y value
		SpriteManagerAdd(SpriteMushroom, 167*8, 12*8);
		SpriteManagerAdd(SpriteAcorn, 176*8, 5*8);
		SpriteManagerAdd(SpriteAcorn, 179*8, 8*8);
		SpriteManagerAdd(SpriteMushroom, 190*8, 13*8);
	    nut_region = 5;
	}
	// Up to 219:
	else if (spr_nutmeg1->x > 1250 && spr_nutmeg1->x <= 1500 && nut_region <= 5) {
		SpriteManagerAdd(EnemyButterfly, 198*8, 13*8);
		SpriteManagerAdd(SpriteAcorn, 207*8, 7*8);
		SpriteManagerAdd(EnemyButterfly, 216*8, 11*8);
	    nut_region = 6;
	}
	// Up to 250:
	else if (spr_nutmeg1->x > 1500 && spr_nutmeg1->x <= 1750 && nut_region <= 6) {
		//
	    nut_region = 7;
	}
	else if (spr_nutmeg1->x > 1750 && spr_nutmeg1->x <= 2000 && nut_region <= 7) {
		//
	    nut_region = 8;
	}
}