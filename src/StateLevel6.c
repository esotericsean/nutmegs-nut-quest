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

IMPORT_MAP (level6map);
IMPORT_MAP (hud);

UINT16 level6counter = 0;

UINT8 level6cameracount = 0;

UINT8 anim_water_counter6 = 0;
UINT8 anim_flag_counter6 = 0;
UINT8 flagpole_activated6 = 0;
UINT8 flagpole_stars6 = 0;
UINT8 endlevel_counter6 = 0;

//pink color palette
const UWORD pal_pink6[] = { RGB(31, 31, 31), RGB(19, 26, 30), RGB(28, 19, 30), RGB(0,  0,  0) };

// BACKGROUND TILE COLOR PALETTES

//grass color palette - ORIGINAL
const UWORD pal_grass_original6[]    = { RGB(14, 30, 14), RGB( 1, 26,  0), RGB(19, 14, 0), RGB(0, 0, 0) };
//grass color palette - LIGHTER
const UWORD pal_grass_lighter6[]     = { RGB(20, 30, 22), RGB( 6, 29,  0), RGB(22, 18, 0), RGB(5, 5, 5) };
//grass color palette - EVEN LIGHTER
const UWORD pal_grass_evenlighter6[] = { RGB(27, 30, 28), RGB(15, 31, 11), RGB(28, 23, 0), RGB(12, 12, 12) };
//grass color palette - LIGHTEST!!!
const UWORD pal_grass_lightest6[]    = { RGB(31, 31, 31), RGB(29, 30, 28), RGB(30, 29, 26), RGB(24, 24, 24) };

//wood color palette - ORIGINAL
const UWORD pal_wood_original6[]    = { RGB(31, 31, 31), RGB(28, 24, 18), RGB(19, 14, 0), RGB(0, 0, 0) };
//wood color palette - LIGHTER
const UWORD pal_wood_lighter6[]     = { RGB(31, 31, 31), RGB(30, 26, 20), RGB(22, 18, 0), RGB(5, 5, 5) };
//wood color palette - EVEN LIGHTER
const UWORD pal_wood_evenlighter6[] = { RGB(31, 31, 31), RGB(30, 27, 24), RGB(28, 23, 0), RGB(12, 12, 12) };
//wood color palette - LIGHTEST!!!
const UWORD pal_wood_lightest6[]    = { RGB(31, 31, 31), RGB(30, 29, 28), RGB(30, 29, 26), RGB(24, 24, 24) };

// SPRITE COLOR PALETTES

//nutmeg color palette - ORIGINAL
const UWORD pal_nutmeg_original6[]    = { RGB(31, 31, 31), RGB(31, 27, 23), RGB(31, 17, 6), RGB(0, 0, 0) };
//nutmeg color palette - LIGHTER
const UWORD pal_nutmeg_lighter6[]     = { RGB(31, 31, 31), RGB(31, 28, 26), RGB(31, 20, 9), RGB(5, 5, 5) };
//nutmeg color palette - EVEN LIGHTER
const UWORD pal_nutmeg_evenlighter6[] = { RGB(31, 31, 31), RGB(31, 30, 28), RGB(31, 24, 13), RGB(12, 12, 12) };
//nutmeg color palette - LIGHTEST!!!
const UWORD pal_nutmeg_lightest6[]    = { RGB(31, 31, 31), RGB(31, 31, 30), RGB(30, 29, 28), RGB(22, 22, 22) };

//acorn color palette - ORIGINAL
const UWORD pal_acorn_original6[]	  = { RGB(31, 31, 31), RGB(30, 23, 17), RGB(20,  9,  0), RGB(10,  5,  1) };
//acorn color palette - LIGHTER
const UWORD pal_acorn_lighter6[]	  = { RGB(31, 31, 31), RGB(30, 25, 20), RGB(23, 12,  2), RGB(16,  7,  2) };
//acorn color palette - EVEN LIGHTER
const UWORD pal_acorn_evenlighter6[]  = { RGB(31, 31, 31), RGB(30, 28, 24), RGB(26, 16,  3), RGB(21, 11,  4) };
//acorn color palette - LIGHTEST!!!
const UWORD pal_acorn_lightest6[]	  = { RGB(31, 31, 31), RGB(30, 29, 25), RGB(30, 25, 17), RGB(29, 19, 10) };

