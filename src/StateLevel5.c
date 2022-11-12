#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>

#include "..\res\src\level5tiles.h"
//#include "..\res\src\level5map.h"

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

IMPORT_MAP (level5map);

UINT16 level5counter = 0;

UINT8 anim_water_counter5 = 0;
UINT8 anim_rain_counter5 = 0;
UINT8 anim_flag_counter5 = 0;
UINT8 flagpole_activated5 = 0;
UINT8 flagpole_stars5 = 0;
UINT8 endlevel_counter5 = 0;
UINT8 lightningstrikecounter = 0;
//UINT8 starshooter = 0;

//pink color palette
const UWORD pal_pink5[] = {
	RGB(31, 31, 31),
	RGB(19, 26, 30),
	RGB(28, 19, 30),
	RGB(0,  0,  0)
};

const UINT16 bg_palette_level5[] = {
	PALETTE_FROM_HEADER(level5tiles)
};

const UINT16 sprites_palette_level5[] = {
	PALETTE_INDEX (nutmeg, 0),
	PALETTE_INDEX (acorn, 1),
	PALETTE_INDEX (mushroom, 4),
	PALETTE_INDEX (star, 2),
	PALETTE_INDEX (puff, 3),
	PALETTE_INDEX (fish, 5),
	PALETTE_INDEX (butterfly, 2),
	PALETTE_INDEX (bunny, 6)
};

