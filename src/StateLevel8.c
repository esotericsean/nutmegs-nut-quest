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

IMPORT_MAP (level8map);

UINT16 level8counter = 0;
UINT8 endlevel_counter8 = 0;

const UINT8 collision_tiles_level8[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
const UINT8 collision_tiles_down_level8[] = {29,30,31,32,0};

DECLARE_MUSIC(quickstart);
DECLARE_MUSIC(mushrooms);
DECLARE_MUSIC(quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_camera;


void Start_StateLevel8() {
	level8counter = 0;
	levelorientation = horizontal;
	SPRITES_8x16;

	nut_region = 0;
	pitdeathactive = true;

	deathmusicplayed = false;

	PlayMusic(quickstart, 1);
	
	//if health is full, add the bow
	if (hasbow == true) { SpriteManagerAdd(SpriteNutmegBow, 4, 15*8); }
	scroll_target = spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 4, 15*8); //36

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level8map), &level8map, collision_tiles_level8, collision_tiles_down_level8);
	Hud_Init(false);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	FlagPole_Init();
	LevelStart_Init(7, 13);
	endlevel_counter8 = 0;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel8() {
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
		if (level8counter == 0) {
			cutscenewalkright = true;
		}
		else if (level8counter == 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		else if (level8counter == 100) {
			cutscenemode = disabled;

			if (levelbeat == false) {
				PlayMusic(mushrooms, 1);
			}
		}

		LevelStart_Update();
		if (level8counter < 105) level8counter++;
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

		if (endlevel_counter8 >= 100) {
			//endlevel_counter8 = 0;
			//cutscenewalkleft = false;
			//cutscenewalkright = false;
			//cutscenemode = disabled;

			SetState(StateOverworld1);
		}

		if (endlevel_counter8 < 250) endlevel_counter8++;

		
	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && levelbeat == false && nutmeg_death == false) {
		FlagPole_Activate (244, 18);
		levelbeat = true;
		endlevel_counter8 = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
	}

	// 0-63:
	if (spr_nutmeg->x > 0 && spr_nutmeg->x <= 250 && nut_region <= 0) {
		SpriteManagerAdd(SpriteAcorn, 11*8+4, 0*8+4);
		SpriteManagerAdd(SpriteAcorn, 37*8, 13*8);
		SpriteManagerAdd(SpriteMushroom, 53*8, 18*8);
		SpriteManagerAdd(EnemyBirdy, 80*8, 19*8);
		SpriteManagerAdd(SpriteAcorn, 80*8, 11*8);
		SpriteManagerAdd(EnemyBirdy, 89*8, 19*8);
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_nutmeg->x > 250 && spr_nutmeg->x <= 500 && nut_region <= 1) {
		SpriteManagerAdd(SpriteAcorn, 58*8, 14*8);
    	nut_region = 2;
	}
	// Up to 125:
	else if (spr_nutmeg->x > 500 && spr_nutmeg->x <= 750 && nut_region <= 2) {
		SpriteManagerAdd(SpriteAcorn, 100*8+4, 11*8);
		SpriteManagerAdd(SpriteAcorn, 102*8+4, 15*8+4);
		SpriteManagerAdd(EnemyBunny, 110*8, 14*8);
	    nut_region = 3;
	}
	// Up to 156:
	else if (spr_nutmeg->x > 750 && spr_nutmeg->x <= 1000 && nut_region <= 3) {
		SpriteManagerAdd(SpriteAcorn, 125*8, 17*8);
		SpriteManagerAdd(SpriteAcorn, 155*8, 1*8);
	    nut_region = 4;
	}
	// Up to 188:
	else if (spr_nutmeg->x > 1000 && spr_nutmeg->x <= 1250 && nut_region <= 4) {
		SpriteManagerAdd(SpriteAcorn, 157*8, 1*8);
		SpriteManagerAdd(SpriteAcorn, 159*8, 2*8);
		SpriteManagerAdd(EnemyBirdy, 159*8+4, 18*8);
		SpriteManagerAdd(SpriteAcorn, 161*8, 4*8);
		SpriteManagerAdd(EnemyButterfly, 177*8, 11*8);
		SpriteManagerAdd(EnemyBunny, 185*8, 18*8);
	    nut_region = 5;
	}
	// Up to 219:
	else if (spr_nutmeg->x > 1250 && spr_nutmeg->x <= 1500 && nut_region <= 5) {
		SpriteManagerAdd(SpriteAcorn, 190*8, 8*8);
		SpriteManagerAdd(SpriteAcorn, 192*8, 15*8);
		SpriteManagerAdd(SpriteAcorn, 198*8, 16*8);
		SpriteManagerAdd(SpriteAcorn, 200*8, 6*8);
		SpriteManagerAdd(EnemyButterfly, 212*8, 13*8);
		SpriteManagerAdd(EnemyBunny, 220*8, 18*8);
	    nut_region = 6;
	}
	// Up to 250:
	else if (spr_nutmeg->x > 1500 && spr_nutmeg->x <= 1750 && nut_region <= 6) {
		SpriteManagerAdd(SpriteAcorn, 211*8, 4*8);
		SpriteManagerAdd(EnemyBirdy, 235*8, 14*8);
	    nut_region = 7;
	}
	else if (spr_nutmeg->x > 1750 && spr_nutmeg->x <= 2000 && nut_region <= 7) {
	    nut_region = 8;
	}
}