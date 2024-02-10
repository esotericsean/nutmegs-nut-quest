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

IMPORT_MAP (level2_1map);

static UINT16 levelCounter = 0;
static UINT8 endlevel_counter = 0;

static const UINT8 collision_tiles_level[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18, 0};

DECLARE_MUSIC (quickstart);
DECLARE_MUSIC (mushrooms);
DECLARE_MUSIC (quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_nutmegbow;
extern Sprite * spr_camera;

//nutmeg sprite region
extern UINT8 nut_region;

void Start_StateLevel2_1() {
	levelCounter = 0;
	levelorientation = horizontal;

	SPRITES_8x16;

	pitdeathactive = true;

	nut_region = 0;
	deathmusicplayed = false;

	__critical { PlayMusic(quickstart, 1); }

	//start the game off with a bow (full health)
	if (lostbow == false) {
		spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, 4, 49);
	}
	scroll_target = spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 4, 49);

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level2_1map), &level2_1map, collision_tiles_level, 0);
	
	Hud_Init(false);
	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	FlagPole_Init();
	endlevel_counter = 0;
	LevelStart_Init(7,9);

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel2_1() {
	Hud_Update();

	if (timerlevel == 0) {
		while (nutmeg_death == false)
		{
			nutmeg_hit();
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
		if (levelCounter == 0) {
			cutscenewalkright = true;
		}
		else if (levelCounter == 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		else if (levelCounter == 100) {
			cutscenemode = disabled;

			if (levelbeat == false) {
				__critical { PlayMusic(mushrooms, 1); }
			}
		}

		LevelStart_Update();
		levelCounter++;
	}

	// no water on this level
	// Water_Animate();

	//animate flagpole
	FlagPole_Animate();
	
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
			SetState(StateOverworld1);
		}

		if (endlevel_counter < 250) endlevel_counter++;
	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && levelbeat == false && nutmeg_death == false) {
		FlagPole_Activate(244,13);

		levelbeat = true;
		endlevel_counter = 0;
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
	if (spr_nutmeg->x <= 250 && nut_region == 0) {
		SpriteManagerAdd(EnemyButterfly, 12*8, 4*8);
		SpriteManagerAdd(SpriteAcorn, 47*8, 2*8);
		SpriteManagerAdd(SpriteAcorn, 54*8, 2*8);
		SpriteManagerAdd(EnemyBunny, 59*8, 13*8); //Bunny always 1 higher in y value
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_nutmeg->x > 250 && nut_region == 1) {
		SpriteManagerAdd(EnemyButterfly, 89*8, 9*8);
		SpriteManagerAdd(SpriteAcorn, 85*8, 12*8);
		SpriteManagerAdd(SpriteAcorn, 93*8, 12*8);
    	nut_region = 2;
	}
	// Up to 125:
	else if (spr_nutmeg->x > 500 && nut_region == 2) {
		SpriteManagerAdd(SpriteAcorn, 105*8, 5*8);
		SpriteManagerAdd(SpriteAcorn, 123*8, 5*8);
	    nut_region = 3;
	}
	// Up to 156:
	else if (spr_nutmeg->x > 750 && nut_region == 3) {
		SpriteManagerAdd(EnemyBunny, 132*8, 9*8);
	    nut_region = 4;
	}
	// Up to 188:
	else if (spr_nutmeg->x > 1000 && nut_region == 4) {
		SpriteManagerAdd(SpriteAcorn, 163*8, 10*8);
		SpriteManagerAdd(SpriteAcorn, 166*8, 8*8);
		SpriteManagerAdd(SpriteAcorn, 178*8, 14*8);
	    nut_region = 5;
	}
	// Up to 219:
	else if (spr_nutmeg->x > 1250 && nut_region == 5) {
		SpriteManagerAdd(EnemyButterfly, 216*8, 11*8);
	    nut_region = 6;
	}
	// Up to 250:
	else if (spr_nutmeg->x > 1500 && nut_region == 6) {
		SpriteManagerAdd(EnemyButterfly, 228*8, 10*8);
	    nut_region = 7;
	}
}