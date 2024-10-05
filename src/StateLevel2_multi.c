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

IMPORT_MAP (level2_multi_1_map);
IMPORT_MAP (level2_multi_2_map);
IMPORT_MAP (level2_multi_3_map);

static const UINT8 collision_tiles_level[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18, 0};

DECLARE_MUSIC (quickstart);
DECLARE_MUSIC (mushrooms);

extern Sprite * spr_nutmeg;

uint16_t exitTopX;
uint16_t exitTopY;
uint16_t exitBottomX;
uint16_t exitBottomY;

uint8_t roomNumber;

uint16_t mapRight;
bool stopMapLeft;
bool stopMapRight;


static const LevelT levelInfo = {
	.isWaterLevel = false,
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

void InitGeneralRoomVars(void)
{
	SpriteManagerReset();

	level = levelInfo;

	levelbeat = false;
	levelStartCounter = 0;
	cutscenemode = enabled;
	levelEndCounter = 0;

	SPRITES_8x16;

	stopMapLeft = true;
	stopMapRight = true;
}

void SetExit (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	exitTopX = x1 * 8;
	exitTopY = y1 * 8;
	exitBottomX = x2 * 8;
	exitBottomY = y2 * 8;
}

void SMAdd (uint8_t sn, uint16_t x, uint16_t y)
{
	Sprite *s = SpriteManagerAdd(sn, x, y);
	s->lim_x = 5000; 
	s->lim_y = 5000; 
}

void StartRoom1 (void)
{
	InitGeneralRoomVars();
	mapRight = 128*8;
	SetExit (127, 0, 130, 30);
	__critical { PlayMusic(quickstart, 1); }
	

	//start the game off with a bow (full health)
	scroll_target = nutmeg_Add(4, 49);


	SMAdd(EnemyButterfly, 23*8, 10*8);
	SMAdd(EnemyBunny, 35*8, 14*8); 
	
	SMAdd(EnemyBunny, 63*8, 14*8); 
	SMAdd (SpriteAcorn, 66*8, 3*8);

	SMAdd(EnemyButterfly, 69*8, 10*8);
	SMAdd (SpriteAcorn, 72*8, 2*8);

	SMAdd(EnemyButterfly, 75*8, 8*8);
	SMAdd (SpriteAcorn, 78*8, 1*8);

	SMAdd(EnemyButterfly, 82*8, 6*8);
	SMAdd (SpriteAcorn, 85*8, 0*8);

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level2_multi_1_map), &level2_multi_1_map, collision_tiles_level, 0);

	Hud_Init();
	FlagPole_Init();
	
	LevelStart_Init(7,4);

	SHOW_SPRITES;
	SHOW_BKG;
	DISPLAY_ON;
}


void StartRoom2 (void)
{
	InitGeneralRoomVars();
	mapRight = 87*8;

	SetExit (70, 21, 90, 22);

	scroll_target = nutmeg_Add(4, 49);

	SMAdd(EnemyBunny, 23*8, 14*8); 
	SMAdd(EnemyButterfly, 27*8, 10*8);
	SMAdd(EnemyButterfly, 33*8, 8*8);
	SMAdd(EnemyButterfly, 40*8, 6*8);

	SMAdd(EnemyBirdy, 71*8, 10*8);
	SMAdd(EnemyBirdy, 80*8, 13*8);
	SMAdd(EnemyButterfly, 87*8, 10*8);

	SMAdd (SpriteAcorn, 14*8, 13*8);
	SMAdd (SpriteAcorn, 27*8, 11*8);
	
	SMAdd (SpriteAcorn, 71*8, 14*8);
	SMAdd (SpriteAcorn, 75*8, 17*8);
	
	SMAdd (SpriteAcorn, 78*8, 3*8);
	SMAdd (SpriteAcorn, 82*8, 3*8);

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level2_multi_2_map), &level2_multi_2_map, collision_tiles_level, 0);

	Hud_Init();
	FlagPole_Init();
	
	SHOW_SPRITES;
	SHOW_BKG;
	DISPLAY_ON;
}


void StartRoom3 (void)
{
	InitGeneralRoomVars();
	level.orientation = vertical;
	cutscenemode = false;

	mapRight = 19*8;
	SetExit (14, 30, 15, 37);

	scroll_target = nutmeg_Add(6*8, 65535-16);

	SMAdd (SpriteAcorn, 1*8, 1*8);
	SMAdd (SpriteAcorn, 17*8, 8*8);
	SMAdd (SpriteAcorn, 12*8, 17*8);
	SMAdd (SpriteAcorn, 13*8, 18*8);
	SMAdd (SpriteAcorn, 2*8, 28*8);

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level2_multi_3_map), &level2_multi_3_map, collision_tiles_level, 0);

	Hud_Init();
	FlagPole_Init();
	
	SHOW_SPRITES;
	SHOW_BKG;
	DISPLAY_ON;
}

#define MAX_ROOM_NUMBER (3)

void NextRoom (void)
{
	display_off();
	roomNumber ++;
	if (roomNumber > MAX_ROOM_NUMBER)
	{
		SetState(StateOverworld);
		return;
	}

	if (roomNumber == 1)
	{
		StartRoom1();
	}
	else if (roomNumber == 2)
	{
		StartRoom2();
	}
	else 
	{
		StartRoom3();
	}
}

void Start_StateLevel2_multi (void) {
	roomNumber = 0;
	NextRoom();
}

void Update_StateLevel2_multi (void) {
	Hud_Update();

	if (cutscenemode == enabled) {
		
		if (levelbeat == true) {
			if (levelEndCounter >= 100) {
				NextRoom();
				return;
			}
		 	levelEndCounter++;
		}	
		else
		{
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
				if ((levelbeat == false) && (roomNumber == 1)) {
					__critical { PlayMusic(mushrooms, 1); }
				}
			}

			levelStartCounter++;
		}
	}
	else
	{
		if (stopMapLeft && (spr_nutmeg->x > 60000))
		{
			spr_nutmeg->x = 0;
		}
		if (stopMapRight && (spr_nutmeg->x > mapRight))
		{
			spr_nutmeg->x = mapRight;
		}
	}

	// no water on this level
	// Water_Animate();

	//animate flagpole
	if (roomNumber == 3)
	{
		FlagPole_Animate();
	}

	if (nutmeg.isDying == false)
	{
		if (nutmeg_isInsideXY(exitTopX,exitTopY,exitBottomX,exitBottomY) && levelbeat == false)
		{
			levelEndCounter = 100;
			if (roomNumber == MAX_ROOM_NUMBER)
			{
				FlagPole_Activate(14,38);
				// this one gets a full end cutscene
				levelEndCounter = 0;
			}
			levelbeat = true;
			cutscenemode = enabled;
			cutscenewalkright = true;
		}
	}
}