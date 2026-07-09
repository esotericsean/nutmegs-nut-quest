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

IMPORT_MAP (level4map);

static const UINT8 collision_tiles_level4[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18, 0};
static const UINT8 collision_tiles_down_level4[] = {29,30,31,32,0};

DECLARE_MUSIC(quickstart);
DECLARE_MUSIC(mushrooms);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;


static const LevelT levelInfo = {
	.isWaterLevel = false,
	.isSpikeLevel = false,

	// Min and max tile number for slippery ice tiles (set to NO_ICE_TILES for no ice)
	.iceTileMin = NO_ICE_TILES,
	.iceTileMax = NO_ICE_TILES,

	// vertical or horizontal Level
	.orientation = horizontal,
	.isHorizontalGoalpost = false,

	// level timer info
	.hasTimer = true,
	.timer = 300,
	.timerclock = 0,
};

void Start_StateLevel4 (void) 
{
	level = levelInfo;

	levelStartCounter = 0;
	nut_region = 0;
	cutscenemode = enabled;
	levelEndCounter = 0;

	PlayMusic(quickstart, 1);

	scroll_target = nutmeg_Add(4, 49); 

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level4map), &level4map, collision_tiles_level4, collision_tiles_down_level4);

	Hud_Init();
	FlagPole_Init();
	LevelStart_Init(7,5);

	SPRITES_8x16;
	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel4 (void) 
{
	Hud_Update();
	
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
				PlayMusic(mushrooms, 1);
			}
		}

		if (levelStartCounter < 105) levelStartCounter++;
	}

	Water_Animate();

	FlagPole_Animate();

	if (levelbeat == true) {
		cutscenemode = enabled;
		cutscenewalkright = true;
		cutscenewalkleft = false;

		if (levelEndCounter >= LEVEL_END_DELAY) {
			StopMusic;
			SetState(StateOverworld);
		}

		if (levelEndCounter < 250) levelEndCounter++;
	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && levelbeat == false && nutmeg.isDying == false) {
		FlagPole_Activate(244, 13);
		levelbeat = true;
		levelEndCounter = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
	}

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