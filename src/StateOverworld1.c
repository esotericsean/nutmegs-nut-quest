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
IMPORT_MAP (overworld3map);

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
static UINT8 overworldNum = 0;

#define ENTERING_WORLD_2_FROM_1 (0xfe)
#define ENTERING_WORLD_1 (0xfd)
#define ENTERING_WORLD_3_FROM_2 (0xfc)
#define ENTERING_WORLD_2_FROM_3 (0xfb)

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

// what level do you have to move to go to the previous and next level
typedef struct mapLevelDirectionT {
	const UINT8 prev;
	const UINT8 next;
} mapLevelDirectionT;

static const mapLevelDirectionT levelDirections[] = {
	{0xff, J_RIGHT},
	{J_LEFT, J_DOWN},
	{J_UP, J_RIGHT},
	{J_LEFT, J_DOWN},
	{J_UP, J_RIGHT},
	{J_LEFT, J_UP},
	{J_DOWN, J_RIGHT},
	{J_LEFT, J_DOWN},
	{J_UP, J_DOWN},
	{J_UP, J_RIGHT}, // 1-BOSS
	{J_LEFT, J_RIGHT},
	{J_LEFT, J_RIGHT},
	{J_LEFT, J_RIGHT},
	{J_LEFT, J_RIGHT},
	{J_DOWN, J_LEFT},
	{J_DOWN, J_LEFT},
	{J_DOWN, J_RIGHT},
	{J_LEFT, J_UP},
	{J_LEFT, J_UP},
	{J_DOWN, J_RIGHT}, // 2-Boss
	{J_LEFT, J_RIGHT}, // 3-1
	{J_LEFT, J_DOWN},
	{J_RIGHT, J_LEFT},
	{J_LEFT, J_RIGHT},
	{J_UP, J_DOWN},
	{J_UP, 0xff}, // 3-Boss
};

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
	{3, 6, 0}, // home tree
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
	{0xff, 0xff, 0xff} // end of array
};


static const mapStepT steps_ow2 [] = {
	{254, 12, 9}, // 254 = special value to force off the left hand side of the map
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
	{18, 4, 19},
	{19, 4, 19},
	{20, 4, 20},
	{0xff, 0xff, 0xff} // end of array
};

static const mapStepT steps_ow3 [] = {
	{254, 4, 19}, // 254 = special value to force off the left hand side of the map
	{0, 4, 19},
	{1, 4, 19},
	{2, 4, 19},
	{3, 4, 19},
	{4, 4, 20},
	{5, 4, 20},
	{6, 4, 20},
	{7, 4, 20},
	{8, 4, 20},
	{9, 4, 20},
	{9, 5, 20},
	{10, 5, 20},
	{11, 5, 20},
	{12, 5, 20},
	{12, 4, 20},
	{13, 4, 20},
	{14, 4, 21},
	{14, 5, 21},
	{14, 6, 21},
	{14, 7, 21},
	{14, 8, 21},
	{14, 9, 21},
	{13, 9, 21},
	{12, 9, 22},
	{11, 9, 22},
	{10, 9, 22},
	{9, 9, 22},
	{8, 9, 22},
	{7, 9, 22},
	{7, 8, 22},
	{7, 7, 22},
	{8, 7, 22},
	{9, 7, 23},
	{10, 7, 23},
	{11, 7, 23},
	{12, 7, 23},
	{13, 7, 23},
	{14, 7, 23},
	{15, 7, 23},
	{16, 7, 23},
	{16, 8, 24},
	{16, 9, 24},
	{16, 10, 24},
	{16, 11, 24},
	{16, 12, 24},
	{16, 13, 24},
	{16, 14, 24},
	{16, 15, 25},
	{16, 16, 25},
	{16, 17, 25},
	{16, 18, 25},
	{16, 19, 26},
	{0xff, 0xff, 0xff} // end of array
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
	
	const mapStepT *p = currentMapSteps;
	uint8_t lastStage = p->level;
	if (overworldNum == 1)
	{
		// skip highlighting the tree
		p ++;
	}

	do
	{
		
		if (overworldNum == 1)
		{
			if (p->level == lastStage)
			{	
				set_tile_xy ( p->x, p->y, 37);
			}
			else if (p->level == 9)
			{
				// change the boss tile instead of the attribute
				set_tile_xy(p->x, p->y, 39);
			}
			else
			{
				// change the boss tile instead of the attribute
				set_tile_xy(p->x, p->y, 36);
			}
			VBK_REG=1;
			set_tile_xy(p->x, p->y, 6);
			VBK_REG=0;
		}
		else if (overworldNum == 2) 
		{
			if (p->level == lastStage)
			{	
				set_tile_xy ( p->x, p->y, 37);
			}
			else if (p->level == 19)
			{
				// change the boss tile instead of the attribute
				set_tile_xy(p->x, p->y, 39);
			}
			else
			{
				// change the boss tile instead of the attribute
				set_tile_xy(p->x, p->y, 36);
			}
			VBK_REG=1;
			set_tile_xy(p->x, p->y, 7);
			VBK_REG=0;
		}
		else if (overworldNum == 3) 
		{
			if (p->level == lastStage)
			{	
				set_tile_xy ( p->x, p->y, 37);
			}
			else if (p->level == 25)
			{
				// change the boss tile instead of the attribute
				set_tile_xy(p->x, p->y, 39);
			}
			else
			{
				// regular levels have a new tile and palette
				set_tile_xy(p->x, p->y, 36);
			}
			VBK_REG=1;
			set_tile_xy(p->x, p->y, 3);
			VBK_REG=0;
		}
		lastStage = p->level;
		p++;
	} while ((p->level != topLevel) && (p->level != 0xff));

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
	UINT8 level = level_next;

	if (overworldNum == 2)
	{
		level = level_next + 1 - (getTens(level_next) * 10);
		if (level_next < 11)
		{
			level = 1;
		}
	} 
	else if (overworldNum == 3)
	{
		level = level_next - 19;
		if (level_next < 21)
		{
			level = 1;
		}
	}
	level += TILE_0;

	if (level_next == 0)
	{
		// show the tree icon?
		level = 0x1e;
	}
	else if ((level_next == 9) || (level_next == 19) || (level_next == 25))
	{
		// show the boss icon?
		level = 0x27;
	}

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

	if (overworldNum == 2 && level == 9)
	{
		// move nutmeg off the left side of the screen
		spr_tinyNutmeg->x = 65527;
	}
	if (overworldNum == 3 && level == 19)
	{
		// move nutmeg off the left side of the screen
		spr_tinyNutmeg->x = 65527;
	}
}

