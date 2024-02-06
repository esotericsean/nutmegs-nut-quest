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
#include "Hud.h"

IMPORT_MAP (level1map);
IMPORT_MAP (hud);

UINT16 level1counter = 0;
UINT8 endlevel_counter = 0;

bool pitdeathactive;

orientation levelorientation;

const UINT8 collision_tiles_level1[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
const UINT8 collision_tiles_down_level1[] = {29,30,31,32,0};

DECLARE_MUSIC (quickstart);
DECLARE_MUSIC (mushrooms);
DECLARE_MUSIC (quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_camera;

//Level Start! Text
const unsigned char UpperL[] = {
	0xff,0x00,0xff,0x20,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerE[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x24,0xff,0x38,0xff,0x20,0xff,0x1c
};
const unsigned char LowerV[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x44,
	0xff,0x44,0xff,0x28,0xff,0x28,0xff,0x10
};
const unsigned char LowerL[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x38
};
const unsigned char UpperS[] = {
	0xff,0x00,0xff,0x18,0xff,0x24,0xff,0x20,
	0xff,0x18,0xff,0x04,0xff,0x24,0xff,0x18
};
const unsigned char LowerT[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x78,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerA[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x04,0xff,0x1c,0xff,0x24,0xff,0x1a
};
const unsigned char LowerR[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x20
};
const unsigned char Exclam[] = {
	0xff,0x00,0xff,0x10,0xff,0x10,0xff,0x10,
	0xff,0x10,0xff,0x10,0xff,0x00,0xff,0x10
};
const unsigned char BlankSky[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00
};

const unsigned char  Letter1[] = { 0x54 }; //54-5E
const unsigned char  Letter2[] = { 0x55 };
const unsigned char  Letter3[] = { 0x56 };
const unsigned char  Letter4[] = { 0x57 };
const unsigned char  Letter5[] = { 0x58 };
const unsigned char  Letter6[] = { 0x59 };
const unsigned char  Letter7[] = { 0x5A };
const unsigned char  Letter8[] = { 0x5B };
const unsigned char  Letter9[] = { 0x5C };
const unsigned char Letter10[] = { 0x5D };
const unsigned char Letter11[] = { 0x5E };

//nutmeg sprite region
UINT8 nut_region;

//first time playing level 1
bool firstplay = true;

bool deathmusicplayed = false;

void Start_StateLevel1() {
	level1counter = 0;
	levelorientation = horizontal;
	SPRITES_8x16;

	pitdeathactive = true;

	nut_region = 0;

	deathmusicplayed = false;

	PlayMusic(quickstart, 1);

	//start the game off with a bow (full health)
	if (firstplay == true) {
		SpriteManagerAdd(SpriteNutmegBow, 4, 49);
		health = full;
		lostbow = false;
		firstplay = false;
	}
	scroll_target = spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 4, 49);

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level1map), &level1map, collision_tiles_level1, collision_tiles_down_level1);
	INIT_HUD(hud);
	Hud_Init();
	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	FlagPole_Init();
	endlevel_counter = 0;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel1() {
	Hud_Update();

	if (timerlevel == 0) {
		nutmeg_death = true;

		if (health == full) {
			lostbow = true;
			bow_counter = 0;
			if (nutmeg_direction == right) { bowanim = 8; }
			else if (nutmeg_direction == left) { bowanim = 9; }
		}
	}

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
		if (level1counter == 0) {
			cutscenewalkright = true;
		}
		else if (level1counter >= 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		if (level1counter >= 10 && level1counter < 40) {
			set_bkg_data (0x54, 1, UpperL);
			set_bkg_data (0x55, 1, LowerE);
			set_bkg_data (0x56, 1, LowerV);
			set_bkg_data (0x57, 1, LowerE);
			set_bkg_data (0x58, 1, LowerL);
			set_bkg_data (0x59, 1, UpperS);
			set_bkg_data (0x5A, 1, LowerT);
			set_bkg_data (0x5B, 1, LowerA);
			set_bkg_data (0x5C, 1, LowerR);
			set_bkg_data (0x5D, 1, LowerT);
			set_bkg_data (0x5E, 1, Exclam);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3);
			set_bkg_tiles (10, 5, 1, 1, Letter4);
			set_bkg_tiles (11, 5, 1, 1, Letter5);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8);
			set_bkg_tiles (10, 6, 1, 1, Letter9);
			set_bkg_tiles (11, 6, 1, 1, Letter10);
			set_bkg_tiles (12, 6, 1, 1, Letter11);
		}
		else if (level1counter >= 40 && level1counter < 70) {
			set_bkg_data (0x54, 1, BlankSky);
			set_bkg_data (0x55, 1, BlankSky);
			set_bkg_data (0x56, 1, BlankSky);
			set_bkg_data (0x57, 1, BlankSky);
			set_bkg_data (0x58, 1, BlankSky);
			set_bkg_data (0x59, 1, BlankSky);
			set_bkg_data (0x5A, 1, BlankSky);
			set_bkg_data (0x5B, 1, BlankSky);
			set_bkg_data (0x5C, 1, BlankSky);
			set_bkg_data (0x5D, 1, BlankSky);
			set_bkg_data (0x5E, 1, BlankSky);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3);
			set_bkg_tiles (10, 5, 1, 1, Letter4);
			set_bkg_tiles (11, 5, 1, 1, Letter5);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8);
			set_bkg_tiles (10, 6, 1, 1, Letter9);
			set_bkg_tiles (11, 6, 1, 1, Letter10);
			set_bkg_tiles (12, 6, 1, 1, Letter11);
		}
		else if (level1counter >= 70 && level1counter < 100) {
			set_bkg_data (0x54, 1, UpperL);
			set_bkg_data (0x55, 1, LowerE);
			set_bkg_data (0x56, 1, LowerV);
			set_bkg_data (0x57, 1, LowerE);
			set_bkg_data (0x58, 1, LowerL);
			set_bkg_data (0x59, 1, UpperS);
			set_bkg_data (0x5A, 1, LowerT);
			set_bkg_data (0x5B, 1, LowerA);
			set_bkg_data (0x5C, 1, LowerR);
			set_bkg_data (0x5D, 1, LowerT);
			set_bkg_data (0x5E, 1, Exclam);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3);
			set_bkg_tiles (10, 5, 1, 1, Letter4);
			set_bkg_tiles (11, 5, 1, 1, Letter5);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8);
			set_bkg_tiles (10, 6, 1, 1, Letter9);
			set_bkg_tiles (11, 6, 1, 1, Letter10);
			set_bkg_tiles (12, 6, 1, 1, Letter11);
		}
		else if (level1counter >= 100 && level1counter < 101) {
			set_bkg_data (0x54, 1, BlankSky);
			set_bkg_data (0x55, 1, BlankSky);
			set_bkg_data (0x56, 1, BlankSky);
			set_bkg_data (0x57, 1, BlankSky);
			set_bkg_data (0x58, 1, BlankSky);
			set_bkg_data (0x59, 1, BlankSky);
			set_bkg_data (0x5A, 1, BlankSky);
			set_bkg_data (0x5B, 1, BlankSky);
			set_bkg_data (0x5C, 1, BlankSky);
			set_bkg_data (0x5D, 1, BlankSky);
			set_bkg_data (0x5E, 1, BlankSky);

			set_bkg_tiles ( 7, 5, 1, 1, Letter1); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 5, 1, 1, Letter2);
			set_bkg_tiles ( 9, 5, 1, 1, Letter3);
			set_bkg_tiles (10, 5, 1, 1, Letter4);
			set_bkg_tiles (11, 5, 1, 1, Letter5);
			set_bkg_tiles ( 7, 6, 1, 1, Letter6);
			set_bkg_tiles ( 8, 6, 1, 1, Letter7);
			set_bkg_tiles ( 9, 6, 1, 1, Letter8);
			set_bkg_tiles (10, 6, 1, 1, Letter9);
			set_bkg_tiles (11, 6, 1, 1, Letter10);
			set_bkg_tiles (12, 6, 1, 1, Letter11);

			cutscenemode = disabled;

			if (levelbeat == false) {
				PlayMusic(mushrooms, 1);
			}
		}

		if (level1counter < 105) level1counter++;
	}

	Water_Animate();

	FlagPole_Animate();

	//animate pink flagpole
	if (levelbeat == true) {
		cutscenemode = enabled;
		
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

	
		if (endlevel_counter >= 100) {
			//endlevel_counter = 0;
			//cutscenewalkleft = false;
			//cutscenewalkright = false;
			//cutscenemode = disabled;

			SetState(StateOverworld1);
		}

		if (endlevel_counter < 250) endlevel_counter++;

	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && levelbeat == false && nutmeg_death == false) {
		FlagPole_Activate(1948,96);

		levelbeat = true;
		endlevel_counter = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
		
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
	if (spr_nutmeg->x > 0 && spr_nutmeg->x <= 250 && nut_region <= 0) {
		//SpriteManagerAdd(SpriteAcorn, 272, 88);
		//SpriteManagerAdd(SpriteAcorn, 296, 40);
		//SpriteManagerAdd(EnemyButterfly, 192, 56);
		//SpriteManagerAdd(EnemyButterfly, 472, 64);
		SpriteManagerAdd(EnemyButterfly, 12*8, 4*8);
		SpriteManagerAdd(SpriteAcorn, 47*8, 2*8);
		SpriteManagerAdd(SpriteAcorn, 54*8, 2*8);
		SpriteManagerAdd(EnemyBunny, 59*8, 13*8); //Bunny always 1 higher in y value
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_nutmeg->x > 250 && spr_nutmeg->x <= 500 && nut_region <= 1) {
		//SpriteManagerAdd(SpriteAcorn, 552, 24);
		//SpriteManagerAdd(SpriteAcorn, 712, 40);
		//SpriteManagerAdd(EnemyBunny, 576, 80);
		//SpriteManagerAdd(EnemyBunny, 712, 96);
		SpriteManagerAdd(EnemyButterfly, 89*8, 9*8);
		SpriteManagerAdd(SpriteAcorn, 85*8, 12*8);
		SpriteManagerAdd(SpriteAcorn, 93*8, 12*8);
    	nut_region = 2;
	}
	// Up to 125:
	else if (spr_nutmeg->x > 500 && spr_nutmeg->x <= 750 && nut_region <= 2) {
		//SpriteManagerAdd(SpriteAcorn, 984, 40);
		SpriteManagerAdd(SpriteAcorn, 105*8, 5*8);
		SpriteManagerAdd(SpriteAcorn, 123*8, 5*8);
	    nut_region = 3;
	}
	// Up to 156:
	else if (spr_nutmeg->x > 750 && spr_nutmeg->x <= 1000 && nut_region <= 3) {
		//SpriteManagerAdd(EnemyBunny, 1048, 64);
		SpriteManagerAdd(EnemyBunny, 132*8, 9*8);
	    nut_region = 4;
	}
	// Up to 188:
	else if (spr_nutmeg->x > 1000 && spr_nutmeg->x <= 1250 && nut_region <= 4) {
		//SpriteManagerAdd(SpriteAcorn, 1296, 80);
		//SpriteManagerAdd(SpriteAcorn, 1320, 64);
		//SpriteManagerAdd(SpriteAcorn, 1424, 112);
		SpriteManagerAdd(SpriteAcorn, 163*8, 10*8);
		SpriteManagerAdd(SpriteAcorn, 166*8, 8*8);
		SpriteManagerAdd(SpriteAcorn, 178*8, 14*8);
	    nut_region = 5;
	}
	// Up to 219:
	else if (spr_nutmeg->x > 1250 && spr_nutmeg->x <= 1500 && nut_region <= 5) {
		//SpriteManagerAdd(EnemyBunny, 1640, 104);
		SpriteManagerAdd(EnemyButterfly, 216*8, 11*8);
	    nut_region = 6;
	}
	// Up to 250:
	else if (spr_nutmeg->x > 1500 && spr_nutmeg->x <= 1750 && nut_region <= 6) {
		//SpriteManagerAdd(SpriteAcorn, 1752, 48);
		SpriteManagerAdd(EnemyButterfly, 228*8, 10*8);
	    nut_region = 7;
	}
	else if (spr_nutmeg->x > 1750 && spr_nutmeg->x <= 2000 && nut_region <= 7) {
	    nut_region = 8;
	}
}