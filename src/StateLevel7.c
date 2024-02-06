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

IMPORT_MAP (level7map);

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


void Start_StateLevel7() {
	level7counter = 0;
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
	Hud_Init(false);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	FlagPole_Init();
	LevelStart_Init(7,5);

	endlevel_counter7 = 0;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel7() {
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
		if (level7counter == 0) {
			cutscenewalkright = true;
		}
		else if (level7counter == 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		else if (level7counter == 100) {
			cutscenemode = disabled;

			if (levelbeat == false) {
				PlayMusic(mushrooms, 1);
			}
		}

		LevelStart_Update();
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