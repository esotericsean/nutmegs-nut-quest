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
extern Sprite * spr_nutmegbow;
extern Sprite * spr_camera;

void Start_StateLevel2() {
	level2counter = 0;

	levelorientation = horizontal;
	SPRITES_8x16;

	nut_region = 0;
	pitdeathactive = true;

	deathmusicplayed = false;

	PlayMusic(quickstart, 1);

	//if health is full, add the bow
	if (hasbow == true) { spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, 4, 49); }
	scroll_target = spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 4, 49); //36
	
	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level2map), &level2map, collision_tiles_level2, collision_tiles_down_level2);
	Hud_Init(false);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	FlagPole_Init();
	endlevel_counter2 = 0;
	LevelStart_Init(7,5);

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
		else if (level2counter == 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		else if (level2counter == 100) {
			cutscenemode = disabled;

			if (levelbeat == false) {
				PlayMusic(mushrooms, 1);
			}
		}

		LevelStart_Update();
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
		FlagPole_Activate (244,13);
		
		levelbeat = true;
		endlevel_counter2 = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
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