//birdy color palette - ORIGINAL
const UWORD pal_birdy_original6[]	  = { RGB(31, 31, 31), RGB(31, 19, 2),  RGB(0,  16, 31), RGB(0, 0, 0) };
//birdy color palette - LIGHTER
const UWORD pal_birdy_lighter6[]	  = { RGB(31, 31, 31), RGB(31, 24, 5),  RGB(1,  21, 31), RGB(5, 5, 5) };
//birdy color palette - EVEN LIGHTER
const UWORD pal_birdy_evenlighter6[]  = { RGB(31, 31, 31), RGB(31, 27, 20), RGB(4,  25, 31), RGB(12, 12, 12) };
//birdy color palette - LIGHTEST!!!
const UWORD pal_birdy_lightest6[]	  = { RGB(31, 31, 31), RGB(31, 29, 25), RGB(12, 28, 31), RGB(22, 22, 22) };

//balloon color palette - ORIGINAL
const UWORD pal_balloon_original6[]	  = { RGB(31, 31, 31), RGB(30, 27, 26), RGB(31, 7, 5), RGB(0, 0, 0) };
//balloon color palette - LIGHTER
const UWORD pal_balloon_lighter6[]	  = { RGB(31, 31, 31), RGB(30, 28, 27), RGB(31, 11, 9), RGB(5, 5, 5) };
//balloon color palette - EVEN LIGHTER
const UWORD pal_balloon_evenlighter6[]	= { RGB(31, 31, 31), RGB(30, 30, 28), RGB(31, 17, 14), RGB(12, 12, 12) };
//balloon color palette - LIGHTEST!!!
const UWORD pal_balloon_lightest6[]	  = { RGB(31, 31, 31), RGB(30, 30, 28), RGB(31, 22, 20), RGB(20, 20, 20) };

//yellow color palette - ORIGINAL
const UWORD pal_yellow_original6[]	  = { RGB(31, 31, 31), RGB(28, 27, 9), RGB(22, 21, 5), RGB(0, 0, 0) };
//yellow color palette - LIGHTER
const UWORD pal_yellow_lighter6[]	  = { RGB(31, 31, 31), RGB(29, 28, 17), RGB(25, 24, 11), RGB(5, 5, 5) };
//yellow color palette - EVEN LIGHTER
const UWORD pal_yellow_evenlighter6[] = { RGB(31, 31, 31), RGB(30, 29, 21), RGB(26, 25, 16), RGB(12, 12, 12) };
//yellow color palette - LIGHTEST!!!
const UWORD pal_yellow_lightest6[]    = { RGB(31, 31, 31), RGB(30, 29, 24), RGB(27, 26, 20), RGB(22, 22, 22) };

//puff white palette change to light grey so you can see it throughout the level
//const UWORD pal_puff_original6[]	  = { RGB(31, 31, 31), RGB(31, 31, 31), RGB(31, 31, 31), RGB(31, 31, 31) };
const UWORD pal_puff_fixed6[]	      = { RGB(20, 20, 20), RGB(20, 20, 20), RGB(20, 20, 20), RGB(20, 20, 20) };

