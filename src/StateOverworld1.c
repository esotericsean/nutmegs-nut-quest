#include "Banks/SetAutoBank.h"

#include "BankManager.h"
#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "../src/GlobalVars.h"

IMPORT_MAP (overworld1map);
IMPORT_MAP (overworld2map);

// OVerworld map scene

/////////////////////////////////////////////////////
//												   //
//					 ~ World 1 ~				   //
//				  The Acorn Kingdom				   //
//												   //
/////////////////////////////////////////////////////

static UINT8 waterAnimCounter = 0; // water animation counter

UINT8 walkCounter = 0;
UINT8 bossflash = 0;
UINT8 W1LevelSelection; 		// nutmeg starts at level 1
								// level 0 is the tree
								// mushroom is level 4
bool levelbeat;

const unsigned char overworld1_tree[] = {
	0x36,0x00,0x5b,0x00,0xff,0x00,0xbb,0x00,
	0x6e,0x00,0x0c,0x1c,0x04,0x1c,0x26,0x3e
};
const unsigned char overworld1_mushroom[] = {
	0xff,0x00,0xff,0x3e,0xc1,0x6f,0xc1,0x7b,
	0xe1,0x7f,0xc3,0x22,0xeb,0x2a,0xef,0x3e
};
const unsigned char overworld1_boss1[] = {
	0x00,0x00,0x1c,0x1c,0x3e,0x22,0x73,0x4d,
	0x61,0x5f,0x61,0x5f,0x32,0x2e,0x1c,0x1c
};
const unsigned char overworld1_boss2[] = {
	0x00,0x00,0x1c,0x1c,0x22,0x3e,0x4d,0x73,
	0x5f,0x61,0x5f,0x61,0x2e,0x32,0x1c,0x1c
};

UINT8 level_current = 0;
UINT8 level_next = 0;
UINT8 level_max = 0;

UINT8 collision_tiles_overworld1[] = {0};

DECLARE_MUSIC(acornkingdom);

//List of tiles that will be animated
static const unsigned char overworld1_water1[] = {
	0xff,0x00,0xff,0x00,0x9f,0x00,0x6f,0x00,
	0xff,0x00,0xf9,0x00,0xf6,0x00,0xff,0x00
};

static const unsigned char overworld1_water2[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0x9f,0x00,
	0x69,0x00,0xf6,0x00,0xff,0x00,0xff,0x00
};

static Sprite *spr_tinyNutmeg;

// index = level, value = stateEnum
static UINT8 StageForLevel [] = {0, 1, 2, 5, 6, 7, 8, 9, 10, 11};

 // index = stateEnum, value = level
static UINT8 LevelForStage [] = {0, 1, 2, 0, 0, 3, 4, 5, 6, 7, 8, 9};

typedef struct mapStepT {
	const UINT8 x;
	const UINT8 y;
	const UINT8 level;
} mapStepT;

// map steps for the currnent overworld map 
static const mapStepT * currentMapSteps;

// are we moving the player to a different level?
bool automove = false;
UINT8 moveCount = 0;

// The map step the player is currently moving towards (if automove is on)
static const mapStepT * movingToStep;

#define TILE_0 (0x29)

static const mapStepT steps_ow1 [] = {
	{4, 6, 0},
	{5, 6, 0},
	{6, 6, 1}, // This is level 1 pos
	{6, 7, 1},
	{6, 8, 2}, // this is level 2 pos
	{7, 8, 2},
	{8, 8, 2},
	{9, 8, 3}, // level 3
	{9, 9, 3},
	{9, 10, 4}, // level 4
	{10, 10, 4},
	{11, 10, 4},
	{12, 10, 5}, // level 5
	{12, 9, 5},
	{12, 8, 5},
	{12, 7, 5},
	{12, 6, 6}, // level 6
	{13, 6, 6},
	{14, 6, 6},
	{15, 6, 7}, // level 7
	{15, 7, 7},
	{15, 8, 7},
	{15, 9, 8}, // level 8
	{15, 10, 8},
	{15, 11, 8},
	{15, 12, 9}, // boss 1
	{16, 12, 9},
	{17, 12, 9},
	{18, 12, 9},
	{19, 12, 9},
	{20, 12, 10}, // go off the screen
};