const UINT8 collision_tiles_level5[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
const UINT8 collision_tiles_down_level5[] = {29,30,31,32};

//extern UINT8* quickstart_mod_Data[];
//extern UINT8* mushrooms_mod_Data[];
//extern UINT8* flagpole_mod_Data[];
//extern UINT8* quickdeath_mod_Data[];
//DECLARE_MUSIC(quickstart);
DECLARE_MUSIC(raindrops);
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
const unsigned char level5_water1[] = {
	0x00,0x08,0x08,0x3c,0x3c,0xff,0xff,0xfb,
	0xff,0xdf,0xf7,0xff,0x7f,0xff,0xfd,0xff
};
const unsigned char level5_water2[] = {
	0x00,0x20,0x20,0xf3,0xf3,0xff,0xff,0xff,
	0xdf,0xff,0xff,0xf7,0x7f,0xff,0xfd,0xff
};
const unsigned char level5_water3[] = {
	0x00,0x82,0x82,0xcf,0xcf,0xff,0xff,0xfb,
	0xdf,0xff,0xff,0xf7,0x7f,0xff,0xfd,0xff
};


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * R A I N * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Set 1:    100, 101, 102, 103 (start with 100)
// Set 2:    104, 105, 106, 107 (start with 106)
// Splash 1: 108, 109, 110, 111
// Splash 2: 112, 113, 114, 115

// Set 1 data:    0x64, 0x65, 0x66
// Set 2 data:    0x68, 0x69, 0x6A
// Splash 1 data: 0x6C, 0x6D, 0x6E
// Splash 2 data: 0x70, 0x71, 0x72

// Blank
const unsigned char rainblankwhite[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
const unsigned char rainblankblue[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00
};

// Set 1:
const unsigned char rainset1_pt1[] = {
	0xff,0x00,0xff,0x00,0xdf,0x00,0xdf,0x00,
	0xbf,0x00,0xbf,0x00,0xff,0x00,0xff,0x00
};
const unsigned char rainset1_pt2[] = {
	0xff,0x00,0xfe,0x00,0xfe,0x00,0xfd,0x00,
	0xfd,0x00,0xfb,0x00,0xfb,0x00,0xff,0x00
};
const unsigned char rainset1_pt3[] = {
	0xff,0x00,0xfb,0x00,0xfb,0x00,0xf7,0x00,
	0xb7,0x00,0xbf,0x00,0x7f,0x00,0x7f,0x00
};
const unsigned char rainset1_pt4[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0xbf,0x00,0xbf,0x00
};

// Set 2:
const unsigned char rainset2_pt1[] = {
	0xff,0x00,0xff,0x00,0xdf,0x00,0xdf,0x00,
	0xbf,0x00,0xbf,0x00,0xff,0x00,0xff,0x00
};
const unsigned char rainset2_pt2[] = {
	0xff,0x00,0xfe,0x00,0xfe,0x00,0xfd,0x00,
	0xfd,0x00,0xfb,0x00,0xfb,0x00,0xff,0x00
};
const unsigned char rainset2_pt3[] = {
	0xff,0x00,0xfb,0x00,0xfb,0x00,0xf7,0x00,
	0xb7,0x00,0xbf,0x00,0x7f,0x00,0x7f,0x00
};
const unsigned char rainset2_pt4[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0xbf,0x00,0xbf,0x00
};

// Splash 1:
const unsigned char rainsplash1_pt1[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x10,0x00,0x10,0x00,0x20,0x00,0x20,0x00
};
const unsigned char rainsplash1_pt2[] = {
	0x00,0x00,0x00,0x00,0x02,0x00,0x02,0x00,
	0x04,0x00,0x04,0x00,0x00,0x00,0x00,0x00
};
const unsigned char rainsplash1_pt3[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x40,0x00,0x08,0x00,0x10,0x00
};
const unsigned char rainsplash1_pt4[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x80,0x00,0x00,0x00,0x02,0x00,0x00,0x00
};

// Splash 2:
const unsigned char rainsplash2_pt1[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x10,0x00,0x10,0x00,0x20,0x00,0x20,0x00
};
const unsigned char rainsplash2_pt2[] = {
	0x00,0x00,0x00,0x00,0x02,0x00,0x02,0x00,
	0x04,0x00,0x04,0x00,0x00,0x00,0x00,0x00
};
const unsigned char rainsplash2_pt3[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x40,0x00,0x08,0x00,0x10,0x00
};
const unsigned char rainsplash2_pt4[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x80,0x00,0x00,0x00,0x02,0x00,0x00,0x00
};

/*
//water anim data locations
const unsigned char level_water_anim1[] = { 0x1A };
const unsigned char level_water_anim2[] = { 0x1B };
const unsigned char level_water_anim3[] = { 0x1C };
*/

//grey top
const unsigned char grey5_33[] = {
	0xff,0x3c,0xc3,0x46,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};
const unsigned char grey5_34[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};
const unsigned char grey5_35[] = {
	0xff,0x3c,0xc3,0x7a,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};
const unsigned char grey5_36[] = {
	0xff,0x3c,0xc3,0x42,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink top
const unsigned char pink5_37[] = {
	0xff,0x3c,0xc3,0x42,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};
const unsigned char pink5_38[] = {
	0xff,0x3c,0xc3,0x5e,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};
const unsigned char pink5_39[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};
const unsigned char pink5_40[] = {
	0xff,0x3c,0xc3,0x62,0x81,0x81,0x81,0x81,
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff
};

//grey mid/bottom
const unsigned char grey5_41[] = {
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};
const unsigned char grey5_42[] = {
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};
const unsigned char grey5_43[] = {
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};
const unsigned char grey5_44[] = {
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink mid/bottom
const unsigned char pink5_45[] = {
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};
const unsigned char pink5_46[] = {
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};
const unsigned char pink5_47[] = {
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};
const unsigned char pink5_48[] = {
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
const unsigned char UpperL5[] = {
	0xff,0x00,0xff,0x20,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerE5[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x24,0xff,0x38,0xff,0x20,0xff,0x1c
};
const unsigned char LowerV5[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x44,
	0xff,0x44,0xff,0x28,0xff,0x28,0xff,0x10
};
const unsigned char LowerL5[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x38
};
const unsigned char UpperS5[] = {
	0xff,0x00,0xff,0x18,0xff,0x24,0xff,0x20,
	0xff,0x18,0xff,0x04,0xff,0x24,0xff,0x18
};
const unsigned char LowerT5[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x78,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerA5[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x04,0xff,0x1c,0xff,0x24,0xff,0x1a
};
const unsigned char LowerR5[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x20
};
const unsigned char Exclam5[] = {
	0xff,0x00,0xff,0x10,0xff,0x10,0xff,0x10,
	0xff,0x10,0xff,0x10,0xff,0x00,0xff,0x10
};
const unsigned char BlankSky5[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00
};

const unsigned char Letter1_5[]  = { 0x54 }; //54-5E
const unsigned char Letter2_5[]  = { 0x55 };
const unsigned char Letter3_5[]  = { 0x56 };
const unsigned char Letter4_5[]  = { 0x57 };
const unsigned char Letter5_5[]  = { 0x58 };
const unsigned char Letter6_5[]  = { 0x59 };
const unsigned char Letter7_5[]  = { 0x5A };
const unsigned char Letter8_5[]  = { 0x5B };
const unsigned char Letter9_5[]  = { 0x5C };
const unsigned char Letter10_5[] = { 0x5D };
const unsigned char Letter11_5[] = { 0x5E };

//nutmeg sprite region
//UINT8 nut_region;

//deathmusicplayed = false;

void Start_StateLevel5() {
	level5counter = 0;
	levelorientation = horizontal;
	SPRITES_8x16;

	nut_region = 0;
	pitdeathactive = true;

	deathmusicplayed = false;

	PlayMusic(raindrops, 1);
	//PlayMusic(mushrooms_mod_Data, 3, 1);

	//SetPalette (BG_PALETTE, 0, 8, bg_palette_level5, bank_StateLevel5);
	SetPalette (SPRITES_PALETTE, 0, 8, sprites_palette_level5, _current_bank);

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

	InitScrollTiles(0, &level5tiles);
	InitScroll(BANK(level5map), &level5map, collision_tiles_level5, collision_tiles_down_level5);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	flagpole_activated5 = 0;
	endlevel_counter5 = 0;

	SHOW_SPRITES;
	SHOW_BKG;

	//WY_REG = 136;
	//SHOW_WIN;
}

void Update_StateLevel5() {
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
		if (level5counter == 0) {
			cutscenewalkright = true;
		}
		else if (level5counter >= 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		if (level5counter >= 10 && level5counter < 40) {
			set_bkg_data (0x54, 1, UpperL5);
			set_bkg_data (0x55, 1, LowerE5);
			set_bkg_data (0x56, 1, LowerV5);
			set_bkg_data (0x57, 1, LowerE5);
			set_bkg_data (0x58, 1, LowerL5);
			set_bkg_data (0x59, 1, UpperS5);
			set_bkg_data (0x5A, 1, LowerT5);
			set_bkg_data (0x5B, 1, LowerA5);
			set_bkg_data (0x5C, 1, LowerR5);
			set_bkg_data (0x5D, 1, LowerT5);
			set_bkg_data (0x5E, 1, Exclam5);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_5); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_5);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_5);
			set_bkg_tiles (10, 5, 1, 1, Letter4_5);
			set_bkg_tiles (11, 5, 1, 1, Letter5_5);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_5);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_5);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_5);
			set_bkg_tiles (10, 6, 1, 1, Letter9_5);
			set_bkg_tiles (11, 6, 1, 1, Letter10_5);
			set_bkg_tiles (12, 6, 1, 1, Letter11_5);
		}
		else if (level5counter >= 40 && level5counter < 70) {
			set_bkg_data (0x54, 1, BlankSky5);
			set_bkg_data (0x55, 1, BlankSky5);
			set_bkg_data (0x56, 1, BlankSky5);
			set_bkg_data (0x57, 1, BlankSky5);
			set_bkg_data (0x58, 1, BlankSky5);
			set_bkg_data (0x59, 1, BlankSky5);
			set_bkg_data (0x5A, 1, BlankSky5);
			set_bkg_data (0x5B, 1, BlankSky5);
			set_bkg_data (0x5C, 1, BlankSky5);
			set_bkg_data (0x5D, 1, BlankSky5);
			set_bkg_data (0x5E, 1, BlankSky5);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_5); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_5);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_5);
			set_bkg_tiles (10, 5, 1, 1, Letter4_5);
			set_bkg_tiles (11, 5, 1, 1, Letter5_5);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_5);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_5);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_5);
			set_bkg_tiles (10, 6, 1, 1, Letter9_5);
			set_bkg_tiles (11, 6, 1, 1, Letter10_5);
			set_bkg_tiles (12, 6, 1, 1, Letter11_5);
		}
		else if (level5counter >= 70 && level5counter < 100) {
			set_bkg_data (0x54, 1, UpperL5);
			set_bkg_data (0x55, 1, LowerE5);
			set_bkg_data (0x56, 1, LowerV5);
			set_bkg_data (0x57, 1, LowerE5);
			set_bkg_data (0x58, 1, LowerL5);
			set_bkg_data (0x59, 1, UpperS5);
			set_bkg_data (0x5A, 1, LowerT5);
			set_bkg_data (0x5B, 1, LowerA5);
			set_bkg_data (0x5C, 1, LowerR5);
			set_bkg_data (0x5D, 1, LowerT5);
			set_bkg_data (0x5E, 1, Exclam5);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_5); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_5);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_5);
			set_bkg_tiles (10, 5, 1, 1, Letter4_5);
			set_bkg_tiles (11, 5, 1, 1, Letter5_5);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_5);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_5);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_5);
			set_bkg_tiles (10, 6, 1, 1, Letter9_5);
			set_bkg_tiles (11, 6, 1, 1, Letter10_5);
			set_bkg_tiles (12, 6, 1, 1, Letter11_5);
		}
		else if (level5counter >= 100 && level5counter < 101) {
			set_bkg_data (0x54, 1, BlankSky5);
			set_bkg_data (0x55, 1, BlankSky5);
			set_bkg_data (0x56, 1, BlankSky5);
			set_bkg_data (0x57, 1, BlankSky5);
			set_bkg_data (0x58, 1, BlankSky5);
			set_bkg_data (0x59, 1, BlankSky5);
			set_bkg_data (0x5A, 1, BlankSky5);
			set_bkg_data (0x5B, 1, BlankSky5);
			set_bkg_data (0x5C, 1, BlankSky5);
			set_bkg_data (0x5D, 1, BlankSky5);
			set_bkg_data (0x5E, 1, BlankSky5);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_5); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_5);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_5);
			set_bkg_tiles (10, 5, 1, 1, Letter4_5);
			set_bkg_tiles (11, 5, 1, 1, Letter5_5);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_5);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_5);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_5);
			set_bkg_tiles (10, 6, 1, 1, Letter9_5);
			set_bkg_tiles (11, 6, 1, 1, Letter10_5);
			set_bkg_tiles (12, 6, 1, 1, Letter11_5);

			cutscenemode = disabled;

			if (flagpole_activated5 == 0) {
				PlayMusic(raindrops, 1);
			}
		}

		if (level5counter < 105) level5counter++;
	}

	//animate water
	if (anim_water_counter5 >= 0 && anim_water_counter5 < 10) {
		set_bkg_data (0x1A, 1, level5_water1);
		set_bkg_data (0x1B, 1, level5_water2);
		set_bkg_data (0x1C, 1, level5_water3);
	}
	else if (anim_water_counter5 >= 10 && anim_water_counter5 < 20) {
		set_bkg_data (0x1A, 1, level5_water2);
		set_bkg_data (0x1B, 1, level5_water3);
		set_bkg_data (0x1C, 1, level5_water1);
	}
	else if (anim_water_counter5 >= 20 && anim_water_counter5 < 30) {
		set_bkg_data (0x1A, 1, level5_water3);
		set_bkg_data (0x1B, 1, level5_water1);
		set_bkg_data (0x1C, 1, level5_water2);
	}
	anim_water_counter5++;
	if (anim_water_counter5 >= 30) anim_water_counter5 = 0;

	//animate rain
	// Set 1 data:    0x64, 0x65, 0x66
	// Set 2 data:    0x68, 0x69, 0x6A
	// Splash 1 data: 0x6C, 0x6D, 0x6E
	// Splash 2 data: 0x70, 0x71, 0x72
	// Variables: rainset1_pt1, anim_rain_counter5, rainblankwhite

	if (anim_rain_counter5 >= 0 && anim_rain_counter5 < 5) {
		//frame 1
		//Set 1:
		set_bkg_data (0x64, 1, rainset1_pt1);
		set_bkg_data (0x65, 1, rainblankblue);
		set_bkg_data (0x66, 1, rainblankblue);
		//Set 2:
		set_bkg_data (0x68, 1, rainblankblue);
		set_bkg_data (0x69, 1, rainblankblue);
		set_bkg_data (0x6A, 1, rainset2_pt4);
		//Splash 1:
		set_bkg_data (0x6C, 1, rainsplash1_pt1);
		set_bkg_data (0x6D, 1, rainblankwhite);
		set_bkg_data (0x6E, 1, rainblankwhite);
		//Splash 2:
		set_bkg_data (0x70, 1, rainblankwhite);
		set_bkg_data (0x71, 1, rainblankwhite);
		set_bkg_data (0x72, 1, rainsplash2_pt4);
	}
	else if (anim_rain_counter5 >= 5 && anim_rain_counter5 < 10) {
		//frame 2
		//Set 1:
		set_bkg_data (0x64, 1, rainblankblue);
		set_bkg_data (0x65, 1, rainset1_pt2);
		set_bkg_data (0x66, 1, rainblankblue);
		//Set 2:
		set_bkg_data (0x68, 1, rainblankblue);
		set_bkg_data (0x69, 1, rainblankblue);
		set_bkg_data (0x6A, 1, rainblankblue);
		//Splash 1:
		set_bkg_data (0x6C, 1, rainblankwhite);
		set_bkg_data (0x6D, 1, rainsplash1_pt2);
		set_bkg_data (0x6E, 1, rainblankwhite);
		//Splash 2:
		set_bkg_data (0x70, 1, rainblankwhite);
		set_bkg_data (0x71, 1, rainblankwhite);
		set_bkg_data (0x72, 1, rainblankwhite);
	}
	else if (anim_rain_counter5 >= 10 && anim_rain_counter5 < 15) {
		//frame 3
		//Set 1:
		set_bkg_data (0x64, 1, rainblankblue);
		set_bkg_data (0x65, 1, rainblankblue);
		set_bkg_data (0x66, 1, rainset1_pt3);
		//Set 2:
		set_bkg_data (0x68, 1, rainset2_pt1);
		set_bkg_data (0x69, 1, rainblankblue);
		set_bkg_data (0x6A, 1, rainblankblue);
		//Splash 1:
		set_bkg_data (0x6C, 1, rainblankwhite);
		set_bkg_data (0x6D, 1, rainblankwhite);
		set_bkg_data (0x6E, 1, rainsplash1_pt3);
		//Splash 2:
		set_bkg_data (0x70, 1, rainsplash2_pt1);
		set_bkg_data (0x71, 1, rainblankwhite);
		set_bkg_data (0x72, 1, rainblankwhite);
	}
	else if (anim_rain_counter5 >= 15 && anim_rain_counter5 < 20) {
		//frame 4
		//Set 1:
		set_bkg_data (0x64, 1, rainblankblue);
		set_bkg_data (0x65, 1, rainblankblue);
		set_bkg_data (0x66, 1, rainset1_pt4);
		//Set 2:
		set_bkg_data (0x68, 1, rainblankblue);
		set_bkg_data (0x69, 1, rainset2_pt2);
		set_bkg_data (0x6A, 1, rainblankblue);
		//Splash 1:
		set_bkg_data (0x6C, 1, rainblankwhite);
		set_bkg_data (0x6D, 1, rainblankwhite);
		set_bkg_data (0x6E, 1, rainsplash1_pt4);
		//Splash 2:
		set_bkg_data (0x70, 1, rainblankwhite);
		set_bkg_data (0x71, 1, rainsplash2_pt2);
		set_bkg_data (0x72, 1, rainblankwhite);
	}
	else if (anim_rain_counter5 >= 20 && anim_rain_counter5 < 25) {
		//frame 5
		//Set 1:
		set_bkg_data (0x64, 1, rainblankblue);
		set_bkg_data (0x65, 1, rainblankblue);
		set_bkg_data (0x66, 1, rainblankblue);
		//Set 2:
		set_bkg_data (0x68, 1, rainblankblue);
		set_bkg_data (0x69, 1, rainblankblue);
		set_bkg_data (0x6A, 1, rainset2_pt3);
		//Splash 1:
		set_bkg_data (0x6C, 1, rainblankwhite);
		set_bkg_data (0x6D, 1, rainblankwhite);
		set_bkg_data (0x6E, 1, rainblankwhite);
		//Splash 2:
		set_bkg_data (0x70, 1, rainblankwhite);
		set_bkg_data (0x71, 1, rainblankwhite);
		set_bkg_data (0x72, 1, rainsplash2_pt3);
	}
	anim_rain_counter5++;
	if (anim_rain_counter5 >= 25) anim_rain_counter5 = 0;

	//animate grey flagpole
	if (flagpole_activated5 == 0) {
		if (anim_flag_counter5 >= 0 && anim_flag_counter5 < 12) {
			set_bkg_data (0x21, 1, grey5_33);
			set_bkg_data (0x29, 1, grey5_41);
			set_bkg_data (0x2A, 1, grey5_41);
		}
		else if (anim_flag_counter5 >= 12 && anim_flag_counter5 < 24) {
			set_bkg_data (0x21, 1, grey5_34);
			set_bkg_data (0x29, 1, grey5_42);
			set_bkg_data (0x2A, 1, grey5_42);
		}
		else if (anim_flag_counter5 >= 24 && anim_flag_counter5 < 36) {
			set_bkg_data (0x21, 1, grey5_35);
			set_bkg_data (0x29, 1, grey5_43);
			set_bkg_data (0x2A, 1, grey5_43);
		}
		else if (anim_flag_counter5 >= 36 && anim_flag_counter5 < 48) {
			set_bkg_data (0x21, 1, grey5_36);
			set_bkg_data (0x29, 1, grey5_44);
			set_bkg_data (0x2A, 1, grey5_44);
		}
		anim_flag_counter5++;
		if (anim_flag_counter5 >= 48) anim_flag_counter5 = 0;
	}
	//animate pink flagpole
	else if (flagpole_activated5 == 1) {
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

		if (endlevel_counter5 == 10) {
			SpriteManagerAdd(SpriteStarLeft, 1948, 96);
			SpriteManagerAdd(SpriteStarRight, 1956, 96);
		}
		else if (endlevel_counter5 == 30) {
			SpriteManagerAdd(SpriteStarLeft, 1948, 80);
			SpriteManagerAdd(SpriteStarRight, 1956, 80);
		}
		else if (endlevel_counter5 == 50) {
			SpriteManagerAdd(SpriteStarLeft, 1948, 64);
			SpriteManagerAdd(SpriteStarRight, 1956, 64);
		}
		else if (endlevel_counter5 >= 100) {
			//endlevel_counter5 = 0;
			//cutscenewalkleft = false;
			//cutscenewalkright = false;
			//cutscenemode = disabled;

			SetState(StateOverworld1);
		}

		if (endlevel_counter5 < 250) endlevel_counter5++;

		//spawn some stars
		/*
		if (flagpole_stars5 < 1) {
			SpriteManagerAdd(SpriteStarLeft, spr_nutmeg->x, spr_nutmeg->y);
			SpriteManagerAdd(SpriteStarRight, spr_nutmeg->x, spr_nutmeg->y);

			//SpriteManagerAdd(SpriteStarLeft, 244, 10);
			//SpriteManagerAdd(SpriteStarRight, 244, 10);
		}
		else if (flagpole_stars5 >= 5 && flagpole_stars5 < 10) {
			SpriteManagerAdd(SpriteStarLeft, 244, 10);
			SpriteManagerAdd(SpriteStarRight, 244, 10);
		}
		else if (flagpole_stars5 >= 10 && flagpole_stars5 < 20) {
			SpriteManagerAdd(SpriteStarLeft, 244, 7);
			SpriteManagerAdd(SpriteStarRight, 244, 7);
		}
		*/

		//change flagpole color palette to pink
		//set_bkg_palette (1, 1, pal_pink5);
		SetPalette(BG_PALETTE, 1, 1, pal_pink5, _current_bank);

		if (anim_flag_counter5 >= 0 && anim_flag_counter5 < 5) {
			set_bkg_data (0x21, 1, pink5_37);
			set_bkg_data (0x29, 1, pink5_45);
			set_bkg_data (0x2A, 1, pink5_45);
		}
		else if (anim_flag_counter5 >= 5 && anim_flag_counter5 < 10) {
			set_bkg_data (0x21, 1, pink5_38);
			set_bkg_data (0x29, 1, pink5_46);
			set_bkg_data (0x2A, 1, pink5_46);
		}
		else if (anim_flag_counter5 >= 10 && anim_flag_counter5 < 15) {
			set_bkg_data (0x21, 1, pink5_39);
			set_bkg_data (0x29, 1, pink5_47);
			set_bkg_data (0x2A, 1, pink5_47);
		}
		else if (anim_flag_counter5 >= 15 && anim_flag_counter5 < 20) {
			set_bkg_data (0x21, 1, pink5_40);
			set_bkg_data (0x29, 1, pink5_48);
			set_bkg_data (0x2A, 1, pink5_48);
		}
		anim_flag_counter5++;
		if (anim_flag_counter5 >= 20) anim_flag_counter5 = 0;

		if (flagpole_stars5 < 20) flagpole_stars5++;
	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && flagpole_activated5 == 0) {
		flagpole_activated5 = 1;
		levelbeat = true;
		endlevel_counter5 = 0;
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
	
	/*
	if (lightningstrikecounter < 205) lightningstrikecounter++;

	if (lightningstrikecounter == 200) {
		SpriteManagerAdd(EnemyLightning, 13*8, 0*8);
	}
	*/

	// 0-63:
	if (spr_nutmeg->x > 0 && spr_nutmeg->x <= 250 && nut_region <= 0) {
		//SpriteManagerAdd(EnemyLightning, 13*8, 0*8);
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_nutmeg->x > 250 && spr_nutmeg->x <= 500 && nut_region <= 1) {
    	nut_region = 2;
	}
	// Up to 125:
	else if (spr_nutmeg->x > 500 && spr_nutmeg->x <= 750 && nut_region <= 2) {
	    nut_region = 3;
	}
	// Up to 156:
	else if (spr_nutmeg->x > 750 && spr_nutmeg->x <= 1000 && nut_region <= 3) {
	    nut_region = 4;
	}
	// Up to 188:
	else if (spr_nutmeg->x > 1000 && spr_nutmeg->x <= 1250 && nut_region <= 4) {
	    nut_region = 5;
	}
	// Up to 219:
	else if (spr_nutmeg->x > 1250 && spr_nutmeg->x <= 1500 && nut_region <= 5) {
		nut_region = 6;
	}
	// Up to 250:
	else if (spr_nutmeg->x > 1500 && spr_nutmeg->x <= 1750 && nut_region <= 6) {
	    nut_region = 7;
	}
	else if (spr_nutmeg->x > 1750 && spr_nutmeg->x <= 2000 && nut_region <= 7) {
	    nut_region = 8;
	}
}