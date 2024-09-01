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
#include "SpriteNutmeg.h"

IMPORT_MAP (level3map);

static const UINT8 collision_tiles_level3[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
static const UINT8 collision_tiles_down_level3[] = {29,30,31,32,0};

DECLARE_MUSIC(quickstart);
DECLARE_MUSIC(mushrooms);
DECLARE_MUSIC(quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_camera;


void Start_StateLevel3 (void)
{
	levelStartCounter = 0;
	levelEndCounter = 0;
	level.orientation = vertical;
	level.isWaterLevel = false;
	

	nut_region = 0;
	pitdeathactive = false;

	deathmusicplayed = false;

	PlayMusic(quickstart, 1);

	scroll_target = nutmeg_Add(4, 49);

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level3map), &level3map, collision_tiles_level3, collision_tiles_down_level3);
	Hud_Init(false);

	cutscenemode = enabled;
	
	FlagPole_Init();
	LevelStart_Init(7,5);

	SPRITES_8x16;
	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel3 (void) 
{
	Hud_Update();

	if (timerlevel == 0) 
	{ 
		nutmeg.isDying = true;
	}

	if (nutmeg.isDying == true) {
		if (deathmusicplayed == false) {
			__critical { PlayMusic(quickdeath, 1); }
			deathmusicplayed = true;
		}

		if (nutmeg.deathtimer >= 125) {
			if (GameOver == true) {
				SetState(StateGameOver);
			}
			else if (GameOver == false) {
				nutmeg_setupNewLife();
				SetState(StateOverworld); // change to correct world
			}
			return;
		}

		nutmeg.deathtimer++;
	}
	
	if (cutscenemode == enabled) {
		//Level Start!
		//Make Nutmeg Walk In
		if (levelStartCounter == 0) {
			cutscenewalkright = true;
		}
		else if (levelStartCounter == 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		else if (levelStartCounter == 100) {
			cutscenemode = disabled;

			if (levelbeat == false) {
				PlayMusic(mushrooms,  1);
			}
		}

		LevelStart_Update();			
		if (levelStartCounter < 105) levelStartCounter++;
	}

	Water_Animate();

	FlagPole_Animate();
	
	if (levelbeat == true) {
		cutscenemode = enabled;
		
		//change for this level because it's vertical not horizontal!!!
		if (spr_nutmeg->x > 248) {
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

		if (levelEndCounter >= 100) {
			//levelEndCounter = 0;
			//cutscenewalkleft = false;
			//cutscenewalkright = false;
			//cutscenemode = disabled;

			SetState(StateOverworld);
		}

		if (levelEndCounter < 250) levelEndCounter++;

	}

	if (spr_nutmeg->x >= 256 && spr_nutmeg->x < 280 && spr_nutmeg->y > 904 && spr_nutmeg->y < 968 && levelbeat == false && nutmeg.isDying == false) {
		FlagPole_Activate(32,120);
		levelbeat = true;
		levelEndCounter = 0;
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
        SetState(StateOverworld);
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

	// * * * * * * * * * * * * * * * * * * * * * * * * //
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	//  Need to update this section to spr_nutmeg->y  //
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	// * * * * * * * * * * * * * * * * * * * * * * * * //

	// 0-63:
	if (spr_nutmeg->y > 0 && spr_nutmeg->y <= 125 && nut_region <= 0) {
		SpriteManagerAdd(EnemyBunny, 16*8, 13*8);
		SpriteManagerAdd(SpriteAcorn, 28*8, 6*8);
		SpriteManagerAdd(SpriteAcorn, 28*8, 10*8);
		SpriteManagerAdd(SpriteAcorn, 28*8, 14*8);
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_nutmeg->y > 125 && spr_nutmeg->y <= 250 && nut_region <= 1) {
		SpriteManagerAdd(EnemyTopSpike, 8*8, 28*8);
		//SpriteManagerAdd(EnemyTopSpike, 20*8, 28*8);
		SpriteManagerAdd(EnemyTopSpike, 18*8, 28*8);
    	nut_region = 2;
	}
	// Up to 125:
	else if (spr_nutmeg->y > 250 && spr_nutmeg->y <= 375 && nut_region <= 2) {
		SpriteManagerAdd(EnemyRockith, 20*8, 33*8);
		SpriteManagerAdd(EnemyTopSpike, 12*8, 38*8);
		SpriteManagerAdd(EnemyBatty, 26*8, 40*8);
	    nut_region = 3;
	}
	// Up to 156:
	else if (spr_nutmeg->y > 375 && spr_nutmeg->y <= 500 && nut_region <= 3) {
		SpriteManagerAdd(EnemyButterfly, 10*8, 57*8);
		SpriteManagerAdd(SpriteAcorn, 6*8, 59*8);
	    nut_region = 4;
	}
	// Up to 188:
	else if (spr_nutmeg->y > 500 && spr_nutmeg->y <= 625 && nut_region <= 4) {
	    SpriteManagerAdd(SpriteAcorn, 28*8, 66*8);
		SpriteManagerAdd(SpriteAcorn, 28*8, 70*8);
		SpriteManagerAdd(SpriteAcorn, 28*8, 74*8);
		SpriteManagerAdd(SpriteAcorn, 28*8, 78*8);
		nut_region = 5;
	}
	// Up to 219:
	else if (spr_nutmeg->y > 625 && spr_nutmeg->y <= 750 && nut_region <= 5) {
		SpriteManagerAdd(EnemyRockith, 20*8, 92*8);
		SpriteManagerAdd(SpriteAcorn, 4*8, 79*8);
		SpriteManagerAdd(SpriteAcorn, 4*8, 83*8);
		SpriteManagerAdd(SpriteAcorn, 4*8, 87*8);
		//SpriteManagerAdd(SpriteAcorn, 4*8, 91*8);
	    nut_region = 6;
	}
	// Up to 250:
	else if (spr_nutmeg->y > 750 && spr_nutmeg->y <= 875 && nut_region <= 6) {
		SpriteManagerAdd(SpriteAcorn, 29*8, 103*8);
		SpriteManagerAdd(SpriteAcorn, 26*8, 106*8);
		SpriteManagerAdd(SpriteAcorn, 23*8, 109*8);
	    nut_region = 7;
	}
	else if (spr_nutmeg->y > 875 && spr_nutmeg->y <= 1000 && nut_region <= 7) {
		SpriteManagerAdd(EnemyBunny, 16*8, 120*8);
	    nut_region = 8;
	}
}