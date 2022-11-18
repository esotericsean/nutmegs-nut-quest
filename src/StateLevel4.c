#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>

#include "..\res\src\level1tiles.h"
//#include "..\res\src\level4map.h"

#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "../res/src/nutmeg.h"
#include "../res/src/acorn.h"
#include "../res/src/star.h"
#include "../res/src/puff.h"
#include "../res/src/mushroom.h"
#include "../res/src/fish.h"
#include "../res/src/butterfly.h"
#include "../res/src/bunny.h"
//#include "../res/src/powerleaf.h"
//#include "../res/src/nutmegbow.h"
#include "Palette.h"

#include "../src/GlobalVars.h"

IMPORT_MAP (level4map);

UINT16 level4counter = 0;

UINT8 anim_water_counter4 = 0;
UINT8 anim_flag_counter4 = 0;
UINT8 flagpole_activated4 = 0;
UINT8 flagpole_stars4 = 0;
UINT8 endlevel_counter4 = 0;
//UINT8 starshooter = 0;

//pink color palette
const UWORD pal_pink4[] = {
	RGB(31, 31, 31),
	RGB(19, 26, 30),
	RGB(28, 19, 30),
	RGB(0,  0,  0)
};

const UINT16 bg_palette_level4[] = {
	PALETTE_FROM_HEADER(level1tiles)
};

const UINT16 sprites_palette_level4[] = {
	PALETTE_INDEX (nutmeg, 0),
	PALETTE_INDEX (acorn, 1),
	PALETTE_INDEX (mushroom, 4),
	PALETTE_INDEX (star, 2),
	PALETTE_INDEX (puff, 3),
	PALETTE_INDEX (fish, 5),
	PALETTE_INDEX (butterfly, 2),
	PALETTE_INDEX (bunny, 6)
};

