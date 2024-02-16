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

static void AddNut (UINT16 x, UINT16 y)
{
	x <<= 3;
	y <<= 3;
	Sprite *s = SpriteManagerAdd(SpriteAcorn, x, y);
	s->lim_x = 1000;
	s->lim_y = 300;
}

void Start_StateLevel2_glidefall(void) 
{

	levelorientation = vertical;
levelbeat = false;
	levelStartCount = 0;
	SPRITES_8x16;

	pitdeathactive = false;

	nut_region = 0;
	deathmusicplayed = false;

	__critical { PlayMusic(quickstart, 1); }

	// clear some nutmeg 
	accelX = 0;
	accelY = 0;
	movestate = inair;

	UINT16 startx = 10;
	UINT16 starty = 2;

	startx <<= 3;
	starty <<= 3;

	if (hasbow == true) {
		spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, startx, starty);
	}
	spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, startx, starty);

	scroll_target = spr_camera = SpriteManagerAdd(SpriteCamera, startx, starty);
	camera_delta_y = 0;

	AddNut (10,20);
	AddNut(5,40);
	
	AddNut(15,60);
	
	InitScrollTiles(0, &level1tiles);
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
			SetState(StateOverworld1);
		}

		if (endlevel_counter < 250) endlevel_counter++;
	}

	// invisible walls left and right
	if (spr_nutmeg->x < 3) { spr_nutmeg->x = 3; }
	if (spr_nutmeg->x > 149) { spr_nutmeg->x = 149; }

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