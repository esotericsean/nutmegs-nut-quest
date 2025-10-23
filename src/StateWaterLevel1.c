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

IMPORT_MAP (waterLevel1Map);

static const UINT8 collision_tiles[] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,0};
static const UINT8 collision_tiles_down[] = {0};

DECLARE_MUSIC (quickstart);
DECLARE_MUSIC (mushrooms);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;

typedef struct {
	UINT8 x;
	UINT8 y;
	UINT8 type; // sprite type
	UINT8 cd0;
	UINT8 cd1;
	UINT8 cd2;
	UINT8 cd3;
	UINT8 cd4;
} actorPosT;

static const actorPosT levelActors [] = 
{
	{14, 3, SpriteAcorn, 0, 0, 0, 0, 0},
	{45, 7, SpriteAcorn, 0, 0, 0, 0, 0},
	{47, 5, SpriteAcorn, 0, 0, 0, 0, 0},
	{47, 9, SpriteAcorn, 0, 0, 0, 0, 0},
	{51, 7, SpriteAcorn, 0, 0, 0, 0, 0},
	{71, 10, SpriteAcorn, 0, 0, 0, 0, 0},
	{100, 16, SpriteAcorn, 0, 0, 0, 0, 0},
	{136, 12, SpriteAcorn, 0, 0, 0, 0, 0},
	{138, 13, SpriteAcorn, 0, 0, 0, 0, 0},
	{161, 15, SpriteAcorn, 0, 0, 0, 0, 0},
	{194, 1, SpriteAcorn, 0, 0, 0, 0, 0},
	{208, 13, SpriteAcorn, 0, 0, 0, 0, 0},
};

#define NUM_ACTORS (sizeof (levelActors) / sizeof(levelActors[0]))
static UINT8 levelActorPos;

static void AddActor (actorPosT *a)
{
	Sprite *s = SpriteManagerAdd(a->type, (UINT16)(a->x) << 3, (UINT16)(a->y) << 3);
	s->lim_x = 400;
	s->lim_y = 300;
	s->custom_data[0] = a->cd0;
	s->custom_data[1] = a->cd1;
	s->custom_data[2] = a->cd2;
	s->custom_data[3] = a->cd3;
	s->custom_data[4] = a->cd4;
}

static void AddActors (void)
{
	UINT16 xpos = spr_nutmeg->x;
	UINT8 x = xpos >> 3;

	if (spr_nutmeg->x > 60000)
	{ 
		x = 0;
	}

	while ((levelActorPos < NUM_ACTORS) && (levelActors[levelActorPos].x < x + 25))
	{
		AddActor (&levelActors[levelActorPos]);
		levelActorPos ++;
	}
}


static const LevelT levelInfo = {
	.isWaterLevel = true,
	.isSpikeLevel = true,

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


void Start_StateWaterLevel1 (void) {
	level = levelInfo;

	levelStartCounter = 0;
	cutscenemode = enabled;
	levelEndCounter = 0;
	levelActorPos = 0;	

	SPRITES_8x16;
	
	PlayMusic(quickstart, 1);

	scroll_target = nutmeg_Add(4, 49);

	InitScrollTiles(0, &waterLevelTiles);
	InitScroll(BANK(waterLevel1Map), &waterLevel1Map, collision_tiles, collision_tiles_down);
	
	Hud_Init();

	
	FlagPole_Init();
	LevelStart_Init(6,4);

	AddActors();

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateWaterLevel1 (void) 
{
	Hud_Update();
	// Freeze level updates while Nutmeg is in a death sequence to avoid
	// interfering music/state changes that can retrigger quickdeath
	if (nutmeg.isDying) {
		return;
	}
	AddActors();
	
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

	// Water_Animate();
	FlagPole_Animate();

	if (levelbeat == true) {
		cutscenemode = enabled;
		cutscenewalkright = true;
		cutscenewalkleft = false;
	
		if (levelEndCounter >= 100) {
			SetState(StateOverworld);
		}

		levelEndCounter++;
	}

    // stop nutmeg from moving off the top of the screen
    if (spr_nutmeg->y < 2)
    {
        spr_nutmeg->y = 2;
    }

    if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && levelbeat == false && nutmeg.isDying == false)
    {
        // activate when crossing pole regardless of Y
        FlagPole_Activate(244,13);

        levelbeat = true;
        levelEndCounter = 0;
        cutscenemode = enabled;
        cutscenewalkright = true;
    }
}