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

IMPORT_MAP (level1_platformmap);

static const UINT8 collision_tiles[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,0};
static const UINT8 collision_tiles_down[] = {29,30,31,32,0};

DECLARE_MUSIC (quickstart);
DECLARE_MUSIC (mushrooms);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;

static const LevelT levelInfo = {
	.isWaterLevel = false,
	.isSpikeLevel = false,
	.isPitDeathActive = true,

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

static const nutPosT levelNuts [] = 
{
	{22, 1},
	{37, 6},
	{74, 1},
	{78, 3},
	{93, 13},
	{117, 2},
	{144, 10},
	{154, 1},
	{164, 13},
	{227, 7},
	{0,0}
};

#define NUM_NUTS (sizeof (levelNuts) / sizeof(levelNuts[0]))
static UINT8 levelNutPos;

static void AddNut (UINT16 x, UINT16 y)
{
	x <<= 3;
	y <<= 3;
	Sprite *s = SpriteManagerAdd(SpriteAcorn, x, y);
	s->lim_x = 400;
	s->lim_y = 300;
}

static void AddNuts (void)
{
	UINT16 xpos = spr_nutmeg->x;
	UINT8 x = xpos >> 3;

	if (spr_nutmeg->x > 60000)
	{ 
		x = 0;
	}

	while ((levelNutPos < NUM_NUTS) && (levelNuts[levelNutPos].x < x + 25))
	{
		AddNut (levelNuts[levelNutPos].x, levelNuts[levelNutPos].y);
		levelNutPos ++;
	}
}

void Start_StateLevel1_platform (void) {

	level = levelInfo;

	levelStartCounter = 0;
	SPRITES_8x16;

	nut_region = 0;
	deathmusicplayed = false;

	PlayMusic(quickstart, 1);

	//start the game off with a bow (full health)
	scroll_target = nutmeg_Add(4, 49);

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level1_platformmap), &level1_platformmap, collision_tiles, collision_tiles_down);
	
	Hud_Init(false);
	cutscenemode = enabled;
	FlagPole_Init();
	levelEndCounter = 0;
	LevelStart_Init(6,4);


	Sprite *s = SpriteManagerAdd(SpritePlatform, 16*8, 3*8);
	Platform_Setup(s, -1, 1, PLATFORM_TYPE_BACK_AND_FORTH, 7*8);

	s = SpriteManagerAdd (SpritePlatform, 52*8, 16*8);
	Platform_Setup(s, 1, 0, PLATFORM_TYPE_BACK_AND_FORTH, 26*8);

	s = SpriteManagerAdd (SpritePlatform, 65*8, 14*8);
	Platform_Setup(s, 0, -1, PLATFORM_TYPE_BACK_AND_FORTH, 10*8);

	s = SpriteManagerAdd (SpritePlatform, 92*8, 16*8);
	Platform_Setup(s, 1, -1, PLATFORM_TYPE_BACK_AND_FORTH, 13*8);

	// upward platforms
	s = SpriteManagerAdd (SpritePlatform, 143*8, 5*8);
	Platform_Setup(s, 0, -1, PLATFORM_TYPE_WRAP_TOP_BOTTOM, 255);

	s = SpriteManagerAdd (SpritePlatform, 153*8, 9*8);
	Platform_Setup(s, 0, -1, PLATFORM_TYPE_WRAP_TOP_BOTTOM, 255);

	s = SpriteManagerAdd (SpritePlatform, 163*8, 13*8);
	Platform_Setup(s, 0, -1, PLATFORM_TYPE_WRAP_TOP_BOTTOM, 255);

	// downward platforms
	s = SpriteManagerAdd (SpritePlatform, 182*8, 4*8);
	Platform_Setup(s, 0, 1, PLATFORM_TYPE_WRAP_TOP_BOTTOM, 255);

	s = SpriteManagerAdd (SpritePlatform, 192*8, 0*8);
	Platform_Setup(s, 0, -1,PLATFORM_TYPE_WRAP_TOP_BOTTOM, 255);
	
	levelNutPos = 0;
	AddNuts();

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel1_platform (void) {
	Hud_Update();
	AddNuts();
	
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

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && levelbeat == false && nutmeg.isDying == false) {
		FlagPole_Activate(244,13);

		levelbeat = true;
		levelEndCounter = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
	}
}