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

IMPORT_MAP (level4map);
IMPORT_MAP (hud);

UINT16 level4counter = 0;
UINT8 endlevel_counter4 = 0;

UINT8 fish_pal_loc;


const UINT8 collision_tiles_level4[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
const UINT8 collision_tiles_down_level4[] = {29,30,31,32,0};

DECLARE_MUSIC(quickstart);
DECLARE_MUSIC(mushrooms);
DECLARE_MUSIC(quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
//extern Sprite * spr_nutmeg2;
extern Sprite * spr_camera;
//struct Sprite * spr_nutmegbow;

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

//timer counter
UINT16 timerlevel4;
UINT8 timerclock4;

void UpdateHud4() {
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

	if (timerclock4 <= 25 && cutscenemode == disabled) timerclock4 ++; //25 seems good

	if (timerclock4 == 25) {
		timerclock4 = 0;
		timerlevel4--;
	}

	//timer:
	//timer 100s digit:
	if (timerlevel4 == 300) UPDATE_HUD_TILE (10, 0, 9);
	if (timerlevel4 < 300 && timerlevel4 >= 200) UPDATE_HUD_TILE (10, 0, 8);
	if (timerlevel4 < 200 && timerlevel4 >= 100) UPDATE_HUD_TILE (10, 0, 7);
	if (timerlevel4 < 100) UPDATE_HUD_TILE (10, 0, 6);
	//timer 10s digit:
	if (timerlevel4 < 300 && timerlevel4 >= 200) {
		switch (timerlevel4 - 200 - (timerlevel4 % 10)) {
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
	else if (timerlevel4 < 200 && timerlevel4 >= 100) {
		switch (timerlevel4 - 100 - (timerlevel4 % 10)) {
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
	switch (timerlevel4 - (timerlevel4 % 10)) {
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
	switch (timerlevel4 % 10) {
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

void Start_StateLevel4() {
	level4counter = 0;
	timerlevel4 = 300;
	timerclock4 = 0;
	levelorientation = horizontal;
	SPRITES_8x16;

	if (health == full) fish_pal_loc = 3;
	else fish_pal_loc = 2;

	nut_region = 0;
	pitdeathactive = true;

	deathmusicplayed = false;

	PlayMusic(quickstart, 1);

	//testing:
	//health = full;
	//lostbow = false;

	//if health is full, add the bow
	if (health == full) { SpriteManagerAdd(SpriteNutmegBow, 4, 49); }
	scroll_target = spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 4, 49); //36

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level4map), &level4map, collision_tiles_level4, collision_tiles_down_level4);
	INIT_HUD(hud);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	FlagPole_Init();
	endlevel_counter4 = 0;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel4() {
	UpdateHud4();

	if (timerlevel4 <= 0) nutmeg_death = true;

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

			if (levelbeat == false) {
				PlayMusic(mushrooms, 1);
			}
		}

		if (level4counter < 105) level4counter++;
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

		if (endlevel_counter4 >= 100) {
			//endlevel_counter4 = 0;
			//cutscenewalkleft = false;
			//cutscenewalkright = false;
			//cutscenemode = disabled;

			SetState(StateOverworld1);
		}

		if (endlevel_counter4 < 250) endlevel_counter4++;
	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && levelbeat == false && nutmeg_death == false) {
		FlagPole_Activate(1948, 96);
		levelbeat = true;
		endlevel_counter4 = 0;
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

	// 0-63:
	if (spr_nutmeg->x > 0 && spr_nutmeg->x <= 250 && nut_region <= 0) {
		SpriteManagerAdd(SpriteMushroom, 31*8, 12*8);
		SpriteManagerAdd(EnemyFish, 16*8, 16*8);
		SpriteManagerAdd(SpriteAcorn, 36*8+4, 5*8);
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_nutmeg->x > 250 && spr_nutmeg->x <= 500 && nut_region <= 1) {
		SpriteManagerAdd(SpriteAcorn, 43*8+4, 3*8);
		SpriteManagerAdd(SpriteAcorn, 50*8+4, 4*8);
		SpriteManagerAdd(SpriteAcorn, 57*8+4, 3*8);
		SpriteManagerAdd(SpriteAcorn, 64*8+4, 4*8);
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
		SpriteManagerAdd(SpriteMushroom, 126*8, 13*8);
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