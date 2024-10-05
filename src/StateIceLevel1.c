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

IMPORT_MAP (level3_1map);

static const LevelT levelInfo = {
	.isWaterLevel = false,
	.isSpikeLevel = false,
	.isPitDeathActive = true,

	// Min and max tile number for slippery ice tiles (set to NO_ICE_TILES for no ice)
	.iceTileMin = 2,
	.iceTileMax = 7,

	// vertical or horizontal Level
	.orientation = horizontal,

	// level timer info
	.hasTimer = true,
	.timer = 300,
	.timerclock = 0,
};

static const UINT8 collision_tiles[] = {2,3,4,5,6,7,16,17,0};
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
	{28, 11, SpriteAcorn, 0, 0, 0, 0, 0},
	{35, 10, SpriteAcorn, 0, 0, 0, 0, 0},
	{44, 6, SpriteAcorn, 0, 0, 0, 0, 0},
	{47, 7, SpriteAcorn, 0, 0, 0, 0, 0},
	{59, 6, SpriteAcorn, 0, 0, 0, 0, 0},
	{64, 4, SpriteAcorn, 0, 0, 0, 0, 0},
	{72, 4, SpriteAcorn, 0, 0, 0, 0, 0},
	{81, 11, SpriteAcorn, 0, 0, 0, 0, 0},
	{84, 5, SpriteAcorn, 0, 0, 0, 0, 0},
	{99, 8, SpriteAcorn, 0, 0, 0, 0, 0},
	{115, 10, SpriteAcorn, 0, 0, 0, 0, 0},
	{121, 2, SpriteAcorn, 0, 0, 0, 0, 0},
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

void Start_StateIceLevel1 (void) {
	levelStartCounter = 0;

	level = levelInfo;

	nut_region = 0;
	deathmusicplayed = false;
	
	SPRITES_8x16;
	
	PlayMusic(quickstart, 1);

	scroll_target = nutmeg_Add(4, 49);

	InitScrollTiles(0, &iceLevelTiles);
	InitScroll(BANK(level3_1map), &level3_1map, collision_tiles, collision_tiles_down);
	
	Hud_Init(false);

	cutscenemode = enabled;
	FlagPole_Init();
	levelEndCounter = 0;
	LevelStart_Init(6,4);

	levelActorPos = 0;
	AddActors();

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateIceLevel1 (void) 
{
	Hud_Update();
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

		LevelStart_Update();
		if (levelStartCounter < 105) levelStartCounter++;
	}

    Water_Animate();
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
    if ((spr_nutmeg->y < 2) || (spr_nutmeg->y > 65000))
	{
		spr_nutmeg->y = 2;
	}

	if (spr_nutmeg->x >= 984 && spr_nutmeg->x < 992 && levelbeat == false && nutmeg.isDying == false) {
		FlagPole_Activate(123,8);

		levelbeat = true;
		levelEndCounter = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
	}
}