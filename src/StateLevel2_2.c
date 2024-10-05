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

IMPORT_MAP (level2_2map);

static const UINT8 collision_tiles_level[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18, 0};

DECLARE_MUSIC (quickstart);
DECLARE_MUSIC (mushrooms);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;

//nutmeg sprite region
extern UINT8 nut_region;

static const LevelT levelInfo = {
	.isWaterLevel = false,
	.isSpikeLevel = false,

	// Min and max tile number for slippery ice tiles (set to NO_ICE_TILES for no ice)
	.iceTileMin = NO_ICE_TILES,
	.iceTileMax = NO_ICE_TILES,

	// vertical or horizontal Level
	.orientation = horizontal,

	// level timer info
	.hasTimer = true,
	.timer = 300,
	.timerclock = 0,
};


static void AddNut (UINT16 x, UINT16 y)
{
	x <<= 3;
	y <<= 3;
	Sprite *s = SpriteManagerAdd(SpriteAcorn, x, y);
	s->lim_x = 1000;
	s->lim_y = 1000;
}

void Start_StateLevel2_2(void) 
{
	level = levelInfo;
	
	levelStartCounter = 0;
	cutscenemode = enabled;
	levelEndCounter = 0;
	nut_region = 0;
	
	SPRITES_8x16;

	__critical { PlayMusic(quickstart, 1); }

	scroll_target = nutmeg_Add (8, 8);

	AddNut (61,4);
	AddNut(47,7);
	
	AddNut(46,30);
	AddNut(48,29);
	AddNut(47,32);

	AddNut(35,41);
	
	AddNut(58,42);
	AddNut(60,41);
	AddNut(59,44);

	AddNut(48,58);

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level2_2map), &level2_2map, collision_tiles_level, 0);
	
	Hud_Init();
	FlagPole_Init();
	LevelStart_Init(7,4);

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel2_2(void) 
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
				__critical { PlayMusic(mushrooms, 1); }
			}
		}

		LevelStart_Update();
		levelStartCounter++;
	}

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
		if (spr_nutmeg->x >= 456 && spr_nutmeg->x <= 464 
				&& spr_nutmeg->y >= 456 && spr_nutmeg->y <=472
				&& levelbeat == false ) {
			FlagPole_Activate(58, 59);

			levelbeat = true;
			levelEndCounter = 0;
			cutscenemode = enabled;
			cutscenewalkright = true;
		}
	
	}
}