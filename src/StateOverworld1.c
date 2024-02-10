#include "Banks/SetAutoBank.h"

#include "BankManager.h"

//#include "..\res\src\overworld1.h"
//#include "..\res\src\overworld1map.h"

#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"

//#include "..\res\src\nutmeg.h"
//#include "..\res\src\acorn.h"
//#include "..\res\src\nutmegtiny.h"
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

//copied from SpriteNutmegTiny
UINT8 e = 0;
UINT8 bossflash = 0;
UINT8 W1LevelSelection; 		// nutmeg starts at level 1
								// level 0 is the tree
								// mushroom is level 4
UINT8 overWorldDirection  = 0;
UINT8 distance  = 0;

bool inputenabled;
UINT8 treetolevel1move;
bool levelbeat;
//end copied from SpriteNutmegTiny



//copied from SpriteNutmegTiny
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

//end copied from SpriteNutmegTiny
UINT8 level_current = 0;
UINT8 level_next = 0;

bool overworld1visited = false;

UINT8 collision_tiles_overworld1[] = {0};

//extern UINT8* acornkingdom_mod_Data[];
DECLARE_MUSIC(acornkingdom);

extern Sprite * spr_nutmegtiny;

//List of tiles that will be animated
static const unsigned char overworld1_water1[] = {
	0xff,0x00,0xff,0x00,0x9f,0x00,0x6f,0x00,
	0xff,0x00,0xf9,0x00,0xf6,0x00,0xff,0x00
};

static const unsigned char overworld1_water2[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0x9f,0x00,
	0x69,0x00,0xf6,0x00,0xff,0x00,0xff,0x00
};

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
	{20, 12, 10},
};


static const mapStepT steps_ow2 [] = {
	{0, 12, 0},
	{1, 12, 0},
	{2, 12, 0},
	{3, 12, 1},
	{4, 12, 1},
	{5, 12, 1},
	{6, 12, 2},
	{7, 12, 2},
	{8, 12, 2},
	{9, 12, 3},
	{10, 12, 3},
	{11, 12, 3},
	{12, 12, 4},
	{13, 12, 4},
	{14, 12, 4},
	{14, 11, 4},
	{14, 10, 5},
	{13, 10, 5},
	{12, 10, 5},
	{12, 9, 5},
	{12, 8, 6},
	{11, 8, 6},
	{10, 8, 6},
	{10, 7, 6},
	{10, 6, 6},
	{11, 6, 6},
	{11, 5, 7},
	{12, 5, 7},
	{12, 5, 7},
	{13, 6, 7},
	{13, 7, 7},
	{14, 7, 7},
	{15, 7, 8},
	{15, 6, 8},
	{16, 6, 8},
	{17, 6, 9},
	{17, 5, 9},
	{17, 4, 10},
};

#define PAL_LIGHT_PATH (6)


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

//copied from SpriteNutmegTiny
//Need to update THIS to spr_nutmegtiny
static void Move (UINT8 dir, UINT8 dis) {
	if (dis > 0) {
		if (e >= 0 && e <= dis) {
			if (dir == 0) TranslateSprite (spr_nutmegtiny, -1, 0);
			if (dir == 1) TranslateSprite (spr_nutmegtiny, 1, 0);
			if (dir == 2) TranslateSprite (spr_nutmegtiny, 0, -1);
			if (dir == 3) TranslateSprite (spr_nutmegtiny, 0, 1);
		}

		e++;

		if (e > dis) {
			e = 0;
			distance = 0;
			levelbeat = false;
			inputenabled = true;
		}
	}
}
//end copied from SpriteNutmegTiny

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
	UINT8 level = LevelForStage[W1LevelSelection];
	level += TILE_0;

	//level display
	// TODO - tree, mushroom and boss have different tiles instead of numbers
	set_tile_xy (11, 1, level);	
	
	/*
		if (W1LevelSelection == 11) {
			if 		(bossflash >= 0 && bossflash < 5)  set_bkg_data (0x3F, 1, overworld1_boss1);
			else if (bossflash >= 5 && bossflash < 10) set_bkg_data (0x3F, 1, overworld1_boss2);

			bossflash++;

			if (bossflash > 10) bossflash = 0;
		}
	*/

	//health system DISPLAY
	// lives
	twoDigitsAt (4, 1, nutmeglives);
	twoDigitsAt (16, 1, acorncounter);
}

static void SetTinyNutmegAtCurrentLevel(void)
{
	UINT8 level = LevelForStage[W1LevelSelection];

	mapStepT *p = currentMapSteps;
	while (p->level < level)
	{
		p ++;
	}
	UINT8 x = (p->x * 8) + 15;
	UINT8 y = (p->y * 8) - 3;
	SpriteManagerAdd(SpriteNutmegTiny, x, y); 
}

