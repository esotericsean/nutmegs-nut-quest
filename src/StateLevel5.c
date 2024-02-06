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
#include "FlagPole.h"
#include "Water.h"

IMPORT_MAP (level5map);
IMPORT_MAP (hud);

UINT16 level5counter = 0;
UINT8 anim_rain_counter5 = 0;
UINT8 endlevel_counter5 = 0;
UINT8 lightningstrikecounter1 = 0;
UINT8 lightningstrikecounter2 = 0;

//nutmeg rainy colors
const UWORD pal_nut5[] = { RGB(31, 31, 31), RGB(25, 21, 19), RGB(23, 13, 4), RGB(2, 2, 2) };

const UINT8 collision_tiles_level5[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
const UINT8 collision_tiles_down_level5[] = {29,30,31,32,0};

DECLARE_MUSIC(raindrops);
DECLARE_MUSIC(quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;


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

//timer counter
UINT16 timerlevel5;
UINT8 timerclock5;

void UpdateHud5() {
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

	if (timerclock5 <= 25 && cutscenemode == disabled) timerclock5 ++; //25 seems good

	if (timerclock5 == 25) {
		timerclock5 = 0;
		timerlevel5--;
	}

	//timer:
	//timer 100s digit:
	if (timerlevel5 == 300) UPDATE_HUD_TILE (10, 0, 9);
	if (timerlevel5 < 300 && timerlevel5 >= 200) UPDATE_HUD_TILE (10, 0, 8);
	if (timerlevel5 < 200 && timerlevel5 >= 100) UPDATE_HUD_TILE (10, 0, 7);
	if (timerlevel5 < 100) UPDATE_HUD_TILE (10, 0, 6);
	//timer 10s digit:
	if (timerlevel5 < 300 && timerlevel5 >= 200) {
		switch (timerlevel5 - 200 - (timerlevel5 % 10)) {
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
	else if (timerlevel5 < 200 && timerlevel5 >= 100) {
		switch (timerlevel5 - 100 - (timerlevel5 % 10)) {
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
	switch (timerlevel5 - (timerlevel5 % 10)) {
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
	switch (timerlevel5 % 10) {
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

void Start_StateLevel5() {
	level5counter = 0;
	timerlevel5 = 300;
	timerclock5 = 0;
	levelorientation = horizontal;
	SPRITES_8x16;

	nut_region = 0;
	pitdeathactive = true;

	deathmusicplayed = false;

	PlayMusic(raindrops, 1);

	//if health is full, add the bow
	if (health == full) { SpriteManagerAdd(SpriteNutmegBow, 3*8, 11*8); }
	scroll_target = spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 3*8, 11*8); //36

	InitScrollTiles(0, &level5tiles);
	InitScroll(BANK(level5map), &level5map, collision_tiles_level5, collision_tiles_down_level5);
	INIT_HUD(hud);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	FlagPole_Init();

	endlevel_counter5 = 0;

	lightningstrikecounter1 = 0;
	lightningstrikecounter2 = 0;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel5() {
	UpdateHud5();

	if (timerlevel5 <= 0) nutmeg_death = true;

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

	if (lightningstrikecounter1 < 87)
		lightningstrikecounter1++;
	
	if (lightningstrikecounter1 == 36) {
		SpriteManagerAdd(EnemyLightningSpot, 13*8, 10*8);
	}
	else if (lightningstrikecounter1 == 86) {
		SpriteManagerAdd(EnemyLightning, 13*8, 0*8);
	}
	
	if (cutscenemode == enabled) {	
		//Level Start!
		//Make Nutmeg Walk In
		if (level5counter == 0) {
			cutscenewalkright = false;
			//SetPalette (SPRITES_PALETTE, 0, 1, pal_nut5, _current_bank);
		}
		else if (level5counter == 100) {
			cutscenemode = disabled;

			if (levelbeat == false) {
				PlayMusic(raindrops, 1);
			}
		}

		if (level5counter < 105) level5counter++;
	}

	if (spr_nutmeg->x < 1936) {
		if (movestate == inair) { TranslateSprite (spr_nutmeg, -1, 0); }
	}
	else if (spr_nutmeg->x >= 1936) {
		TranslateSprite (spr_nutmeg, 0, 0);
	}

	Water_Animate();

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

	FlagPole_Animate();

	if (levelbeat == true) {
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

		if (endlevel_counter5 >= 100) {
			//endlevel_counter5 = 0;
			//cutscenewalkleft = false;
			//cutscenewalkright = false;
			//cutscenemode = disabled;

			SetState(StateOverworld1);
		}

		if (endlevel_counter5 < 250) endlevel_counter5++;


	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && levelbeat == false && nutmeg_death == false) {
		FlagPole_Activate(1948, 96);
		levelbeat = true;
		endlevel_counter5 = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
		
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

	//INFINITE SPAWNS WHILE IN REGIONS:
	if (spr_nutmeg->x > 0 && spr_nutmeg->x <= 250) {
		if (lightningstrikecounter2 == 100) {
			SpriteManagerAdd(EnemyLightningSpot, 28*8, 10*8); //subtract 3 from the y
		}
		else if (lightningstrikecounter2 == 150) {
			SpriteManagerAdd(EnemyLightning, 28*8, 0*8);
		}

		lightningstrikecounter2++;
		if (lightningstrikecounter2 >= 155) lightningstrikecounter2 = 0;
	}
	else if (spr_nutmeg->x > 250 && spr_nutmeg->x <= 400) {
		if (lightningstrikecounter2 == 100) {
			SpriteManagerAdd(EnemyLightningSpot, 45*8, 11*8); //subtract 3 from the y
		}
		else if (lightningstrikecounter2 == 150) {
			SpriteManagerAdd(EnemyLightning, 45*8, 0*8);
		}

		lightningstrikecounter2++;
		if (lightningstrikecounter2 >= 155) lightningstrikecounter2 = 0;
	}
	else if (spr_nutmeg->x > 400 && spr_nutmeg->x <= 750) {
		if (lightningstrikecounter2 == 100) {
			SpriteManagerAdd(EnemyLightningSpot, 75*8, 10*8); //subtract 3 from the y
		}
		else if (lightningstrikecounter2 == 150) {
			SpriteManagerAdd(EnemyLightning, 75*8, 0*8);
		}

		lightningstrikecounter2++;
		if (lightningstrikecounter2 >= 155) lightningstrikecounter2 = 0;
	}
	else if (spr_nutmeg->x > 750 && spr_nutmeg->x <= 1000) {
		if (lightningstrikecounter2 == 100) {
			SpriteManagerAdd(EnemyLightningSpot, 105*8, 10*8); //subtract 3 from the y
		}
		else if (lightningstrikecounter2 == 150) {
			SpriteManagerAdd(EnemyLightning, 105*8, 0*8);
		}

		lightningstrikecounter2++;
		if (lightningstrikecounter2 >= 155) lightningstrikecounter2 = 0;
	}
	else if (spr_nutmeg->x > 1000 && spr_nutmeg->x <= 1500) {
		if (lightningstrikecounter2 == 100) {
			SpriteManagerAdd(EnemyLightningSpot, 159*8, 6*8); //subtract 3 from the y
		}
		else if (lightningstrikecounter2 == 150) {
			SpriteManagerAdd(EnemyLightning, 159*8, 0*8);
		}

		lightningstrikecounter2++;
		if (lightningstrikecounter2 >= 155) lightningstrikecounter2 = 0;
	}
	else if (spr_nutmeg->x > 1500 && spr_nutmeg->x <= 2000) {
		if (lightningstrikecounter2 == 100) {
			SpriteManagerAdd(EnemyLightningSpot, 236*8, 6*8); //subtract 3 from the y
		}
		else if (lightningstrikecounter2 == 150) {
			SpriteManagerAdd(EnemyLightning, 236*8, 0*8);
		}

		lightningstrikecounter2++;
		if (lightningstrikecounter2 >= 155) lightningstrikecounter2 = 0;
	}

	//Only Spawn Once:
	// 0-63:
	if (spr_nutmeg->x > 0 && spr_nutmeg->x <= 250 && nut_region <= 0) {
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_nutmeg->x > 250 && spr_nutmeg->x <= 500 && nut_region <= 1) {
		SpriteManagerAdd(EnemyEarthy, 63*8, 13*8); //subtract 0 from y
		nut_region = 2;
	}
	// Up to 125:
	else if (spr_nutmeg->x > 500 && spr_nutmeg->x <= 750 && nut_region <= 2) {
		SpriteManagerAdd(SpriteAcorn, 72*8, 1*8);
		SpriteManagerAdd(SpriteAcorn, 92*8, 13*8);
	    nut_region = 3;
	}
	// Up to 156:
	else if (spr_nutmeg->x > 750 && spr_nutmeg->x <= 1000 && nut_region <= 3) {
		SpriteManagerAdd(EnemyEarthy, 136*8, 14*8);
	    nut_region = 4;
	}
	// Up to 188:
	else if (spr_nutmeg->x > 1000 && spr_nutmeg->x <= 1250 && nut_region <= 4) {
		SpriteManagerAdd(SpriteAcorn, 139*8, 3*8);
		SpriteManagerAdd(SpriteAcorn, 141*8, 3*8);
	    nut_region = 5;
	}
	// Up to 219:
	else if (spr_nutmeg->x > 1250 && spr_nutmeg->x <= 1500 && nut_region <= 5) {
		SpriteManagerAdd(SpriteAcorn, 172*8, 5*8);
		SpriteManagerAdd(SpriteAcorn, 179*8, 1*8);
		nut_region = 6;
	}
	// Up to 250:
	else if (spr_nutmeg->x > 1500 && spr_nutmeg->x <= 1750 && nut_region <= 6) {
		SpriteManagerAdd(SpriteAcorn, 197*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 198*8, 12*8);
		SpriteManagerAdd(SpriteAcorn, 222*8, 6*8);
	    nut_region = 7;
	}
	else if (spr_nutmeg->x > 1750 && spr_nutmeg->x <= 2000 && nut_region <= 7) {
		SpriteManagerAdd(EnemyEarthy, 235*8, 13*8);
	    nut_region = 8;
	}
}