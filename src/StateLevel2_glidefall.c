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

IMPORT_MAP (level2_glidefallmap);

static UINT8 levelStartCount = 0;
static UINT8 endlevel_counter = 0;

static const UINT8 collision_tiles_level[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18, 0};

DECLARE_MUSIC (quickstart);
DECLARE_MUSIC (mushrooms);
DECLARE_MUSIC (quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_nutmegbow;
extern Sprite * spr_camera;

//nutmeg sprite region
extern UINT8 nut_region;

static UINT8 camera_delta_y;
typedef struct {
	UINT8 x;
	UINT8 y;
} nutPosT;


static const nutPosT levelNuts [] = 
{
	{9, 18},
	{4, 29},
	{3, 35},
	{10, 52},
	{5, 64},
	{15, 73},
	{3, 87},
	{7, 91},
	{16, 96},
	{11, 107},
	{4, 111},
	{18,140},
	{18,147},
	{12, 150},
	{4, 153},
	{2, 171},
	{12, 183},
	{6, 188},
	{5, 193},
	{12, 208},
	{11, 213},
	{10, 217},
	{9, 221},
	{9, 225},
	{8, 229},
	{9, 232},
	{12, 235},
	{12, 238},
	{11, 240},
	{8, 241},
	{4, 242},
	{1, 243},
	{0, 0},
};

#define NUM_NUTS (sizeof (levelNuts) / sizeof(levelNuts[0]))
static UINT8 levelNutPos;
static void AddNut (UINT16 x, UINT16 y)
{
	x <<= 3;
	y <<= 3;
	Sprite *s = SpriteManagerAdd(SpriteAcorn, x, y);
	s->lim_x = 200;
	s->lim_y = 300;
}

static void AddNuts (void)
{
	UINT16 ypos = spr_nutmeg->y;
	UINT8 y = ypos >> 3;

	if (spr_nutmeg->y > 60000)
	{ 
		y = 0;
	}

	while ((levelNutPos < NUM_NUTS) && (levelNuts[levelNutPos].y < y + 20))
	{
		AddNut (levelNuts[levelNutPos].x, levelNuts[levelNutPos].y);
		levelNutPos ++;
	}
}

void Start_StateLevel2_glidefall(void) 
{
	isSpikeLevel = true;
	
	levelorientation = vertical;
	levelbeat = false;
	levelStartCount = 0;
	SPRITES_8x16;

	pitdeathactive = false;

	nut_region = 0;
	deathmusicplayed = false;

	__critical { PlayMusic(quickstart, 1); }

	UINT16 startx = 10;
	UINT16 starty = 2;

	startx <<= 3;
	starty <<= 3;

	if (hasbow == true) {
		spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, startx, starty);
	}
	spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, startx, starty);

	// clear some nutmeg 
	accelX = 0;
	accelY = 0;
	movestate = inair;
	// stop nutmeg from being able to jump in mid air at the start of the level
	jumpPeak = 1; 

	scroll_target = spr_camera = SpriteManagerAdd(SpriteCamera, startx, starty);
	camera_delta_y = 0;

	levelNutPos = 0;
	AddNuts ();
	
	
	InitScrollTiles(0, &levelFreeFallTiles);
	InitScroll(BANK(level2_glidefallmap), &level2_glidefallmap, collision_tiles_level, 0);
	
	Hud_Init(false);
	
	cutscenemode = false;
	isAcornMoving = true; //yes, it is moving

	FlagPole_Init();
	endlevel_counter = 0;
	LevelStart_Init(7,7);

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel2_glidefall(void) 
{
	Hud_Update();
	AddNuts ();
	
	if (timerlevel == 0) {
		while (nutmeg_death == false)
		{
			nutmeg_hit();
		}
	}

	if (nutmeg_death == true) {
		if (deathmusicplayed == false) {
			__critical { PlayMusic(quickdeath, 1); }
			deathmusicplayed = true;
		}

		isSpikeLevel = false;

		if (nutmegdeathtimer >= 125) {
			if (GameOver == true) {
				SetState(StateGameOver);
			}
			else if (GameOver == false) {
				nutmeg_setupNewLife();
				SetState(StateOverworld1); // change to correct world
			}
			return;
		}

		nutmegdeathtimer++;
	}
	
	if (levelStartCount < 105) {
		//Level Start!
		
		if (levelStartCount == 100) {
			__critical { PlayMusic(mushrooms, 1); }
		}

		LevelStart_Update();
		levelStartCount++;
	}

	//animate flagpole
	FlagPole_Animate();
	
	if (levelbeat == true) {
		cutscenemode = enabled;
		
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

	
		if (endlevel_counter >= 100) {
			isSpikeLevel = false;
			SetState(StateOverworld1);
		}

		if (endlevel_counter < 250) endlevel_counter++;
	}

	// invisible walls left and right
	if (spr_nutmeg->x < 3) { spr_nutmeg->x = 3; }

	if ((spr_nutmeg->y < 1950) && (spr_nutmeg->x > 149)) { spr_nutmeg->x = 149; }

	// ramp up as you drop until the camera is well below you
	if (camera_delta_y < 70)
	{
		camera_delta_y ++;
	}

	scroll_target->y = spr_nutmeg->y + camera_delta_y;

	if (nutmeg_death == false)
	{
		if (spr_nutmeg->y >= 1950 && spr_nutmeg-> y < 2500 && levelbeat == false ) {
			FlagPole_Activate(10, 256);

			levelbeat = true;
			endlevel_counter = 0;
			cutscenemode = enabled;
			cutscenewalkright = true;
		}
	
	}
}