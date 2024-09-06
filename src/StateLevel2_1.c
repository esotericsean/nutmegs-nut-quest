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

static const UINT8 collision_tiles_level[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18, 0};

DECLARE_MUSIC (quickstart);
DECLARE_MUSIC (mushrooms);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_camera;

//nutmeg sprite region
extern UINT8 nut_region;

void Start_StateLevel2_1 (void) {
	level.hasTimer = true;
	levelStartCounter = 0;
	level.orientation = horizontal;
	level.isWaterLevel = false;
	level.iceTileMin = NO_ICE_TILES;
	level.iceTileMax = NO_ICE_TILES;

	SPRITES_8x16;

	pitdeathactive = true;

	nut_region = 0;
	deathmusicplayed = false;

	__critical { PlayMusic(quickstart, 1); }

	scroll_target = nutmeg_Add (4, 49);

	// TEST OUT A PLATFORM
	SpriteManagerAdd(SpritePlatform, 14*8, 18*8);

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level2_1map), &level2_1map, collision_tiles_level, 0);
	
	Hud_Init(false);
	cutscenemode = enabled;
	FlagPole_Init();
	levelEndCounter = 0;
	LevelStart_Init(7,11);

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel2_1 (void) {
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
				__critical { PlayMusic(mushrooms, 1); }
			}
		}

		LevelStart_Update();
		levelStartCounter++;
	}

	// no water on this level
	// Water_Animate();

	//animate flagpole
	FlagPole_Animate();
	
	if (levelbeat == true) {
		cutscenemode = enabled;
		cutscenewalkright = true;
		cutscenewalkleft = false;
	
		if (levelEndCounter >= 100) {
			SetState(StateOverworld);
		}

		if (levelEndCounter < 250) levelEndCounter++;
	}

	if (nutmeg.isDying == false)
	{
		if (spr_nutmeg->x >= 1992 && spr_nutmeg->x < 2000 && levelbeat == false ) {
			FlagPole_Activate(250,19);

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
		if (nut_region == 0){
			if (spr_nutmeg->x <= 250)
			{
				SpriteManagerAdd(EnemyButterfly, 12*8, 4*8);
				SpriteManagerAdd(SpriteAcorn, 47*8, 2*8);
				SpriteManagerAdd(SpriteAcorn, 54*8, 2*8);
				SpriteManagerAdd(EnemyBunny, 59*8, 13*8); //Bunny always 1 higher in y value
				nut_region = 1;
			}
		}
		// Up to 94:
		else if (nut_region == 1) {
			if (spr_nutmeg->x > 250)
			{
				SpriteManagerAdd(EnemyButterfly, 89*8, 9*8);
				SpriteManagerAdd(SpriteAcorn, 85*8, 12*8);
				SpriteManagerAdd(SpriteAcorn, 93*8, 12*8);
				nut_region = 2;
			}
		}
		// Up to 125:
		else if (nut_region == 2) {
			if (spr_nutmeg->x > 500)
			{
				SpriteManagerAdd(SpriteAcorn, 105*8, 5*8);
				SpriteManagerAdd(SpriteAcorn, 123*8, 5*8);
				nut_region = 3;
			}
		}
		// Up to 156:
		else if (nut_region == 3) {
			if (spr_nutmeg->x > 750)
			{
				SpriteManagerAdd(EnemyBunny, 132*8, 9*8);
				nut_region = 4;
			}
		}
		// Up to 188:
		else if (nut_region == 4) {
			if (spr_nutmeg->x > 1000)
			{
				SpriteManagerAdd(SpriteAcorn, 163*8, 10*8);
				SpriteManagerAdd(SpriteAcorn, 166*8, 8*8);
				SpriteManagerAdd(SpriteAcorn, 178*8, 14*8);
				nut_region = 5;
			}
		}
		// Up to 219:
		else if (nut_region == 5) {
			if (spr_nutmeg->x > 1250)
			{
				SpriteManagerAdd(EnemyButterfly, 216*8, 11*8);
				nut_region = 6;
			}
		}
		// Up to 250:
		else if (nut_region == 6) {
			if (spr_nutmeg->x > 1500) {
				SpriteManagerAdd(EnemyButterfly, 228*8, 10*8);
				nut_region = 7;
			}
		}
	}
}