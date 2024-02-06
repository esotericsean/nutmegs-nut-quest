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

IMPORT_MAP (level7map);
IMPORT_MAP (hud);

UINT16 level7counter = 0;
UINT8 endlevel_counter7 = 0;

//nutmeg color palettes
const UWORD pal_nutmegnormal7[] = { RGB(31, 31, 31), RGB(5,  24, 14), RGB(5,  19, 12), RGB(0,  0,  0) };
const UWORD pal_nutmegblue7[] 	= { RGB(31, 31, 31), RGB(19, 22, 30), RGB(12, 13, 28), RGB(8,  8, 27) };

const UINT8 collision_tiles_level7[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
const UINT8 collision_tiles_down_level7[] = {29,30,31,32,0};

DECLARE_MUSIC(quickstart);
DECLARE_MUSIC(mushrooms);
DECLARE_MUSIC(quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_camera;

//grey top
const unsigned char grey7_33[] = {
	0xff,0x3c,0xc3,0x46,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};
const unsigned char grey7_34[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};
const unsigned char grey7_35[] = {
	0xff,0x3c,0xc3,0x7a,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};
const unsigned char grey7_36[] = {
	0xff,0x3c,0xc3,0x42,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink top
const unsigned char pink7_37[] = {
	0xff,0x3c,0xc3,0x42,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};
const unsigned char pink7_38[] = {
	0xff,0x3c,0xc3,0x5e,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};
const unsigned char pink7_39[] = {
	0xff,0x3c,0xc3,0x7e,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};
const unsigned char pink7_40[] = {
	0xff,0x3c,0xc3,0x62,0x81,0x81,0x81,0x81,
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff
};

//grey mid/bottom
const unsigned char grey7_41[] = {
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81,
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff
};
const unsigned char grey7_42[] = {
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87,
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9
};
const unsigned char grey7_43[] = {
	0x81,0xe1,0x81,0xf9,0x81,0xff,0x81,0xff,
	0x81,0x9f,0x81,0x87,0x81,0x81,0x81,0x81
};
const unsigned char grey7_44[] = {
	0x81,0x81,0x81,0x81,0x81,0xe1,0x81,0xf9,
	0x81,0xff,0x81,0xff,0x81,0x9f,0x81,0x87
};

//pink mid/bottom
const unsigned char pink7_45[] = {
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f,
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1
};
const unsigned char pink7_46[] = {
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff,
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81
};
const unsigned char pink7_47[] = {
	0x81,0xff,0x81,0xff,0x81,0xf9,0x81,0xe1,
	0x81,0x81,0x81,0x81,0x81,0x87,0x81,0x9f
};
const unsigned char pink7_48[] = {
	0x81,0xf9,0x81,0xe1,0x81,0x81,0x81,0x81,
	0x81,0x87,0x81,0x9f,0x81,0xff,0x81,0xff
};

//Level Start! Text
const unsigned char UpperL7[] = {
	0xff,0x00,0xff,0x20,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerE7[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x24,0xff,0x38,0xff,0x20,0xff,0x1c
};
const unsigned char LowerV7[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x44,
	0xff,0x44,0xff,0x28,0xff,0x28,0xff,0x10
};
const unsigned char LowerL7[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x38
};
const unsigned char UpperS7[] = {
	0xff,0x00,0xff,0x18,0xff,0x24,0xff,0x20,
	0xff,0x18,0xff,0x04,0xff,0x24,0xff,0x18
};
const unsigned char LowerT7[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x78,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerA7[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x04,0xff,0x1c,0xff,0x24,0xff,0x1a
};
const unsigned char LowerR7[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x20
};
const unsigned char Exclam7[] = {
	0xff,0x00,0xff,0x10,0xff,0x10,0xff,0x10,
	0xff,0x10,0xff,0x10,0xff,0x00,0xff,0x10
};
const unsigned char BlankSky7[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00
};

const unsigned char Letter1_7[]  = { 0x54 }; //54-5E
const unsigned char Letter2_7[]  = { 0x55 };
const unsigned char Letter3_7[]  = { 0x56 };
const unsigned char Letter4_7[]  = { 0x57 };
const unsigned char Letter5_7[]  = { 0x58 };
const unsigned char Letter6_7[]  = { 0x59 };
const unsigned char Letter7_7[]  = { 0x5A };
const unsigned char Letter8_7[]  = { 0x5B };
const unsigned char Letter9_7[]  = { 0x5C };
const unsigned char Letter10_7[] = { 0x5D };
const unsigned char Letter11_7[] = { 0x5E };

//timer counter
UINT16 timerlevel7;
UINT8 timerclock7;

void UpdateHud7() {
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

	if (timerclock7 <= 25 && cutscenemode == disabled) timerclock7 ++; //25 seems good

	if (timerclock7 == 25) {
		timerclock7 = 0;
		timerlevel7--;
	}

	//timer:
	//timer 100s digit:
	if (timerlevel7 == 300) UPDATE_HUD_TILE (10, 0, 9);
	if (timerlevel7 < 300 && timerlevel7 >= 200) UPDATE_HUD_TILE (10, 0, 8);
	if (timerlevel7 < 200 && timerlevel7 >= 100) UPDATE_HUD_TILE (10, 0, 7);
	if (timerlevel7 < 100) UPDATE_HUD_TILE (10, 0, 6);
	//timer 10s digit:
	if (timerlevel7 < 300 && timerlevel7 >= 200) {
		switch (timerlevel7 - 200 - (timerlevel7 % 10)) {
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
	else if (timerlevel7 < 200 && timerlevel7 >= 100) {
		switch (timerlevel7 - 100 - (timerlevel7 % 10)) {
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
	switch (timerlevel7 - (timerlevel7 % 10)) {
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
	switch (timerlevel7 % 10) {
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

void Start_StateLevel7() {
	level7counter = 0;
	timerlevel7 = 300;
	timerclock7 = 0;
	levelorientation = horizontal;
	SPRITES_8x16;

	fish_pal_loc = 3;

	nut_region = 0;
	pitdeathactive = true;

	deathmusicplayed = false;

	PlayMusic(quickstart, 1);
	
	//if health is full, add the bow
	if (health == full) { SpriteManagerAdd(SpriteNutmegBow, 4, 49); }
	scroll_target = spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 4, 49); //36

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level7map), &level7map, collision_tiles_level7, collision_tiles_down_level7);
	INIT_HUD(hud);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	FlagPole_Init();
	endlevel_counter7 = 0;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel7() {
	UpdateHud7();

	if (timerlevel7 <= 0) nutmeg_death = true;

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
		if (level7counter == 0) {
			cutscenewalkright = true;
		}
		else if (level7counter >= 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		if (level7counter >= 10 && level7counter < 40) {
			set_bkg_data (0x54, 1, UpperL7);
			set_bkg_data (0x55, 1, LowerE7);
			set_bkg_data (0x56, 1, LowerV7);
			set_bkg_data (0x57, 1, LowerE7);
			set_bkg_data (0x58, 1, LowerL7);
			set_bkg_data (0x59, 1, UpperS7);
			set_bkg_data (0x5A, 1, LowerT7);
			set_bkg_data (0x5B, 1, LowerA7);
			set_bkg_data (0x5C, 1, LowerR7);
			set_bkg_data (0x5D, 1, LowerT7);
			set_bkg_data (0x5E, 1, Exclam7);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_7); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_7);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_7);
			set_bkg_tiles (10, 5, 1, 1, Letter4_7);
			set_bkg_tiles (11, 5, 1, 1, Letter5_7);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_7);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_7);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_7);
			set_bkg_tiles (10, 6, 1, 1, Letter9_7);
			set_bkg_tiles (11, 6, 1, 1, Letter10_7);
			set_bkg_tiles (12, 6, 1, 1, Letter11_7);
		}
		else if (level7counter >= 40 && level7counter < 70) {
			set_bkg_data (0x54, 1, BlankSky7);
			set_bkg_data (0x55, 1, BlankSky7);
			set_bkg_data (0x56, 1, BlankSky7);
			set_bkg_data (0x57, 1, BlankSky7);
			set_bkg_data (0x58, 1, BlankSky7);
			set_bkg_data (0x59, 1, BlankSky7);
			set_bkg_data (0x5A, 1, BlankSky7);
			set_bkg_data (0x5B, 1, BlankSky7);
			set_bkg_data (0x5C, 1, BlankSky7);
			set_bkg_data (0x5D, 1, BlankSky7);
			set_bkg_data (0x5E, 1, BlankSky7);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_7); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_7);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_7);
			set_bkg_tiles (10, 5, 1, 1, Letter4_7);
			set_bkg_tiles (11, 5, 1, 1, Letter5_7);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_7);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_7);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_7);
			set_bkg_tiles (10, 6, 1, 1, Letter9_7);
			set_bkg_tiles (11, 6, 1, 1, Letter10_7);
			set_bkg_tiles (12, 6, 1, 1, Letter11_7);
		}
		else if (level7counter >= 70 && level7counter < 100) {
			set_bkg_data (0x54, 1, UpperL7);
			set_bkg_data (0x55, 1, LowerE7);
			set_bkg_data (0x56, 1, LowerV7);
			set_bkg_data (0x57, 1, LowerE7);
			set_bkg_data (0x58, 1, LowerL7);
			set_bkg_data (0x59, 1, UpperS7);
			set_bkg_data (0x5A, 1, LowerT7);
			set_bkg_data (0x5B, 1, LowerA7);
			set_bkg_data (0x5C, 1, LowerR7);
			set_bkg_data (0x5D, 1, LowerT7);
			set_bkg_data (0x5E, 1, Exclam7);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_7); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_7);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_7);
			set_bkg_tiles (10, 5, 1, 1, Letter4_7);
			set_bkg_tiles (11, 5, 1, 1, Letter5_7);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_7);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_7);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_7);
			set_bkg_tiles (10, 6, 1, 1, Letter9_7);
			set_bkg_tiles (11, 6, 1, 1, Letter10_7);
			set_bkg_tiles (12, 6, 1, 1, Letter11_7);
		}
		else if (level7counter >= 100 && level7counter < 101) {
			set_bkg_data (0x54, 1, BlankSky7);
			set_bkg_data (0x55, 1, BlankSky7);
			set_bkg_data (0x56, 1, BlankSky7);
			set_bkg_data (0x57, 1, BlankSky7);
			set_bkg_data (0x58, 1, BlankSky7);
			set_bkg_data (0x59, 1, BlankSky7);
			set_bkg_data (0x5A, 1, BlankSky7);
			set_bkg_data (0x5B, 1, BlankSky7);
			set_bkg_data (0x5C, 1, BlankSky7);
			set_bkg_data (0x5D, 1, BlankSky7);
			set_bkg_data (0x5E, 1, BlankSky7);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1_7); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2_7);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3_7);
			set_bkg_tiles (10, 5, 1, 1, Letter4_7);
			set_bkg_tiles (11, 5, 1, 1, Letter5_7);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6_7);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7_7);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8_7);
			set_bkg_tiles (10, 6, 1, 1, Letter9_7);
			set_bkg_tiles (11, 6, 1, 1, Letter10_7);
			set_bkg_tiles (12, 6, 1, 1, Letter11_7);

			cutscenemode = disabled;

			if (levelbeat == false) {
				PlayMusic(mushrooms, 1);
			}
		}

		if (level7counter < 105) level7counter++;
	}

	Water_Animate();

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

		if (endlevel_counter7 >= 100) {
			//endlevel_counter7 = 0;
			//cutscenewalkleft = false;
			//cutscenewalkright = false;
			//cutscenemode = disabled;

			SetState(StateOverworld1);
		}

		if (endlevel_counter7 < 250) endlevel_counter7++;
	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && levelbeat == false && nutmeg_death == false) {
		FlagPole_Activate(1948, 94); 
		levelbeat = true;
		endlevel_counter7 = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
	
	}

	// 0-31:
	if (spr_nutmeg->x > 0 && spr_nutmeg->x <= 250 && nut_region <= 0) {
		//generate puff to add its color palette before others
		SpriteManagerAdd(SpritePuffLeft, 0, 0);
		//generate star to add its color palette before others
		SpriteManagerAdd(SpriteStarLeft, 0, 0);

		SpriteManagerAdd(SpriteAcorn, 25*8, 9*8);
		SpriteManagerAdd(SpriteAcorn, 27*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 30*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 32*8, 9*8);
		nut_region = 1;
	}
	// Up to 62:
	else if (spr_nutmeg->x > 250 && spr_nutmeg->x <= 500 && nut_region <= 1) {
		SpriteManagerAdd(SpriteAcorn, 71*8, 9*8);
    	nut_region = 2;
	}
	// Up to 94:
	else if (spr_nutmeg->x > 500 && spr_nutmeg->x <= 750 && nut_region <= 2) {
		
		SpriteManagerAdd(EnemyFish, 96*8, 15*8);

		SpriteManagerAdd(SpriteAcorn, 107*8, 4*8);
		SpriteManagerAdd(SpriteAcorn, 109*8, 6*8);
	    nut_region = 3;
	}
	// Up to 125:
	else if (spr_nutmeg->x > 750 && spr_nutmeg->x <= 1000 && nut_region <= 3) {
		SpriteManagerAdd(SpriteAcorn, 123*8+4, 3*8);
		SpriteManagerAdd(SpriteAcorn, 130*8+4, 14*8);
		SpriteManagerAdd(EnemyBatty, 131*8, 8*8);
	    nut_region = 4;
	}
	// Up to 156:
	else if (spr_nutmeg->x > 1000 && spr_nutmeg->x <= 1250 && nut_region <= 4) {
		SpriteManagerAdd(SpriteAcorn, 149*8-2, 12*8-2);
		SpriteManagerAdd(SpriteAcorn, 150*8+2, 12*8-2);
		SpriteManagerAdd(SpriteAcorn, 149*8-2, 13*8+2);
		SpriteManagerAdd(SpriteAcorn, 150*8+2, 13*8+2);

		SpriteManagerAdd(SpriteAcorn, 158*8+4, 14*8+4);
		SpriteManagerAdd(SpriteAcorn, 164*8+4, 2*8+4);
	    nut_region = 5;
	}
	// Up to 188:
	else if (spr_nutmeg->x > 1250 && spr_nutmeg->x <= 1500 && nut_region <= 5) {
		SpriteManagerAdd(SpriteAcorn, 168*8+4, 2*8+4);
		SpriteManagerAdd(EnemyBatty, 183*8, 4*8);
	    nut_region = 6;
	}
	// Up to 219:
	else if (spr_nutmeg->x > 1500 && spr_nutmeg->x <= 1750 && nut_region <= 6) {
		SpriteManagerAdd(SpriteAcorn, 211*8, 9*8);
		SpriteManagerAdd(SpriteAcorn, 213*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 216*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 218*8, 9*8);
		SpriteManagerAdd(EnemyButterfly, 198*8, 12*8);
		SpriteManagerAdd(EnemyBunny, 221*8, 13*8);
	    nut_region = 7;
	}
	else if (spr_nutmeg->x > 1750 && spr_nutmeg->x <= 2000 && nut_region <= 7) {
	    nut_region = 8;
	}
}