static const mapStepT steps_ow2 [] = {
	{0, 12, 9},
	{1, 12, 9},
	{2, 12, 9},
	{3, 12, 10},
	{4, 12, 10},
	{5, 12, 10},
	{6, 12, 11},
	{7, 12, 11},
	{8, 12, 11},
	{9, 12, 12},
	{10, 12, 12},
	{11, 12, 12},
	{12, 12, 13},
	{13, 12, 13},
	{14, 12, 13},
	{14, 11, 13},
	{14, 10, 14},
	{13, 10, 14},
	{12, 10, 14},
	{12, 9, 14},
	{12, 8, 15},
	{11, 8, 15},
	{10, 8, 15},
	{10, 7, 15},
	{10, 6, 15},
	{11, 6, 15},
	{11, 5, 16},
	{12, 5, 16},
	{13, 5, 16},
	{13, 6, 16},
	{13, 7, 16},
	{14, 7, 16},
	{15, 7, 17},
	{15, 6, 17},
	{16, 6, 17},
	{17, 6, 18},
	{17, 5, 18},
	{17, 4, 19},
};

#define PAL_LIGHT_PATH (6)

static const mapStepT *mapStepForLevel (UINT8 l)
{
	const mapStepT *p = currentMapSteps;
	while (p->level != l)
	{ 
		p++;
	}
	return p;
}

static void LightenPath (UINT8 topLevel)
{
	//change level dots color palettes when beating levels
	VBK_REG = 1;
	const mapStepT *p = currentMapSteps;

	do
	{
		set_tile_xy ( p->x, p->y, PAL_LIGHT_PATH);
		p++;
	} while (p->level != topLevel);

	// color the current level as well
	set_tile_xy ( p->x, p->y, PAL_LIGHT_PATH);
	VBK_REG = 0;
}

static UINT8 getTens (UINT8 full)
{
    UINT8 t = 0 ;
    while (full > 9)
    {
        full -= 10;
        t ++;
    }
    return t;
}

static void twoDigitsAt (UINT8 x, UINT8 y, UINT8 val)
{
	UINT8 tile = 0;
	UINT8 tens = getTens(val);
	UINT8 ones = val - (tens * 10);
	if (tens == 0)
	{
		tile = ones + TILE_0;
		set_tile_xy (x, y, tile);
	}
	else
	{
		tile = tens + TILE_0;
		set_tile_xy (x, y, tile);
		tile = ones + TILE_0;
		x++;
		set_tile_xy (x, y, tile);
	}
}

void Setup_HUD(void)
{
	UINT8 level = level_current - (getTens(level_current) * 10);
	level += TILE_0;

	//level display
	set_tile_xy (11, 1, level);	

	twoDigitsAt (4, 1, nutmeglives);
	twoDigitsAt (16, 1, acorncounter);
}

#define TINY_NUTMEG_OFFSET_X (0)
#define TINY_NUTMEG_OFFSET_Y (-3)

static void SetTinyNutmegAtCurrentLevel(void)
{
	UINT8 level = level_current;
	const mapStepT *p = mapStepForLevel (level_current);

	UINT8 x = (p->x << 3) + TINY_NUTMEG_OFFSET_X;
	UINT8 y = (p->y << 3) + TINY_NUTMEG_OFFSET_Y;

	spr_tinyNutmeg = SpriteManagerAdd(SpriteNutmegTiny, x, y); 

	if (level == 0)
	{
		// move nutmeg onto the tree
		TranslateSprite(spr_tinyNutmeg, -8, 0);
	}

	if (level == 10)
	{
		// move nutmeg off the left side of the screen
		TranslateSprite(spr_tinyNutmeg, -20, 0);
	}
}