static void startAutoMoveTowards (UINT8 towards)
{
	level_next = towards;
	automove = true;

	// Start moving towards the next step
	movingToStep = mapStepForLevel(level_current);
	if (level_next < level_current)
	{
		movingToStep --;
	}
	else
	{
		movingToStep ++;
	}
}

void Start_StateOverworld1 (void) {
	SPRITES_8x16;

	isAcornMoving = false;

	// Setup the map steps for the current overworld;
	if ((level_current < 10) || (level_current == ENTERING_WORLD_1))
	{
		overworldNum = 1;
		currentMapSteps = steps_ow1;
		InitScroll(BANK(overworld1map), &overworld1map, collision_tiles_overworld1, 0);
	}
	else if (((level_current >= 10) && (level_current < 20))
		|| (level_current == ENTERING_WORLD_2_FROM_1)
		|| (level_current == ENTERING_WORLD_2_FROM_3))
	{
		overworldNum = 2;
		currentMapSteps = steps_ow2;
		InitScroll(BANK(overworld2map), &overworld2map, collision_tiles_overworld1, 0);
	} else
	{
		overworldNum = 3;
		currentMapSteps = steps_ow3;
		InitScroll(BANK(overworld3map), &overworld3map, collision_tiles_overworld1, 0);
	}

	// on world transistions do some fiddling to make nutmeg walk to the correct level
	if (level_current == ENTERING_WORLD_1)
	{
		level_current = 10;
		level_next = 9;
		startAutoMoveTowards(level_next);
	} else if (level_current == ENTERING_WORLD_2_FROM_1)
	{
		level_current = 9;
		level_next = 10;
		startAutoMoveTowards(level_next);
	} else if (level_current == ENTERING_WORLD_2_FROM_3)
	{
		level_current = 20;
		level_next = 19;
		startAutoMoveTowards(level_next);
	} else if (level_current == ENTERING_WORLD_3_FROM_2)
	{
		level_current = 19;
		level_next = 20;
		startAutoMoveTowards(level_next);
	}

	if (levelbeat)
	{	
		// Did we beat a new level
		if (level_current == level_max)
		{
			// update the max
			level_max++;

			// start moving towads the new level
			startAutoMoveTowards (level_max);
		} 

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

static void moveTowardsNextLevel(void)
{
	if (moveCount == 0)
	{
		UINT16 x = spr_tinyNutmeg->x - TINY_NUTMEG_OFFSET_X;
		UINT16 y = spr_tinyNutmeg->y - TINY_NUTMEG_OFFSET_Y;

		UINT16 tx = movingToStep->x;
		if (tx == 254)
		{
			// max - 8
			tx = 65527;
		}
		else
		{
			tx <<= 3;
		}
		UINT16 ty = movingToStep->y;
		ty <<= 3;

		// check if we are there
		if ((x == tx) && (y == ty))
		{
			const mapStepT * oneBefore = movingToStep - 1;

			// check if we need to move another step
			if ((movingToStep->level == level_next) && (level_next > level_current))
			{
				// we are there
				automove = false;
				level_current = level_next;
				if ((overworldNum == 1) && (level_next == 10))
				{
					level_current = ENTERING_WORLD_2_FROM_1;
					SetState (StateOverworldChange);
				}
				else if ((overworldNum == 2) && (level_next == 20))
				{
					level_current = ENTERING_WORLD_3_FROM_2;
					SetState (StateOverworldChange);
				}
				else
				{
					Setup_HUD();
				}
			}
			else if (((oneBefore->level == level_next-1) || movingToStep == currentMapSteps) && (level_next < level_current))
			{
				// we are there
				automove = false;
				level_current = level_next;
				if ((overworldNum == 2) && (level_next == 9))
				{
					level_current = ENTERING_WORLD_1;
					SetState (StateOverworldChange);
				}
				if ((overworldNum == 3) && (level_next == 19))
				{
					level_current = ENTERING_WORLD_2_FROM_3;
					SetState (StateOverworldChange);
				}
				else
				{
					Setup_HUD();
				}
			}
			else 
			{
				// start moving to the next step
				if (level_next < level_current)
				{
					movingToStep --;
				}
				else
				{
					movingToStep ++;
				}

				tx = movingToStep->x;
				if (tx == 254)
				{
					// max - 8
					tx = 65527;
				}
				else
				{
					tx <<= 3;
				}
				ty = movingToStep->y;
				ty <<= 3;
			}
		}

		// move 1 pixel towards the goal
		if (tx == 65527)
		{
			// this is the special case to move nutmeg off the left hand side of the map
			TranslateSprite (spr_tinyNutmeg, -1, 0);
			spr_tinyNutmeg->mirror = V_MIRROR;
		}
		else if ((x > 60000) || (x < tx)) { 
			TranslateSprite (spr_tinyNutmeg, 1, 0);
			spr_tinyNutmeg->mirror = NO_MIRROR;	
		}
		else if (x > tx) { 
			TranslateSprite (spr_tinyNutmeg, -1, 0);
			spr_tinyNutmeg->mirror = V_MIRROR;
		}
		else if (y < ty) { TranslateSprite (spr_tinyNutmeg, 0, 1);}
		else if (y > ty) { TranslateSprite (spr_tinyNutmeg, 0, -1);}
	}

	moveCount++;
	if (moveCount == 1)
	{
		moveCount = 0;
	}
}

void Update_StateOverworld1 (void) {
	animateWater ();

	// level selection
	if (automove == false) {
		UINT8 j = joypad();
		if ((levelDirections[level_current].prev == j) && (level_current > 0))
		{
			startAutoMoveTowards (level_current-1);
		}
		else if ((levelDirections[level_current].next == j) && (level_current < 25))
		{
			startAutoMoveTowards (level_current+1);
		}
		
		if (KEY_PRESSED(J_A) || KEY_PRESSED(J_START)) {
			if (level_current == 0) SetState(StateLevelTree);
			if (level_current == 1) SetState(StateLevel1);
			else if (level_current == 2) SetState(StateLevel2);
			else if (level_current == 3) SetState(StateLevel3);
			else if (level_current == 4) SetState(StateLevel4);
			else if (level_current == 5) SetState(StateLevel5);
			else if (level_current == 6) SetState(StateLevel6);
			else if (level_current == 7) SetState(StateLevel7);
			else if (level_current == 8) SetState(StateLevel8);
			else if (level_current == 9) SetState(StateW1Boss);
			else if (level_current == 10) SetState(StateLevel2_1);
			else if (level_current == 11) SetState(StateLevel2_2);
			else if (level_current == 12) SetState(StateLevel2_platform);
			else if (level_current == 13) SetState(StateLevel1_platform);
			else if (level_current == 14) SetState(StateLevel2_glidefall);
			else if (level_current >= 15) SetState(StateLevel2_multi);
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
		moveTowardsNextLevel();

	}
}