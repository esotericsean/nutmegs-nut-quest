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

IMPORT_MAP (level2map);


UINT16 level2counter = 0;
UINT8 endlevel_counter2 = 0;


const UINT8 collision_tiles_level2[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
const UINT8 collision_tiles_down_level2[] = {29,30,31,32,0};

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


void Start_StateLevel2() {
	level2counter = 0;

	levelorientation = horizontal;
	SPRITES_8x16;

	nut_region = 0;
	pitdeathactive = true;

	deathmusicplayed = false;

	PlayMusic(quickstart, 1);

	//if health is full, add the bow
	if (health == full) { SpriteManagerAdd(SpriteNutmegBow, 4, 49); }
	scroll_target = spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 4, 49); //36

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level2map), &level2map, collision_tiles_level2, collision_tiles_down_level2);
	Hud_Init(false);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	FlagPole_Init();
	endlevel_counter2 = 0;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel2() {
	Hud_Update();

	if (timerlevel == 0)
	{
		nutmeg_death = true;
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

			if (levelbeat == false) {
				PlayMusic(mushrooms, 1);
			}
		}

		if (level2counter < 105) level2counter++;
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

		if (endlevel_counter2 >= 100) {
			//endlevel_counter2 = 0;
			//cutscenewalkleft = false;
			//cutscenewalkright = false;
			//cutscenemode = disabled;

			SetState(StateOverworld1);
		}

		if (endlevel_counter2 < 250) endlevel_counter2++;
	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && levelbeat == false && nutmeg_death == false) {
		FlagPole_Activate (1948,96);
		
		levelbeat = true;
		endlevel_counter2 = 0;
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
		SpriteManagerAdd(SpriteAcorn, 27*8, 12*8);
		SpriteManagerAdd(EnemyBunny, 37*8, 14*8); //Bunny always 1 higher in y value
		SpriteManagerAdd(SpriteAcorn, 43*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 53*8, 4*8);
		SpriteManagerAdd(EnemyButterfly, 57*8, 3*8);
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_nutmeg->x > 250 && spr_nutmeg->x <= 500 && nut_region <= 1) {
		SpriteManagerAdd(SpriteAcorn, 68*8, 2*8);
		SpriteManagerAdd(SpriteAcorn, 77*8, 8*8);
		SpriteManagerAdd(SpriteAcorn, 91*8, 6*8);
    	nut_region = 2;
	}
	// Up to 125:
	else if (spr_nutmeg->x > 500 && spr_nutmeg->x <= 750 && nut_region <= 2) {
		SpriteManagerAdd(EnemyButterfly, 99*8, 10*8);
	    nut_region = 3;
	}
	// Up to 156:
	else if (spr_nutmeg->x > 750 && spr_nutmeg->x <= 1000 && nut_region <= 3) {
		SpriteManagerAdd(SpriteAcorn, 133*8, 9*8);
		SpriteManagerAdd(SpriteAcorn, 136*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 139*8, 9*8);
	    nut_region = 4;
	}
	// Up to 188:
	else if (spr_nutmeg->x > 1000 && spr_nutmeg->x <= 1250 && nut_region <= 4) {
		SpriteManagerAdd(EnemyBunny, 160*8, 13*8); //Bunny always 1 higher in y value
		SpriteManagerAdd(SpriteMushroom, 167*8, 12*8);
		SpriteManagerAdd(SpriteAcorn, 177*8, 5*8);
		SpriteManagerAdd(SpriteAcorn, 180*8, 8*8);
		SpriteManagerAdd(SpriteMushroom, 190*8, 13*8);
	    nut_region = 5;
	}
	// Up to 219:
	else if (spr_nutmeg->x > 1250 && spr_nutmeg->x <= 1500 && nut_region <= 5) {
		SpriteManagerAdd(EnemyButterfly, 198*8, 13*8);
		SpriteManagerAdd(SpriteAcorn, 207*8, 7*8);
		SpriteManagerAdd(EnemyButterfly, 216*8, 11*8);
	    nut_region = 6;
	}
	// Up to 250:
	else if (spr_nutmeg->x > 1500 && spr_nutmeg->x <= 1750 && nut_region <= 6) {
		//
	    nut_region = 7;
	}
	else if (spr_nutmeg->x > 1750 && spr_nutmeg->x <= 2000 && nut_region <= 7) {
		//
	    nut_region = 8;
	}
}