void Start_StateOverworld1() {
	SPRITES_8x16;

	// testing - start on world 2
	//level_max = 10;

	// Setup the map steps for the current overworld;
	if (level_max < 10)
	{
		currentMapSteps = steps_ow1;
		InitScroll(BANK(overworld1map), &overworld1map, collision_tiles_overworld1, 0);
	}
	else 
	{
		currentMapSteps = steps_ow2;
		InitScroll(BANK(overworld2map), &overworld2map, collision_tiles_overworld1, 0);
	}

	// TESTING some fiddling around the first level of the second overworld
	//level_max = 9;
	//level_current = 9;

	if (levelbeat)
	{	
		level_max++;

		level_next = level_max;
		automove = true;
		
		// Start moving towards the next step
		movingToStep = mapStepForLevel(level_current);
		movingToStep ++;

		levelbeat = false;
	}

	LightenPath(level_max);
	Setup_HUD();

	// sprites
	SetTinyNutmegAtCurrentLevel();
	SpriteManagerAdd(SpriteNutHead, 16, 7);
	SpriteManagerAdd(SpriteAcorn, 14*8, 7);

	isAcornMoving = false;

	waterAnimCounter = 0;

	PlayMusic(acornkingdom, 1);

	
	SHOW_SPRITES;
	SHOW_BKG;
	HIDE_WIN;
}

static void animateWater (void)
{
	if (waterAnimCounter == 0) 
	{
		set_bkg_data (0x01, 1, overworld1_water1);
	}
	else if (waterAnimCounter == 20) 
	{
		set_bkg_data (0x01, 1, overworld1_water2);
	}
	waterAnimCounter++;

	if (waterAnimCounter == 40) {
		waterAnimCounter = 0;
	}
}

void Update_StateOverworld1() {
	animateWater ();

	// level selection
	if (automove == false) {
		if (KEY_PRESSED(J_A) || KEY_PRESSED(J_START)) {
			if (level_current == 1) SetState(StateLevel1);
			else if (level_current == 2) SetState(StateLevel2);
			else if (level_current == 3) SetState(StateLevel3);
			else if (level_current == 4) SetState(StateLevel4);
			else if (level_current == 5) SetState(StateLevel5);
			else if (level_current == 6) SetState(StateLevel6);
			else if (level_current == 7) SetState(StateLevel7);
			else if (level_current == 8) SetState(StateLevel8);
			else if (level_current == 9) SetState(StateW1Boss);
			else if (level_current >= 10) SetState(StateLevel2_1);

			return;
		}
	}

	// dir 0 = left
	// dir 1 = right
	// dir 2 = up
	// dir 3 = down
	if (automove == true)
	{
		// TODO - flash the screen when we enter the boss stage
		/*
		if (W1LevelSelection == 11) {
			if 		(bossflash >= 0 && bossflash < 5)  set_bkg_data (0x3F, 1, overworld1_boss1);
			else if (bossflash >= 5 && bossflash < 10) set_bkg_data (0x3F, 1, overworld1_boss2);

			bossflash++;

			if (bossflash > 10) bossflash = 0;
		}
		*/

		if (moveCount == 0)
		{
			UINT16 x = spr_tinyNutmeg->x - TINY_NUTMEG_OFFSET_X;
			UINT16 y = spr_tinyNutmeg->y - TINY_NUTMEG_OFFSET_Y;

			UINT16 tx = movingToStep->x;
			tx <<= 3;
			UINT16 ty = movingToStep->y;
			ty <<= 3;

			// check if we are there
			if ((x == tx) && (y == ty))
			{
				// check if we need to move another step
				if (movingToStep->level == level_next)
				{
					// we are there
					automove = false;
					level_current = level_next;
					Setup_HUD();
				}
				else 
				{
					// start moving to the next step
					movingToStep++;
					tx = movingToStep->x;
					tx <<= 3;
					ty = movingToStep->y;
					ty <<= 3;
				}
			}

			// move 1 pixel towards the goal
			if (x < tx) { TranslateSprite (spr_tinyNutmeg, 1, 0);}
			else if (x > tx) { TranslateSprite (spr_tinyNutmeg, -1, 0);}
			else if (y < ty) { TranslateSprite (spr_tinyNutmeg, 0, 1);}
			else if (y > ty) { TranslateSprite (spr_tinyNutmeg, 0, -1);}
		}

		moveCount++;
		if (moveCount == 3)
		{
			moveCount = 0;
		}
	}
}