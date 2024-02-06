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
#include "LevelStart.h"

IMPORT_MAP (level4map);

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


void Start_StateLevel4() {
	level4counter = 0;
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
	Hud_Init(false);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	FlagPole_Init();
	LevelStart_Init(7,5);
	endlevel_counter4 = 0;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel4() {
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
		if (level4counter == 0) {
			cutscenewalkright = true;
		}
		else if (level4counter == 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		else if (level4counter == 100) {
			cutscenemode = disabled;

			if (levelbeat == false) {
				PlayMusic(mushrooms, 1);
			}
		}

		LevelStart_Update();
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