const UINT8 collision_tiles_level6[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
const UINT8 collision_tiles_down_level6[] = {29,30,31,32,0};

DECLARE_MUSIC(quickstart);
DECLARE_MUSIC(ruffles);
DECLARE_MUSIC(flagpole);
DECLARE_MUSIC(quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_camera;

//water tiles are stored in 1A, 1B, and 1C
//in GBTD, water is 26, 27, 28
const unsigned char level6_water1[] = {
	0x00,0x08,0x08,0x3c,0x3c,0xff,0xff,0xfb,
	0xff,0xdf,0xf7,0xff,0x7f,0xff,0xfd,0xff
};
const unsigned char level6_water2[] = {
	0x00,0x20,0x20,0xf3,0xf3,0xff,0xff,0xff,
	0xdf,0xff,0xff,0xf7,0x7f,0xff,0xfd,0xff
};
const unsigned char level6_water3[] = {
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
const unsigned char grey6_33[] = {
	0xff,0x3c,0xc3,0x46,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};
const unsigned char grey6_34[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};
const unsigned char grey6_35[] = {
	0xff,0x3c,0xc3,0x7a,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};
const unsigned char grey6_36[] = {
	0xff,0x3c,0xc3,0x42,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink top
const unsigned char pink6_37[] = {
	0xff,0x3c,0xc3,0x42,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};
const unsigned char pink6_38[] = {
	0xff,0x3c,0xc3,0x5e,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};
const unsigned char pink6_39[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};
const unsigned char pink6_40[] = {
	0xff,0x3c,0xc3,0x62,0x81,0x81,0x81,0x81,
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff
};

//grey mid/bottom
const unsigned char grey6_41[] = {
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};
const unsigned char grey6_42[] = {
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};
const unsigned char grey6_43[] = {
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};
const unsigned char grey6_44[] = {
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink mid/bottom
const unsigned char pink6_45[] = {
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};
const unsigned char pink6_46[] = {
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};
const unsigned char pink6_47[] = {
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};
const unsigned char pink6_48[] = {
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
const unsigned char UpperL6[] = {
	0xff,0x00,0xff,0x20,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerE6[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x24,0xff,0x38,0xff,0x20,0xff,0x1c
};
const unsigned char LowerV6[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x44,
	0xff,0x44,0xff,0x28,0xff,0x28,0xff,0x10
};
const unsigned char LowerL6[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x38
};
const unsigned char UpperS6[] = {
	0xff,0x00,0xff,0x18,0xff,0x24,0xff,0x20,
	0xff,0x18,0xff,0x04,0xff,0x24,0xff,0x18
};
const unsigned char LowerT6[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x78,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerA6[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x04,0xff,0x1c,0xff,0x24,0xff,0x1a
};
const unsigned char LowerR6[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x20
};
const unsigned char Exclam6[] = {
	0xff,0x00,0xff,0x10,0xff,0x10,0xff,0x10,
	0xff,0x10,0xff,0x10,0xff,0x00,0xff,0x10
};
const unsigned char BlankSky6[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00
};

const unsigned char Letter1_6[]  = { 0x54 }; //54-5E
const unsigned char Letter2_6[]  = { 0x55 };
const unsigned char Letter3_6[]  = { 0x56 };
const unsigned char Letter4_6[]  = { 0x57 };
const unsigned char Letter5_6[]  = { 0x58 };
const unsigned char Letter6_6[]  = { 0x59 };
const unsigned char Letter7_6[]  = { 0x5A };
const unsigned char Letter8_6[]  = { 0x5B };
const unsigned char Letter9_6[]  = { 0x5C };
const unsigned char Letter10_6[] = { 0x5D };
const unsigned char Letter11_6[] = { 0x5E };

//timer counter
UINT16 timerlevel6;
UINT8 timerclock6;

void UpdateHud6() {
	//health system DISPLAY
	//health first number:
	if (nutmeg_death == false) {
		switch (nutmeglives - (nutmeglives % 10)) {
			case 0:  UPDATE_HUD_TILE (3, 0, 6);  break;
			case 10: UPDATE_HUD_TILE (3, 0, 7);  break;
			case 20: UPDATE_HUD_TILE (3, 0, 8);  break;
			case 30: UPDATE_HUD_TILE (3, 0, 9);  break;
			case 40: UPDATE_HUD_TILE (3, 0, 10); break;
			case 50: UPDATE_HUD_TILE (3, 0, 11); break;
			case 60: UPDATE_HUD_TILE (3, 0, 12); break;
			case 70: UPDATE_HUD_TILE (3, 0, 13); break;
			case 80: UPDATE_HUD_TILE (3, 0, 14); break;
			case 90: UPDATE_HUD_TILE (3, 0, 15); break;
		}
		//health second number:
		switch (nutmeglives % 10) {
			case 0: UPDATE_HUD_TILE (4, 0, 6);  break;
			case 1: UPDATE_HUD_TILE (4, 0, 7);  break;
			case 2: UPDATE_HUD_TILE (4, 0, 8);  break;
			case 3: UPDATE_HUD_TILE (4, 0, 9);  break;
			case 4: UPDATE_HUD_TILE (4, 0, 10); break;
			case 5: UPDATE_HUD_TILE (4, 0, 11); break;
			case 6: UPDATE_HUD_TILE (4, 0, 12); break;
			case 7: UPDATE_HUD_TILE (4, 0, 13); break;
			case 8: UPDATE_HUD_TILE (4, 0, 14); break;
			case 9: UPDATE_HUD_TILE (4, 0, 15); break;
		}
	}

	//acorns:
	//acorns first number:
	switch (acorncounter - (acorncounter % 10)) {
		case 0:  UPDATE_HUD_TILE (17, 0, 6);  break;
		case 10: UPDATE_HUD_TILE (17, 0, 7);  break;
		case 20: UPDATE_HUD_TILE (17, 0, 8);  break;
		case 30: UPDATE_HUD_TILE (17, 0, 9);  break;
		case 40: UPDATE_HUD_TILE (17, 0, 10); break;
		case 50: UPDATE_HUD_TILE (17, 0, 11); break;
		case 60: UPDATE_HUD_TILE (17, 0, 12); break;
		case 70: UPDATE_HUD_TILE (17, 0, 13); break;
		case 80: UPDATE_HUD_TILE (17, 0, 14); break;
		case 90: UPDATE_HUD_TILE (17, 0, 15); break;
	}
	//acorns second number:
	switch (acorncounter % 10) {
		case 0: UPDATE_HUD_TILE (18, 0, 6);  break;
		case 1: UPDATE_HUD_TILE (18, 0, 7);  break;
		case 2: UPDATE_HUD_TILE (18, 0, 8);  break;
		case 3: UPDATE_HUD_TILE (18, 0, 9);  break;
		case 4: UPDATE_HUD_TILE (18, 0, 10); break;
		case 5: UPDATE_HUD_TILE (18, 0, 11); break;
		case 6: UPDATE_HUD_TILE (18, 0, 12); break;
		case 7: UPDATE_HUD_TILE (18, 0, 13); break;
		case 8: UPDATE_HUD_TILE (18, 0, 14); break;
		case 9: UPDATE_HUD_TILE (18, 0, 15); break;
	}

	if (timerclock6 <= 25 && cutscenemode == disabled) timerclock6 ++; //25 seems good

	if (timerclock6 == 25) {
		timerclock6 = 0;
		timerlevel6--;
	}

	//timer:
	//timer 100s digit:
	if (timerlevel6 == 300) UPDATE_HUD_TILE (10, 0, 9);
	if (timerlevel6 < 300 && timerlevel6 >= 200) UPDATE_HUD_TILE (10, 0, 8);
	if (timerlevel6 < 200 && timerlevel6 >= 100) UPDATE_HUD_TILE (10, 0, 7);
	if (timerlevel6 < 100) UPDATE_HUD_TILE (10, 0, 6);
	//timer 10s digit:
	if (timerlevel6 < 300 && timerlevel6 >= 200) {
		switch (timerlevel6 - 200 - (timerlevel6 % 10)) {
			case 0:  UPDATE_HUD_TILE (11, 0, 6);  break;
			case 10: UPDATE_HUD_TILE (11, 0, 7);  break;
			case 20: UPDATE_HUD_TILE (11, 0, 8);  break;
			case 30: UPDATE_HUD_TILE (11, 0, 9);  break;
			case 40: UPDATE_HUD_TILE (11, 0, 10); break;
			case 50: UPDATE_HUD_TILE (11, 0, 11); break;
			case 60: UPDATE_HUD_TILE (11, 0, 12); break;
			case 70: UPDATE_HUD_TILE (11, 0, 13); break;
			case 80: UPDATE_HUD_TILE (11, 0, 14); break;
			case 90: UPDATE_HUD_TILE (11, 0, 15); break;
		}
	}
	else if (timerlevel6 < 200 && timerlevel6 >= 100) {
		switch (timerlevel6 - 100 - (timerlevel6 % 10)) {
			case 0:  UPDATE_HUD_TILE (11, 0, 6);  break;
			case 10: UPDATE_HUD_TILE (11, 0, 7);  break;
			case 20: UPDATE_HUD_TILE (11, 0, 8);  break;
			case 30: UPDATE_HUD_TILE (11, 0, 9);  break;
			case 40: UPDATE_HUD_TILE (11, 0, 10); break;
			case 50: UPDATE_HUD_TILE (11, 0, 11); break;
			case 60: UPDATE_HUD_TILE (11, 0, 12); break;
			case 70: UPDATE_HUD_TILE (11, 0, 13); break;
			case 80: UPDATE_HUD_TILE (11, 0, 14); break;
			case 90: UPDATE_HUD_TILE (11, 0, 15); break;
		}
	}
	switch (timerlevel6 - (timerlevel6 % 10)) {
		case 0:  UPDATE_HUD_TILE (11, 0, 6);  break;
		case 10: UPDATE_HUD_TILE (11, 0, 7);  break;
		case 20: UPDATE_HUD_TILE (11, 0, 8);  break;
		case 30: UPDATE_HUD_TILE (11, 0, 9);  break;
		case 40: UPDATE_HUD_TILE (11, 0, 10); break;
		case 50: UPDATE_HUD_TILE (11, 0, 11); break;
		case 60: UPDATE_HUD_TILE (11, 0, 12); break;
		case 70: UPDATE_HUD_TILE (11, 0, 13); break;
		case 80: UPDATE_HUD_TILE (11, 0, 14); break;
		case 90: UPDATE_HUD_TILE (11, 0, 15); break;
	}
	//timer 1s digit:
	switch (timerlevel6 % 10) {
		case 0: UPDATE_HUD_TILE (12, 0, 6);  break;
		case 1: UPDATE_HUD_TILE (12, 0, 7);  break;
		case 2: UPDATE_HUD_TILE (12, 0, 8);  break;
		case 3: UPDATE_HUD_TILE (12, 0, 9);  break;
		case 4: UPDATE_HUD_TILE (12, 0, 10); break;
		case 5: UPDATE_HUD_TILE (12, 0, 11); break;
		case 6: UPDATE_HUD_TILE (12, 0, 12); break;
		case 7: UPDATE_HUD_TILE (12, 0, 13); break;
		case 8: UPDATE_HUD_TILE (12, 0, 14); break;
		case 9: UPDATE_HUD_TILE (12, 0, 15); break;
	}
}

void Start_StateLevel6() {
	level6counter = 0;
	timerlevel6 = 300;
	timerclock6 = 0;
	levelorientation = horizontal;
	SPRITES_8x16;

	nut_region = 0;
	pitdeathactive = true;

	deathmusicplayed = false;

	PlayMusic(quickstart, 1);

	//testing:
	health = full;
	lostbow = false;
	
	//if health is full, add the bow
	if (health == full) { SpriteManagerAdd(SpriteNutmegBow, 4, 49); }
	scroll_target = spr_camera = SpriteManagerAdd(SpriteCamera, 80, 12); //49
	spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 4, 49);

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level6map), &level6map, collision_tiles_level6, collision_tiles_down_level6);
	INIT_HUD(hud);

	cutscenemode = enabled;
	isAcornMoving = true;
	flagpole_activated6 = 0;
	endlevel_counter6 = 0;

	level6cameracount = 0;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel6() {
	UpdateHud6();

	if (timerlevel6 <= 0) nutmeg_death = true;

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
		if (level6counter == 0) {
			cutscenewalkright = true;
		}
		else if (level6counter >= 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		if (level6counter >= 10 && level6counter < 40) {
			set_bkg_data (0x54, 1, UpperL6);
			set_bkg_data (0x55, 1, LowerE6);
			set_bkg_data (0x56, 1, LowerV6);
			set_bkg_data (0x57, 1, LowerE6);
			set_bkg_data (0x58, 1, LowerL6);
			set_bkg_data (0x59, 1, UpperS6);
			set_bkg_data (0x5A, 1, LowerT6);
			set_bkg_data (0x5B, 1, LowerA6);
			set_bkg_data (0x5C, 1, LowerR6);
			set_bkg_data (0x5D, 1, LowerT6);
			set_bkg_data (0x5E, 1, Exclam6);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_6); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_6);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_6);
			set_bkg_tiles (10, 5, 1, 1, Letter4_6);
			set_bkg_tiles (11, 5, 1, 1, Letter5_6);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_6);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_6);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_6);
			set_bkg_tiles (10, 6, 1, 1, Letter9_6);
			set_bkg_tiles (11, 6, 1, 1, Letter10_6);
			set_bkg_tiles (12, 6, 1, 1, Letter11_6);
		}
		else if (level6counter >= 40 && level6counter < 70) {
			set_bkg_data (0x54, 1, BlankSky6);
			set_bkg_data (0x55, 1, BlankSky6);
			set_bkg_data (0x56, 1, BlankSky6);
			set_bkg_data (0x57, 1, BlankSky6);
			set_bkg_data (0x58, 1, BlankSky6);
			set_bkg_data (0x59, 1, BlankSky6);
			set_bkg_data (0x5A, 1, BlankSky6);
			set_bkg_data (0x5B, 1, BlankSky6);
			set_bkg_data (0x5C, 1, BlankSky6);
			set_bkg_data (0x5D, 1, BlankSky6);
			set_bkg_data (0x5E, 1, BlankSky6);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_6); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_6);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_6);
			set_bkg_tiles (10, 5, 1, 1, Letter4_6);
			set_bkg_tiles (11, 5, 1, 1, Letter5_6);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_6);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_6);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_6);
			set_bkg_tiles (10, 6, 1, 1, Letter9_6);
			set_bkg_tiles (11, 6, 1, 1, Letter10_6);
			set_bkg_tiles (12, 6, 1, 1, Letter11_6);
		}
		else if (level6counter >= 70 && level6counter < 100) {
			set_bkg_data (0x54, 1, UpperL6);
			set_bkg_data (0x55, 1, LowerE6);
			set_bkg_data (0x56, 1, LowerV6);
			set_bkg_data (0x57, 1, LowerE6);
			set_bkg_data (0x58, 1, LowerL6);
			set_bkg_data (0x59, 1, UpperS6);
			set_bkg_data (0x5A, 1, LowerT6);
			set_bkg_data (0x5B, 1, LowerA6);
			set_bkg_data (0x5C, 1, LowerR6);
			set_bkg_data (0x5D, 1, LowerT6);
			set_bkg_data (0x5E, 1, Exclam6);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_6); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_6);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_6);
			set_bkg_tiles (10, 5, 1, 1, Letter4_6);
			set_bkg_tiles (11, 5, 1, 1, Letter5_6);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_6);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_6);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_6);
			set_bkg_tiles (10, 6, 1, 1, Letter9_6);
			set_bkg_tiles (11, 6, 1, 1, Letter10_6);
			set_bkg_tiles (12, 6, 1, 1, Letter11_6);
		}
		else if (level6counter >= 100 && level6counter < 101) {
			set_bkg_data (0x54, 1, BlankSky6);
			set_bkg_data (0x55, 1, BlankSky6);
			set_bkg_data (0x56, 1, BlankSky6);
			set_bkg_data (0x57, 1, BlankSky6);
			set_bkg_data (0x58, 1, BlankSky6);
			set_bkg_data (0x59, 1, BlankSky6);
			set_bkg_data (0x5A, 1, BlankSky6);
			set_bkg_data (0x5B, 1, BlankSky6);
			set_bkg_data (0x5C, 1, BlankSky6);
			set_bkg_data (0x5D, 1, BlankSky6);
			set_bkg_data (0x5E, 1, BlankSky6);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_6); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_6);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_6);
			set_bkg_tiles (10, 5, 1, 1, Letter4_6);
			set_bkg_tiles (11, 5, 1, 1, Letter5_6);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_6);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_6);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_6);
			set_bkg_tiles (10, 6, 1, 1, Letter9_6);
			set_bkg_tiles (11, 6, 1, 1, Letter10_6);
			set_bkg_tiles (12, 6, 1, 1, Letter11_6);

			cutscenemode = disabled;

			if (flagpole_activated6 == 0) {
				PlayMusic(ruffles, 1);
			}
		}

		if (level6counter < 105) level6counter++;
	}

	if (cutscenemode == disabled) {
		level6cameracount++;
		if (level6cameracount > 2) level6cameracount = 0;

		if (level6cameracount == 2) {
			//TranslateSprite (spr_camera, 1, 0);
			spr_camera->x++;
		}
	}

	//tile 237 stop checking
	if (spr_nutmeg->x < 237*8) {
		if (spr_nutmeg->x < spr_camera->x - 64) {
			spr_nutmeg->x = spr_camera->x - 64;
		}
		if (spr_nutmeg->x > spr_camera->x + 64) {
			spr_nutmeg->x = spr_camera->x + 64;
		}
	}

	//animate grey flagpole
	if (flagpole_activated6 == 0) {
		if (anim_flag_counter6 >= 0 && anim_flag_counter6 < 12) {
			set_bkg_data (0x21, 1, grey6_33);
			set_bkg_data (0x29, 1, grey6_41);
			set_bkg_data (0x2A, 1, grey6_41);
		}
		else if (anim_flag_counter6 >= 12 && anim_flag_counter6 < 24) {
			set_bkg_data (0x21, 1, grey6_34);
			set_bkg_data (0x29, 1, grey6_42);
			set_bkg_data (0x2A, 1, grey6_42);
		}
		else if (anim_flag_counter6 >= 24 && anim_flag_counter6 < 36) {
			set_bkg_data (0x21, 1, grey6_35);
			set_bkg_data (0x29, 1, grey6_43);
			set_bkg_data (0x2A, 1, grey6_43);
		}
		else if (anim_flag_counter6 >= 36 && anim_flag_counter6 < 48) {
			set_bkg_data (0x21, 1, grey6_36);
			set_bkg_data (0x29, 1, grey6_44);
			set_bkg_data (0x2A, 1, grey6_44);
		}
		anim_flag_counter6++;
		if (anim_flag_counter6 >= 48) anim_flag_counter6 = 0;
	}
	//animate pink flagpole
	else if (flagpole_activated6 == 1) {
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

		if (endlevel_counter6 == 10) {
			SpriteManagerAdd(SpriteStarLeft, 1948, 96);
			SpriteManagerAdd(SpriteStarRight, 1956, 96);
		}
		else if (endlevel_counter6 == 30) {
			SpriteManagerAdd(SpriteStarLeft, 1948, 80);
			SpriteManagerAdd(SpriteStarRight, 1956, 80);
		}
		else if (endlevel_counter6 == 50) {
			SpriteManagerAdd(SpriteStarLeft, 1948, 64);
			SpriteManagerAdd(SpriteStarRight, 1956, 64);
		}
		else if (endlevel_counter6 >= 100) {
			SetState(StateOverworld1);
		}

		if (endlevel_counter6 < 250) endlevel_counter6++;

		//change flagpole color palette to pink
		//set_bkg_palette (1, 1, pal_pink6);
		SetPalette(BG_PALETTE, 1, 1, pal_pink6, _current_bank);

		if (anim_flag_counter6 >= 0 && anim_flag_counter6 < 5) {
			set_bkg_data (0x21, 1, pink6_37);
			set_bkg_data (0x29, 1, pink6_45);
			set_bkg_data (0x2A, 1, pink6_45);
		}
		else if (anim_flag_counter6 >= 5 && anim_flag_counter6 < 10) {
			set_bkg_data (0x21, 1, pink6_38);
			set_bkg_data (0x29, 1, pink6_46);
			set_bkg_data (0x2A, 1, pink6_46);
		}
		else if (anim_flag_counter6 >= 10 && anim_flag_counter6 < 15) {
			set_bkg_data (0x21, 1, pink6_39);
			set_bkg_data (0x29, 1, pink6_47);
			set_bkg_data (0x2A, 1, pink6_47);
		}
		else if (anim_flag_counter6 >= 15 && anim_flag_counter6 < 20) {
			set_bkg_data (0x21, 1, pink6_40);
			set_bkg_data (0x29, 1, pink6_48);
			set_bkg_data (0x2A, 1, pink6_48);
		}
		anim_flag_counter6++;
		if (anim_flag_counter6 >= 20) anim_flag_counter6 = 0;

		if (flagpole_stars6 < 20) flagpole_stars6++;
	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && flagpole_activated6 == 0 && nutmeg_death == false) {
		flagpole_activated6 = 1;
		levelbeat = true;
		endlevel_counter6 = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
		__critical { PlayMusic(flagpole, 1); }
		//distance = 0;
		//SetState(StateOverworld1);
	}

	//switched puff to Nutmeg's palette, so leave it alone for this level
	/*if (spr_nutmeg->x > 13*8) {
		SetPalette(SPRITES_PALETTE, 3, 1, pal_puff_fixed6, _current_bank);
	}*/

	// Sprites:
	// 0 = yellow (bow, butterfly, star)
	// 1 = orange (nutmeg, puff)
	// 2 = red (balloon)
	// 3 = brown (acorn)
	// 4 = blue (bird)

	// set palettes while going through cloud
	// grass is 0, wood is 5, nutmeg is sprite 0
	if (spr_camera->x > 72*8 && spr_camera->x < 73*8) {
		SetPalette(BG_PALETTE, 0, 1, pal_grass_lighter6, _current_bank);
		SetPalette(BG_PALETTE, 5, 1, pal_wood_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 1, 1, pal_nutmeg_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 2, 1, pal_balloon_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 3, 1, pal_acorn_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 4, 1, pal_birdy_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 0, 1, pal_yellow_lighter6, _current_bank);
	}
	else if (spr_camera->x > 74*8 && spr_camera->x < 75*8) {
		SetPalette(BG_PALETTE, 0, 1, pal_grass_evenlighter6, _current_bank);
		SetPalette(BG_PALETTE, 5, 1, pal_wood_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 1, 1, pal_nutmeg_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 2, 1, pal_balloon_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 3, 1, pal_acorn_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 4, 1, pal_birdy_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 0, 1, pal_yellow_evenlighter6, _current_bank);
	}
	else if (spr_camera->x > 76*8 && spr_camera->x < 77*8) {
		SetPalette(BG_PALETTE, 0, 1, pal_grass_lightest6, _current_bank);
		SetPalette(BG_PALETTE, 5, 1, pal_wood_lightest6, _current_bank);
		SetPalette(SPRITES_PALETTE, 1, 1, pal_nutmeg_lightest6, _current_bank);
		SetPalette(SPRITES_PALETTE, 2, 1, pal_balloon_lightest6, _current_bank);
		SetPalette(SPRITES_PALETTE, 3, 1, pal_acorn_lightest6, _current_bank);
		SetPalette(SPRITES_PALETTE, 4, 1, pal_birdy_lightest6, _current_bank);
		SetPalette(SPRITES_PALETTE, 0, 1, pal_yellow_lightest6, _current_bank);
	}
	else if (spr_camera->x > 210*8 && spr_camera->x < 211*8) {
		SetPalette(BG_PALETTE, 0, 1, pal_grass_evenlighter6, _current_bank);
		SetPalette(BG_PALETTE, 5, 1, pal_wood_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 1, 1, pal_nutmeg_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 2, 1, pal_balloon_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 3, 1, pal_acorn_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 4, 1, pal_birdy_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 0, 1, pal_yellow_evenlighter6, _current_bank);
	}
	else if (spr_camera->x > 212*8 && spr_camera->x < 213*8) {
		SetPalette(BG_PALETTE, 0, 1, pal_grass_lighter6, _current_bank);
		SetPalette(BG_PALETTE, 5, 1, pal_wood_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 1, 1, pal_nutmeg_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 2, 1, pal_balloon_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 3, 1, pal_acorn_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 4, 1, pal_birdy_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 0, 1, pal_yellow_lighter6, _current_bank);
	}
	else if (spr_camera->x > 214*8 && spr_camera->x < 215*8) {
		SetPalette(BG_PALETTE, 0, 1, pal_grass_original6, _current_bank);
		SetPalette(BG_PALETTE, 5, 1, pal_wood_original6, _current_bank);
		SetPalette(SPRITES_PALETTE, 1, 1, pal_nutmeg_original6, _current_bank);
		SetPalette(SPRITES_PALETTE, 2, 1, pal_balloon_original6, _current_bank);
		SetPalette(SPRITES_PALETTE, 3, 1, pal_acorn_original6, _current_bank);
		SetPalette(SPRITES_PALETTE, 4, 1, pal_birdy_original6, _current_bank);
		SetPalette(SPRITES_PALETTE, 0, 1, pal_yellow_original6, _current_bank);
	}

	// 0-63:
	if (spr_camera->x > 0 && spr_camera->x <= 250 && nut_region <= 0) {
		SpriteManagerAdd(SpriteBalloon, 7*8, 7*8);
		SpriteManagerAdd(SpriteBalloon, 13*8-2, 15*8);
		SpriteManagerAdd(SpritePuffLeft, 0*8, 13*8);
		SpriteManagerAdd(SpriteAcorn, 34*8, 12*8);
		SpriteManagerAdd(SpriteAcorn, 14*8, 10*8);
		SpriteManagerAdd(EnemyBirdy, 17*8, 10*8);
		SpriteManagerAdd(SpriteAcorn, 24*8, 10*8);
		SpriteManagerAdd(SpriteAcorn, 27*8, 10*8);
		SpriteManagerAdd(EnemyButterfly, 33*8, 7*8);
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_camera->x > 250 && spr_camera->x <= 500 && nut_region <= 1) {
		SpriteManagerAdd(SpriteAcorn, 52*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 60*8, 2*8);
		SpriteManagerAdd(SpriteAcorn, 63*8, 4*8);
		SpriteManagerAdd(SpriteAcorn, 66*8, 6*8);
		SpriteManagerAdd(SpriteBalloon, 71*8, 10*8);
    	nut_region = 2;
	}
	// Up to 125:
	else if (spr_camera->x > 500 && spr_camera->x <= 750 && nut_region <= 2) {
		SpriteManagerAdd(SpriteAcorn, 79*8, 3*8);
		SpriteManagerAdd(SpriteAcorn, 83*8, 8*8);
		SpriteManagerAdd(EnemyButterfly, 82*8, 8*8);
		SpriteManagerAdd(SpriteBalloon, 89*8, 14*8);
		SpriteManagerAdd(EnemyBirdy, 101*8, 5*8);
	    nut_region = 3;
	}
	// Up to 156:
	else if (spr_camera->x > 750 && spr_camera->x <= 1000 && nut_region <= 3) {
		SpriteManagerAdd(SpriteAcorn, 111*8, 7*8);
		SpriteManagerAdd(EnemyBirdy, 130*8, 9*8);
		SpriteManagerAdd(SpriteAcorn, 140*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 142*8, 7*8);
		SpriteManagerAdd(SpriteBalloon, 146*8, 9*8);
	    nut_region = 4;
	}
	// Up to 188:
	else if (spr_camera->x > 1000 && spr_camera->x <= 1250 && nut_region <= 4) {
		SpriteManagerAdd(SpriteBalloon, 163*8, 13*8);
		SpriteManagerAdd(EnemyButterfly, 172*8, 8*8);
		SpriteManagerAdd(SpriteAcorn, 185*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 185*8, 9*8);
	    nut_region = 5;
	}
	// Up to 219:
	else if (spr_camera->x > 1250 && spr_camera->x <= 1500 && nut_region <= 5) {
		SpriteManagerAdd(SpriteAcorn, 205*8, 12*8);
		SpriteManagerAdd(EnemyBirdy, 218*8, 10*8);
		nut_region = 6;
	}
	// Up to 250:
	else if (spr_camera->x > 1500 && spr_camera->x <= 1750 && nut_region <= 6) {
		SpriteManagerAdd(EnemyBirdy, 231*8, 11*8);
	    nut_region = 7;
	}
	else if (spr_camera->x > 1750 && spr_camera->x <= 2000 && nut_region <= 7) {
	    nut_region = 8;
	}
}