void Start_StateOverworld1() {
	SPRITES_8x16;

	// TODO Setup the right overworld
 	currentMapSteps = steps_ow2;

	//InitScroll(BANK(overworld1map), &overworld1map, collision_tiles_overworld1, 0);
	InitScroll(BANK(overworld2map), &overworld2map, collision_tiles_overworld1, 0);

	LightenPath(LevelForStage[W1LevelSelection]);
	Setup_HUD();

	// sprites
	SetTinyNutmegAtCurrentLevel();
	SpriteManagerAdd(SpriteNutHead, 16, 7);
	SpriteManagerAdd(SpriteAcorn, 14*8, 7);

	isAcornMoving = false;

	waterAnimCounter = 0;

	PlayMusic(acornkingdom, 1);

	if (overworld1visited == false) {
		W1LevelSelection = 0;
		treetolevel1move = 0;
		inputenabled = false;
	}

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
	// if first time visiting Overworld 1, set to tree level
	// and set overworld1visited to true so it can't do it again
	if (overworld1visited == false) {
		if 		(treetolevel1move < 50)  { overWorldDirection  = 1; W1LevelSelection = 0; inputenabled = false; levelbeat = false; }
		else if (treetolevel1move == 50) { overWorldDirection  = 1; distance = 23; W1LevelSelection = 1; inputenabled = false; }
		else if (treetolevel1move >= 65) { inputenabled = false; overworld1visited = true; levelbeat = false; }

		treetolevel1move++;
	}

	//use this to modify background tiles in static scenes
	//set_bkg_tiles (6, 8, 1, 1, overworld1_water1); //x, y, w, h, *tiles

	//water anim
	animateWater ();

	//level selection
	if (inputenabled == true) {
		if (KEY_PRESSED(J_A) || KEY_PRESSED(J_START)) {
			//if (W1LevelSelection == 0) SetState(StateTree);
			//distance = 0;
			if (W1LevelSelection == 1) SetState(StateLevel1);
			else if (W1LevelSelection == 2) SetState(StateLevel2);
			else if (W1LevelSelection == 5) SetState(StateLevel3);
			else if (W1LevelSelection == 6) SetState(StateLevel4);
			else if (W1LevelSelection == 7) SetState(StateLevel5);
			else if (W1LevelSelection == 8) SetState(StateLevel6);
			else if (W1LevelSelection == 9) SetState(StateLevel7);
			else if (W1LevelSelection == 10) SetState(StateLevel8);
			else if (W1LevelSelection == 11) SetState(StateW1Boss);
		}
	}

	// dir 0 = left
	// dir 1 = right
	// dir 2 = up
	// dir 3 = down

	if (e == 0 && levelbeat == true) {
		// LEVEL 1
		if (W1LevelSelection == 1 && levelbeat == true) {
			overWorldDirection  = 3; distance = 15; W1LevelSelection = 2;  inputenabled = false;
		}
		// LEVEL 2
		else if (W1LevelSelection == 2 && levelbeat == true) {
			overWorldDirection  = 1; distance = 23; W1LevelSelection = 5; inputenabled = false;
		}
		// LEVEL 5
		else if (W1LevelSelection == 5 && levelbeat == true) {
			overWorldDirection  = 3; distance = 15; W1LevelSelection = 6; inputenabled = false;
		}
		// LEVEL 6
		else if (W1LevelSelection == 6 && levelbeat == true) {
			overWorldDirection  = 1; distance = 23; W1LevelSelection = 7; inputenabled = false;
		}
		// LEVEL 7
		else if (W1LevelSelection == 7 && levelbeat == true) {
			overWorldDirection  = 2; distance = 31; W1LevelSelection = 8; inputenabled = false;
		}
		// LEVEL 8
		else if (W1LevelSelection == 8 && levelbeat == true) {
			overWorldDirection  = 1; distance = 23; W1LevelSelection = 9; inputenabled = false;
		}
		// LEVEL 9
		else if (W1LevelSelection == 9 && levelbeat == true) {
			overWorldDirection  = 3; distance = 23; W1LevelSelection = 10; inputenabled = false;
		}
		// LEVEL 10
		else if (W1LevelSelection == 10 && levelbeat == true) {
			overWorldDirection  = 3; distance = 24; W1LevelSelection = 11; inputenabled = false;
		}
		// LEVEL 11 - PICNIC TABLE (MINI BOSS)
		else if (W1LevelSelection == 11 && levelbeat == true) {
			overWorldDirection  = 1; distance = 46; W1LevelSelection = 12; inputenabled = false;
		} //change to overworld2
	}

	/* * * * * * * * * * * * * * * * * * * * * */ // 1. Depending on which level player is standing on
	/*     Send to Move Function (line 137)    */ //    define a overWorldDirection  and DISTANCE and update player
	/*                                         */ //    to the level Nutmeg will be traveling to
	if (distance > 0) 
	{
		Move (overWorldDirection , distance); // 2. Send DIR and DIS to a function that moves the
	}
	/*                                         */ //    player, run the function until e = distance
	/*                                         */ // 3. Reset e to 0, distance to 0
	/* * * * * * * * * * * * * * * * * * * * * */ //


}