const UINT8 collision_tiles_level4[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
const UINT8 collision_tiles_down_level4[] = {29,30,31,32};

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
extern Sprite * spr_nutmeg;
//extern Sprite * spr_nutmeg2;
extern Sprite * spr_camera;
//struct Sprite * spr_nutmegbow;

//water tiles are stored in 1A, 1B, and 1C
//in GBTD, water is 26, 27, 28
const unsigned char level4_water1[] = {
	0x00,0x08,0x08,0x3c,0x3c,0xff,0xff,0xfb,
	0xff,0xdf,0xf7,0xff,0x7f,0xff,0xfd,0xff
};
const unsigned char level4_water2[] = {
	0x00,0x20,0x20,0xf3,0xf3,0xff,0xff,0xff,
	0xdf,0xff,0xff,0xf7,0x7f,0xff,0xfd,0xff
};
const unsigned char level4_water3[] = {
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
const unsigned char grey4_33[] = {
	0xff,0x3c,0xc3,0x46,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};
const unsigned char grey4_34[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};
const unsigned char grey4_35[] = {
	0xff,0x3c,0xc3,0x7a,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};
const unsigned char grey4_36[] = {
	0xff,0x3c,0xc3,0x42,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink top
const unsigned char pink4_37[] = {
	0xff,0x3c,0xc3,0x42,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};
const unsigned char pink4_38[] = {
	0xff,0x3c,0xc3,0x5e,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};
const unsigned char pink4_39[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};
const unsigned char pink4_40[] = {
	0xff,0x3c,0xc3,0x62,0x81,0x81,0x81,0x81,
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff
};

//grey mid/bottom
const unsigned char grey4_41[] = {
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};
const unsigned char grey4_42[] = {
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};
const unsigned char grey4_43[] = {
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};
const unsigned char grey4_44[] = {
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink mid/bottom
const unsigned char pink4_45[] = {
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};
const unsigned char pink4_46[] = {
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};
const unsigned char pink4_47[] = {
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};
const unsigned char pink4_48[] = {
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
const unsigned char UpperL4[] = {
	0xff,0x00,0xff,0x20,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerE4[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x24,0xff,0x38,0xff,0x20,0xff,0x1c
};
const unsigned char LowerV4[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x44,
	0xff,0x44,0xff,0x28,0xff,0x28,0xff,0x10
};
const unsigned char LowerL4[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x38
};
const unsigned char UpperS4[] = {
	0xff,0x00,0xff,0x18,0xff,0x24,0xff,0x20,
	0xff,0x18,0xff,0x04,0xff,0x24,0xff,0x18
};
const unsigned char LowerT4[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x78,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerA4[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x04,0xff,0x1c,0xff,0x24,0xff,0x1a
};
const unsigned char LowerR4[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x20
};
const unsigned char Exclam4[] = {
	0xff,0x00,0xff,0x10,0xff,0x10,0xff,0x10,
	0xff,0x10,0xff,0x10,0xff,0x00,0xff,0x10
};
const unsigned char BlankSky4[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00
};

const unsigned char Letter1_4[]  = { 0x54 }; //54-5E
const unsigned char Letter2_4[]  = { 0x55 };
const unsigned char Letter3_4[]  = { 0x56 };
const unsigned char Letter4_4[]  = { 0x57 };
const unsigned char Letter5_4[]  = { 0x58 };
const unsigned char Letter6_4[]  = { 0x59 };
const unsigned char Letter7_4[]  = { 0x5A };
const unsigned char Letter8_4[]  = { 0x5B };
const unsigned char Letter9_4[]  = { 0x5C };
const unsigned char Letter10_4[] = { 0x5D };
const unsigned char Letter11_4[] = { 0x5E };

//nutmeg sprite region
//UINT8 nut_region;

//deathmusicplayed = false;

void Start_StateLevel4() {
	level4counter = 0;
	levelorientation = horizontal;
	SPRITES_8x16;

	nut_region = 0;
	pitdeathactive = true;

	deathmusicplayed = false;

	PlayMusic(quickstart, 1);
	//PlayMusic(mushrooms_mod_Data, 3, 1);

	//SetPalette (BG_PALETTE, 0, 8, bg_palette_level4, bank_StateLevel4);
	SetPalette (SPRITES_PALETTE, 0, 8, sprites_palette_level4, _current_bank);

	//for(i = 0; i != N_SPRITE_TYPES; ++ i) { SpriteManagerLoad(i); }

	//SpriteManagerLoad(35);  //nutmeg
	//SpriteManagerLoad(31); //mushroom
	//SpriteManagerLoad(2);  //acorn
	//SpriteManagerLoad(19); //fish
	//SpriteManagerLoad(3);  //butterfly
	//SpriteManagerLoad(4);  //bunny
	//SpriteManagerLoad(10); //star
	//SpriteManagerLoad(11); //star
	//SpriteManagerLoad(12); //puff
	//SpriteManagerLoad(13); //puff

	//scroll_target = spr_camera = SpriteManagerAdd(SpriteCamera, 4, 49); //36
	//spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, 56, 68);
	scroll_target = spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 4, 49); //36
	//spr_nutmeg2 = SpriteManagerAdd(SpriteNutmeg2, 20, 49); //52

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level4map), &level4map, collision_tiles_level4, collision_tiles_down_level4);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	flagpole_activated4 = 0;
	endlevel_counter4 = 0;

	SHOW_SPRITES;
	SHOW_BKG;

	//WY_REG = 136;
	//SHOW_WIN;
}

void Update_StateLevel4() {
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
		if (level4counter == 0) {
			cutscenewalkright = true;
		}
		else if (level4counter >= 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		if (level4counter >= 10 && level4counter < 40) {
			set_bkg_data (0x54, 1, UpperL4);
			set_bkg_data (0x55, 1, LowerE4);
			set_bkg_data (0x56, 1, LowerV4);
			set_bkg_data (0x57, 1, LowerE4);
			set_bkg_data (0x58, 1, LowerL4);
			set_bkg_data (0x59, 1, UpperS4);
			set_bkg_data (0x5A, 1, LowerT4);
			set_bkg_data (0x5B, 1, LowerA4);
			set_bkg_data (0x5C, 1, LowerR4);
			set_bkg_data (0x5D, 1, LowerT4);
			set_bkg_data (0x5E, 1, Exclam4);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_4); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_4);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_4);
			set_bkg_tiles (10, 5, 1, 1, Letter4_4);
			set_bkg_tiles (11, 5, 1, 1, Letter5_4);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_4);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_4);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_4);
			set_bkg_tiles (10, 6, 1, 1, Letter9_4);
			set_bkg_tiles (11, 6, 1, 1, Letter10_4);
			set_bkg_tiles (12, 6, 1, 1, Letter11_4);
		}
		else if (level4counter >= 40 && level4counter < 70) {
			set_bkg_data (0x54, 1, BlankSky4);
			set_bkg_data (0x55, 1, BlankSky4);
			set_bkg_data (0x56, 1, BlankSky4);
			set_bkg_data (0x57, 1, BlankSky4);
			set_bkg_data (0x58, 1, BlankSky4);
			set_bkg_data (0x59, 1, BlankSky4);
			set_bkg_data (0x5A, 1, BlankSky4);
			set_bkg_data (0x5B, 1, BlankSky4);
			set_bkg_data (0x5C, 1, BlankSky4);
			set_bkg_data (0x5D, 1, BlankSky4);
			set_bkg_data (0x5E, 1, BlankSky4);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_4); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_4);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_4);
			set_bkg_tiles (10, 5, 1, 1, Letter4_4);
			set_bkg_tiles (11, 5, 1, 1, Letter5_4);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_4);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_4);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_4);
			set_bkg_tiles (10, 6, 1, 1, Letter9_4);
			set_bkg_tiles (11, 6, 1, 1, Letter10_4);
			set_bkg_tiles (12, 6, 1, 1, Letter11_4);
		}
		else if (level4counter >= 70 && level4counter < 100) {
			set_bkg_data (0x54, 1, UpperL4);
			set_bkg_data (0x55, 1, LowerE4);
			set_bkg_data (0x56, 1, LowerV4);
			set_bkg_data (0x57, 1, LowerE4);
			set_bkg_data (0x58, 1, LowerL4);
			set_bkg_data (0x59, 1, UpperS4);
			set_bkg_data (0x5A, 1, LowerT4);
			set_bkg_data (0x5B, 1, LowerA4);
			set_bkg_data (0x5C, 1, LowerR4);
			set_bkg_data (0x5D, 1, LowerT4);
			set_bkg_data (0x5E, 1, Exclam4);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_4); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_4);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_4);
			set_bkg_tiles (10, 5, 1, 1, Letter4_4);
			set_bkg_tiles (11, 5, 1, 1, Letter5_4);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_4);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_4);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_4);
			set_bkg_tiles (10, 6, 1, 1, Letter9_4);
			set_bkg_tiles (11, 6, 1, 1, Letter10_4);
			set_bkg_tiles (12, 6, 1, 1, Letter11_4);
		}
		else if (level4counter >= 100 && level4counter < 101) {
			set_bkg_data (0x54, 1, BlankSky4);
			set_bkg_data (0x55, 1, BlankSky4);
			set_bkg_data (0x56, 1, BlankSky4);
			set_bkg_data (0x57, 1, BlankSky4);
			set_bkg_data (0x58, 1, BlankSky4);
			set_bkg_data (0x59, 1, BlankSky4);
			set_bkg_data (0x5A, 1, BlankSky4);
			set_bkg_data (0x5B, 1, BlankSky4);
			set_bkg_data (0x5C, 1, BlankSky4);
			set_bkg_data (0x5D, 1, BlankSky4);
			set_bkg_data (0x5E, 1, BlankSky4);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_4); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_4);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_4);
			set_bkg_tiles (10, 5, 1, 1, Letter4_4);
			set_bkg_tiles (11, 5, 1, 1, Letter5_4);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_4);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_4);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_4);
			set_bkg_tiles (10, 6, 1, 1, Letter9_4);
			set_bkg_tiles (11, 6, 1, 1, Letter10_4);
			set_bkg_tiles (12, 6, 1, 1, Letter11_4);

			cutscenemode = disabled;

			if (flagpole_activated4 == 0) {
				PlayMusic(mushrooms, 1);
			}
		}

		if (level4counter < 105) level4counter++;
	}

	//animate water
	if (anim_water_counter4 >= 0 && anim_water_counter4 < 10) {
		set_bkg_data (0x1A, 1, level4_water1);
		set_bkg_data (0x1B, 1, level4_water2);
		set_bkg_data (0x1C, 1, level4_water3);
	}
	else if (anim_water_counter4 >= 10 && anim_water_counter4 < 20) {
		set_bkg_data (0x1A, 1, level4_water2);
		set_bkg_data (0x1B, 1, level4_water3);
		set_bkg_data (0x1C, 1, level4_water1);
	}
	else if (anim_water_counter4 >= 20 && anim_water_counter4 < 30) {
		set_bkg_data (0x1A, 1, level4_water3);
		set_bkg_data (0x1B, 1, level4_water1);
		set_bkg_data (0x1C, 1, level4_water2);
	}
	anim_water_counter4++;
	if (anim_water_counter4 >= 30) anim_water_counter4 = 0;

	//animate grey flagpole
	if (flagpole_activated4 == 0) {
		if (anim_flag_counter4 >= 0 && anim_flag_counter4 < 12) {
			set_bkg_data (0x21, 1, grey4_33);
			set_bkg_data (0x29, 1, grey4_41);
			set_bkg_data (0x2A, 1, grey4_41);
		}
		else if (anim_flag_counter4 >= 12 && anim_flag_counter4 < 24) {
			set_bkg_data (0x21, 1, grey4_34);
			set_bkg_data (0x29, 1, grey4_42);
			set_bkg_data (0x2A, 1, grey4_42);
		}
		else if (anim_flag_counter4 >= 24 && anim_flag_counter4 < 36) {
			set_bkg_data (0x21, 1, grey4_35);
			set_bkg_data (0x29, 1, grey4_43);
			set_bkg_data (0x2A, 1, grey4_43);
		}
		else if (anim_flag_counter4 >= 36 && anim_flag_counter4 < 48) {
			set_bkg_data (0x21, 1, grey4_36);
			set_bkg_data (0x29, 1, grey4_44);
			set_bkg_data (0x2A, 1, grey4_44);
		}
		anim_flag_counter4++;
		if (anim_flag_counter4 >= 48) anim_flag_counter4 = 0;
	}
	//animate pink flagpole
	else if (flagpole_activated4 == 1) {
		cutscenemode = enabled;
		cutscenewalkright = true;
		cutscenewalkleft = false;
		
		if (spr_nutmeg->x > 1956) {
			cutscenewalkright = true;
			cutscenewalkleft = false;
		}
		else if (spr_nutmeg->x < 1956) {
			cutscenewalkright = true;
			cutscenewalkleft = false;
		}
		else if (spr_nutmeg->x == 1956) {
			cutscenewalkright = true;
			cutscenewalkleft = false;
		}

		if (endlevel_counter4 == 10) {
			SpriteManagerAdd(SpriteStarLeft, 1948, 96);
			SpriteManagerAdd(SpriteStarRight, 1956, 96);
		}
		else if (endlevel_counter4 == 30) {
			SpriteManagerAdd(SpriteStarLeft, 1948, 80);
			SpriteManagerAdd(SpriteStarRight, 1956, 80);
		}
		else if (endlevel_counter4 == 50) {
			SpriteManagerAdd(SpriteStarLeft, 1948, 64);
			SpriteManagerAdd(SpriteStarRight, 1956, 64);
		}
		else if (endlevel_counter4 >= 100) {
			//endlevel_counter4 = 0;
			//cutscenewalkleft = false;
			//cutscenewalkright = false;
			//cutscenemode = disabled;

			SetState(StateOverworld1);
		}

		if (endlevel_counter4 < 250) endlevel_counter4++;

		//spawn some stars
		/*
		if (flagpole_stars4 < 1) {
			SpriteManagerAdd(SpriteStarLeft, spr_nutmeg->x, spr_nutmeg->y);
			SpriteManagerAdd(SpriteStarRight, spr_nutmeg->x, spr_nutmeg->y);

			//SpriteManagerAdd(SpriteStarLeft, 244, 10);
			//SpriteManagerAdd(SpriteStarRight, 244, 10);
		}
		else if (flagpole_stars4 >= 5 && flagpole_stars4 < 10) {
			SpriteManagerAdd(SpriteStarLeft, 244, 10);
			SpriteManagerAdd(SpriteStarRight, 244, 10);
		}
		else if (flagpole_stars4 >= 10 && flagpole_stars4 < 20) {
			SpriteManagerAdd(SpriteStarLeft, 244, 7);
			SpriteManagerAdd(SpriteStarRight, 244, 7);
		}
		*/

		//change flagpole color palette to pink
		//set_bkg_palette (1, 1, pal_pink4);
		SetPalette(BG_PALETTE, 1, 1, pal_pink4, _current_bank);

		if (anim_flag_counter4 >= 0 && anim_flag_counter4 < 5) {
			set_bkg_data (0x21, 1, pink4_37);
			set_bkg_data (0x29, 1, pink4_45);
			set_bkg_data (0x2A, 1, pink4_45);
		}
		else if (anim_flag_counter4 >= 5 && anim_flag_counter4 < 10) {
			set_bkg_data (0x21, 1, pink4_38);
			set_bkg_data (0x29, 1, pink4_46);
			set_bkg_data (0x2A, 1, pink4_46);
		}
		else if (anim_flag_counter4 >= 10 && anim_flag_counter4 < 15) {
			set_bkg_data (0x21, 1, pink4_39);
			set_bkg_data (0x29, 1, pink4_47);
			set_bkg_data (0x2A, 1, pink4_47);
		}
		else if (anim_flag_counter4 >= 15 && anim_flag_counter4 < 20) {
			set_bkg_data (0x21, 1, pink4_40);
			set_bkg_data (0x29, 1, pink4_48);
			set_bkg_data (0x2A, 1, pink4_48);
		}
		anim_flag_counter4++;
		if (anim_flag_counter4 >= 20) anim_flag_counter4 = 0;

		if (flagpole_stars4 < 20) flagpole_stars4++;
	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && flagpole_activated4 == 0) {
		flagpole_activated4 = 1;
		levelbeat = true;
		endlevel_counter4 = 0;
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
			SpriteManagerAdd(SpriteStarLeft, spr_nutmeg->x, spr_nutmeg->y);
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
	if (spr_nutmeg->x > 0 && spr_nutmeg->x <= 250 && nut_region <= 0) {
		SpriteManagerAdd(SpriteMushroom, 31*8, 12*8);
		SpriteManagerAdd(EnemyFish, 16*8, 16*8);
		SpriteManagerAdd(SpriteAcorn, 36*8, 5*8);
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_nutmeg->x > 250 && spr_nutmeg->x <= 500 && nut_region <= 1) {
		SpriteManagerAdd(SpriteAcorn, 43*8, 3*8);
		SpriteManagerAdd(SpriteAcorn, 50*8, 4*8);
		SpriteManagerAdd(SpriteAcorn, 57*8, 3*8);
		SpriteManagerAdd(SpriteAcorn, 64*8, 4*8);
		SpriteManagerAdd(EnemyButterfly, 74*8, 11*8);
    	nut_region = 2;
	}
	// Up to 125:
	else if (spr_nutmeg->x > 500 && spr_nutmeg->x <= 750 && nut_region <= 2) {
		SpriteManagerAdd(SpriteAcorn, 87*8, 12*8);
	    nut_region = 3;
	}
	// Up to 156:
	else if (spr_nutmeg->x > 750 && spr_nutmeg->x <= 1000 && nut_region <= 3) {
		SpriteManagerAdd(EnemyFish, 110*8, 16*8);
		SpriteManagerAdd(SpriteAcorn, 126*8, 5*8);
		SpriteManagerAdd(EnemyBunny, 126*8, 13*8);
		SpriteManagerAdd(SpriteAcorn, 129*8, 5*8);
	    nut_region = 4;
	}
	// Up to 188:
	else if (spr_nutmeg->x > 1000 && spr_nutmeg->x <= 1250 && nut_region <= 4) {
		SpriteManagerAdd(EnemyFish, 145*8, 16*8);
		SpriteManagerAdd(EnemyButterfly, 162*8, 10*8);
	    nut_region = 5;
	}
	// Up to 219:
	else if (spr_nutmeg->x > 1250 && spr_nutmeg->x <= 1500 && nut_region <= 5) {
	    SpriteManagerAdd(EnemyFish, 192*8, 16*8);
		SpriteManagerAdd(SpriteAcorn, 192*8+3, 6*8);
		SpriteManagerAdd(SpriteAcorn, 192*8+3, 8*8);
		SpriteManagerAdd(SpriteAcorn, 192*8+3, 10*8);
		nut_region = 6;
	}
	// Up to 250:
	else if (spr_nutmeg->x > 1500 && spr_nutmeg->x <= 1750 && nut_region <= 6) {
		SpriteManagerAdd(SpriteAcorn, 210*8, 12*8);
		SpriteManagerAdd(SpriteAcorn, 213*8, 12*8);
		SpriteManagerAdd(SpriteAcorn, 216*8, 12*8);
		SpriteManagerAdd(EnemyButterfly, 215*8, 8*8);
		SpriteManagerAdd(EnemyBunny, 225*8, 13*8);
	    nut_region = 7;
	}
	else if (spr_nutmeg->x > 1750 && spr_nutmeg->x <= 2000 && nut_region <= 7) {
		SpriteManagerAdd(SpriteAcorn, 234*8, 3*8);
	    nut_region = 8;
	}
}