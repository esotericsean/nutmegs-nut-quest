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

IMPORT_MAP (level2_platformmap);

static UINT8 startLevel_counter = 0;
static UINT8 endlevel_counter = 0;


static const UINT8 collision_tiles[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,0};
static const UINT8 collision_tiles_down[] = {29,30,31,32,0};

DECLARE_MUSIC (quickstart);
DECLARE_MUSIC (mushrooms);
DECLARE_MUSIC (quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_nutmegbow;
extern Sprite * spr_camera;


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
	{20, 5, SpritePlatform, 0, 1, PLATFORM_TYPE_BACK_AND_FORTH, 11*8, 0}, // up down
	{24, 5, SpritePlatform, 0, 0, PLATFORM_TYPE_WAITING_TO_DROP, 0 , 0}, // dropping
	{29, 7, SpriteAcorn, 0, 0, 0, 0, 0},
	{31, 3, SpriteAcorn, 0, 0, 0, 0, 0},
	{31, 10, SpriteAcorn, 0, 0, 0, 0, 0},
	{46, 6, SpritePlatform, 0, 0, PLATFORM_TYPE_WAITING_TO_DROP, 0, 0}, // dropping
	{56, 5, SpritePlatform, 0, 0, PLATFORM_TYPE_WAITING_TO_DROP, 0, 0}, // dropping
	{66, 4, SpritePlatform, 0, 0, PLATFORM_TYPE_WAITING_TO_DROP, 0, 0}, // dropping
	{76, 3, SpritePlatform, 0, 0, PLATFORM_TYPE_WAITING_TO_DROP, 0, 0}, // dropping
	{79, 11, SpriteAcorn, 0, 0, 0, 0, 0},
	{79, 11, SpriteAcorn, 0, 0, 0, 0, 0},
	{87, 15, SpriteMushroom, 0, 0, 0, 0, 0},
	{89, 4, SpriteAcorn, 0, 0, 0, 0, 0},
	{91, 7, SpritePlatform, 1, 0, PLATFORM_TYPE_BACK_AND_FORTH, 14*8, 0}, // left right
	{114, 16, SpritePlatform, 1, ((UINT8)-1), PLATFORM_TYPE_BACK_AND_FORTH, 13*8, 0}, // diagonal
	{119, 3, SpriteAcorn, 0, 0, 0, 0, 0},
	{146, 10, EnemyBirdy, 0, 0, 0, 0, 0},
	{153, 3, SpriteAcorn, 0, 0, 0, 0, 0},
	{159, 10, EnemyBirdy, 0, 0, 0, 0, 0},
	{167, 3, SpriteAcorn, 0, 0, 0, 0, 0},
	{172, 10, EnemyBirdy, 0, 0, 0, 0, 0},
	{180, 2, SpriteAcorn, 0, 0, 0, 0, 0},
	{185, 10, EnemyBirdy, 0, 0, 0, 0, 0},
	{194, 2, SpriteAcorn, 0, 0, 0, 0, 0},
	{231, 6, SpriteAcorn, 0, 0, 0, 0, 0},
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

void Start_StateLevel2_platform (void) {
	startLevel_counter = 0;
	levelorientation = horizontal;
	SPRITES_8x16;

	pitdeathactive = true;
	nut_region = 0;
	deathmusicplayed = false;

	PlayMusic(quickstart, 1);

	//start the game off with a bow (full health)
	if (hasbow == true) {
		spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, 4, 49);
	}
	scroll_target = spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 4, 49);

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level2_platformmap), &level2_platformmap, collision_tiles, collision_tiles_down);
	
	Hud_Init(false);
	cutscenemode = enabled;
	isAcornMoving = false; //yes, it is moving
	FlagPole_Init();
	endlevel_counter = 0;
	LevelStart_Init(6,4);

	levelActorPos = 0;
	AddActors();

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel2_platform (void) {
	Hud_Update();
	AddActors();

	if (timerlevel == 0) {
		nutmeg_death = true;
	
		if (health == full) {
			lostbow = true;
			bow_counter = 0;
			if (nutmeg_direction == right) { bowanim = 8; }
			else if (nutmeg_direction == left) { bowanim = 9; }
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
	
	if (cutscenemode == enabled) {
		//Level Start!
		//Make Nutmeg Walk In
		if (startLevel_counter == 0) {
			cutscenewalkright = true;
		}
		else if (startLevel_counter == 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		else if (startLevel_counter == 100) {
			cutscenemode = disabled;

			if (levelbeat == false) {
				PlayMusic(mushrooms, 1);
			}
		}

		LevelStart_Update();
		if (startLevel_counter < 105) startLevel_counter++;
	}

	Water_Animate();
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

		endlevel_counter++;
	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && levelbeat == false && nutmeg_death == false) {
		FlagPole_Activate(244,13);

		levelbeat = true;
		endlevel_counter = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
	}
}