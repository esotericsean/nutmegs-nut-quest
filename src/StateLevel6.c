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
#include "Hud.h"
#include "LevelStart.h"

IMPORT_MAP (level6map);


UINT16 level6counter = 0;
UINT8 level6cameracount = 0;
UINT8 endlevel_counter6 = 0;

// BACKGROUND TILE COLOR PALETTES

//grass color palette - ORIGINAL
const UWORD pal_grass_original6[]    = { RGB(14, 30, 14), RGB( 1, 26,  0), RGB(19, 14, 0), RGB(0, 0, 0) };
//grass color palette - LIGHTER
const UWORD pal_grass_lighter6[]     = { RGB(20, 30, 22), RGB( 6, 29,  0), RGB(22, 18, 0), RGB(5, 5, 5) };
//grass color palette - EVEN LIGHTER
const UWORD pal_grass_evenlighter6[] = { RGB(27, 30, 28), RGB(15, 31, 11), RGB(28, 23, 0), RGB(12, 12, 12) };
//grass color palette - LIGHTEST!!!
const UWORD pal_grass_lightest6[]    = { RGB(31, 31, 31), RGB(29, 30, 28), RGB(30, 29, 26), RGB(24, 24, 24) };

//wood color palette - ORIGINAL
const UWORD pal_wood_original6[]    = { RGB(31, 31, 31), RGB(28, 24, 18), RGB(19, 14, 0), RGB(0, 0, 0) };
//wood color palette - LIGHTER
const UWORD pal_wood_lighter6[]     = { RGB(31, 31, 31), RGB(30, 26, 20), RGB(22, 18, 0), RGB(5, 5, 5) };
//wood color palette - EVEN LIGHTER
const UWORD pal_wood_evenlighter6[] = { RGB(31, 31, 31), RGB(30, 27, 24), RGB(28, 23, 0), RGB(12, 12, 12) };
//wood color palette - LIGHTEST!!!
const UWORD pal_wood_lightest6[]    = { RGB(31, 31, 31), RGB(30, 29, 28), RGB(30, 29, 26), RGB(24, 24, 24) };

// SPRITE COLOR PALETTES

//nutmeg color palette - ORIGINAL
const UWORD pal_nutmeg_original6[]    = { RGB(31, 31, 31), RGB(31, 27, 23), RGB(31, 17, 6), RGB(0, 0, 0) };
//nutmeg color palette - LIGHTER
const UWORD pal_nutmeg_lighter6[]     = { RGB(31, 31, 31), RGB(31, 28, 26), RGB(31, 20, 9), RGB(5, 5, 5) };
//nutmeg color palette - EVEN LIGHTER
const UWORD pal_nutmeg_evenlighter6[] = { RGB(31, 31, 31), RGB(31, 30, 28), RGB(31, 24, 13), RGB(12, 12, 12) };
//nutmeg color palette - LIGHTEST!!!
const UWORD pal_nutmeg_lightest6[]    = { RGB(31, 31, 31), RGB(31, 31, 30), RGB(30, 29, 28), RGB(22, 22, 22) };

//acorn color palette - ORIGINAL
const UWORD pal_acorn_original6[]	  = { RGB(31, 31, 31), RGB(30, 23, 17), RGB(20,  9,  0), RGB(10,  5,  1) };
//acorn color palette - LIGHTER
const UWORD pal_acorn_lighter6[]	  = { RGB(31, 31, 31), RGB(30, 25, 20), RGB(23, 12,  2), RGB(16,  7,  2) };
//acorn color palette - EVEN LIGHTER
const UWORD pal_acorn_evenlighter6[]  = { RGB(31, 31, 31), RGB(30, 28, 24), RGB(26, 16,  3), RGB(21, 11,  4) };
//acorn color palette - LIGHTEST!!!
const UWORD pal_acorn_lightest6[]	  = { RGB(31, 31, 31), RGB(30, 29, 25), RGB(30, 25, 17), RGB(29, 19, 10) };

//birdy color palette - ORIGINAL
const UWORD pal_birdy_original6[]	  = { RGB(31, 31, 31), RGB(31, 19, 2),  RGB(0,  16, 31), RGB(0, 0, 0) };
//birdy color palette - LIGHTER
const UWORD pal_birdy_lighter6[]	  = { RGB(31, 31, 31), RGB(31, 24, 5),  RGB(1,  21, 31), RGB(5, 5, 5) };
//birdy color palette - EVEN LIGHTER
const UWORD pal_birdy_evenlighter6[]  = { RGB(31, 31, 31), RGB(31, 27, 20), RGB(4,  25, 31), RGB(12, 12, 12) };
//birdy color palette - LIGHTEST!!!
const UWORD pal_birdy_lightest6[]	  = { RGB(31, 31, 31), RGB(31, 29, 25), RGB(12, 28, 31), RGB(22, 22, 22) };

//balloon color palette - ORIGINAL
const UWORD pal_balloon_original6[]	  = { RGB(31, 31, 31), RGB(30, 27, 26), RGB(31, 7, 5), RGB(0, 0, 0) };
//balloon color palette - LIGHTER
const UWORD pal_balloon_lighter6[]	  = { RGB(31, 31, 31), RGB(30, 28, 27), RGB(31, 11, 9), RGB(5, 5, 5) };
//balloon color palette - EVEN LIGHTER
const UWORD pal_balloon_evenlighter6[]	= { RGB(31, 31, 31), RGB(30, 30, 28), RGB(31, 17, 14), RGB(12, 12, 12) };
//balloon color palette - LIGHTEST!!!
const UWORD pal_balloon_lightest6[]	  = { RGB(31, 31, 31), RGB(30, 30, 28), RGB(31, 22, 20), RGB(20, 20, 20) };

//yellow color palette - ORIGINAL
const UWORD pal_yellow_original6[]	  = { RGB(31, 31, 31), RGB(28, 27, 9), RGB(22, 21, 5), RGB(0, 0, 0) };
//yellow color palette - LIGHTER
const UWORD pal_yellow_lighter6[]	  = { RGB(31, 31, 31), RGB(29, 28, 17), RGB(25, 24, 11), RGB(5, 5, 5) };
//yellow color palette - EVEN LIGHTER
const UWORD pal_yellow_evenlighter6[] = { RGB(31, 31, 31), RGB(30, 29, 21), RGB(26, 25, 16), RGB(12, 12, 12) };
//yellow color palette - LIGHTEST!!!
const UWORD pal_yellow_lightest6[]    = { RGB(31, 31, 31), RGB(30, 29, 24), RGB(27, 26, 20), RGB(22, 22, 22) };

//puff white palette change to light grey so you can see it throughout the level
//const UWORD pal_puff_original6[]	  = { RGB(31, 31, 31), RGB(31, 31, 31), RGB(31, 31, 31), RGB(31, 31, 31) };
const UWORD pal_puff_fixed6[]	      = { RGB(20, 20, 20), RGB(20, 20, 20), RGB(20, 20, 20), RGB(20, 20, 20) };

const UINT8 collision_tiles_level6[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
const UINT8 collision_tiles_down_level6[] = {29,30,31,32,0};

DECLARE_MUSIC(quickstart);
DECLARE_MUSIC(ruffles);
DECLARE_MUSIC(quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_camera;



void Start_StateLevel6() {
	level6counter = 0;
	levelorientation = horizontal;
	SPRITES_8x16;

	nut_region = 0;
	pitdeathactive = true;

	deathmusicplayed = false;

	PlayMusic(quickstart, 1);

	//testing:
	//health = full;
	//lostbow = false;

	//add butterfly so yellow palette is loaded first if bow isn't present
	SpriteManagerAdd(EnemyButterfly, 3*8, 4*8);
	
	//if health is full, add the bow
	if (health == full) { SpriteManagerAdd(SpriteNutmegBow, 4, 49); }
	//else if (health == low) {SpriteManagerAdd(SpriteNutmegBow, -10, -10); lostbow = false; } //add bow to set color palettes

	scroll_target = spr_camera = SpriteManagerAdd(SpriteCamera, 80, 12); //49
	spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 4, 49);

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level6map), &level6map, collision_tiles_level6, collision_tiles_down_level6);
	Hud_Init(false);


	cutscenemode = enabled;
	isAcornMoving = true;
	FlagPole_Init();
	LevelStart_Init(7,5);

	endlevel_counter6 = 0;

	level6cameracount = 0;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel6() {
	Hud_Update();

	if (timerlevel == 0)
	{
		nutmeg_death = true;
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
				SetState(StateOverworld1); // change to correct world
			}
		}

		nutmegdeathtimer++;
	}
	
	if (cutscenemode == enabled) {
		//Level Start!
		//Make Nutmeg Walk In
		if (level6counter == 0) {
			cutscenewalkright = true;
		}
		else if (level6counter == 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		else if (level6counter == 100) {
			cutscenemode = disabled;

			if (levelbeat == false) {
				PlayMusic(ruffles, 1);
			}
		}

		LevelStart_Update();
		if (level6counter < 105) level6counter++;
	}

	if (cutscenemode == disabled) {
		level6cameracount++;
		if (level6cameracount > 2) level6cameracount = 0;

		if (level6cameracount == 2) {
			//TranslateSprite (spr_camera, 1, 0);
			if (spr_camera->x < 237*8) { spr_camera->x++; } //stop moving at end
		}
	}

	//tile 237 stop checking
	if (spr_nutmeg->x < 237*8) {
		if (spr_nutmeg->x < spr_camera->x - 64) {
			spr_nutmeg->x = spr_camera->x - 64;
		}
		if (spr_nutmeg->x > spr_camera->x + 64) {
			spr_nutmeg->x = spr_camera->x + 64;
		}
	}

	FlagPole_Animate();
	
	if (levelbeat == true) {
		cutscenemode = enabled;
		cutscenewalkright = true;
		cutscenewalkleft = false;
		
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

		if (endlevel_counter6 >= 100) {
			SetState(StateOverworld1);
		}

		if (endlevel_counter6 < 250) endlevel_counter6++;

	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && levelbeat == false && nutmeg_death == false) {
		FlagPole_Activate(244,13);
		levelbeat = true;
		endlevel_counter6 = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
	}

	//switched puff to Nutmeg's palette, so leave it alone for this level
	/*if (spr_nutmeg->x > 13*8) {
		SetPalette(SPRITES_PALETTE, 3, 1, pal_puff_fixed6, _current_bank);
	}*/

	// Sprites:
	// 0 = yellow (bow, butterfly, star)
	// 1 = orange (nutmeg, puff)
	// 2 = red (balloon)
	// 3 = brown (acorn)
	// 4 = blue (bird)

	// set palettes while going through cloud
	// grass is 0, wood is 5, nutmeg is sprite 0
	if (spr_camera->x > 72*8 && spr_camera->x < 73*8) {
		SetPalette(BG_PALETTE, 0, 1, pal_grass_lighter6, _current_bank);
		SetPalette(BG_PALETTE, 5, 1, pal_wood_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 1, 1, pal_nutmeg_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 2, 1, pal_balloon_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 3, 1, pal_acorn_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 4, 1, pal_birdy_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 0, 1, pal_yellow_lighter6, _current_bank);
	}
	else if (spr_camera->x > 74*8 && spr_camera->x < 75*8) {
		SetPalette(BG_PALETTE, 0, 1, pal_grass_evenlighter6, _current_bank);
		SetPalette(BG_PALETTE, 5, 1, pal_wood_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 1, 1, pal_nutmeg_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 2, 1, pal_balloon_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 3, 1, pal_acorn_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 4, 1, pal_birdy_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 0, 1, pal_yellow_evenlighter6, _current_bank);
	}
	else if (spr_camera->x > 76*8 && spr_camera->x < 77*8) {
		SetPalette(BG_PALETTE, 0, 1, pal_grass_lightest6, _current_bank);
		SetPalette(BG_PALETTE, 5, 1, pal_wood_lightest6, _current_bank);
		SetPalette(SPRITES_PALETTE, 1, 1, pal_nutmeg_lightest6, _current_bank);
		SetPalette(SPRITES_PALETTE, 2, 1, pal_balloon_lightest6, _current_bank);
		SetPalette(SPRITES_PALETTE, 3, 1, pal_acorn_lightest6, _current_bank);
		SetPalette(SPRITES_PALETTE, 4, 1, pal_birdy_lightest6, _current_bank);
		SetPalette(SPRITES_PALETTE, 0, 1, pal_yellow_lightest6, _current_bank);
	}
	else if (spr_camera->x > 210*8 && spr_camera->x < 211*8) {
		SetPalette(BG_PALETTE, 0, 1, pal_grass_evenlighter6, _current_bank);
		SetPalette(BG_PALETTE, 5, 1, pal_wood_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 1, 1, pal_nutmeg_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 2, 1, pal_balloon_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 3, 1, pal_acorn_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 4, 1, pal_birdy_evenlighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 0, 1, pal_yellow_evenlighter6, _current_bank);
	}
	else if (spr_camera->x > 212*8 && spr_camera->x < 213*8) {
		SetPalette(BG_PALETTE, 0, 1, pal_grass_lighter6, _current_bank);
		SetPalette(BG_PALETTE, 5, 1, pal_wood_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 1, 1, pal_nutmeg_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 2, 1, pal_balloon_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 3, 1, pal_acorn_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 4, 1, pal_birdy_lighter6, _current_bank);
		SetPalette(SPRITES_PALETTE, 0, 1, pal_yellow_lighter6, _current_bank);
	}
	else if (spr_camera->x > 214*8 && spr_camera->x < 215*8) {
		SetPalette(BG_PALETTE, 0, 1, pal_grass_original6, _current_bank);
		SetPalette(BG_PALETTE, 5, 1, pal_wood_original6, _current_bank);
		SetPalette(SPRITES_PALETTE, 1, 1, pal_nutmeg_original6, _current_bank);
		SetPalette(SPRITES_PALETTE, 2, 1, pal_balloon_original6, _current_bank);
		SetPalette(SPRITES_PALETTE, 3, 1, pal_acorn_original6, _current_bank);
		SetPalette(SPRITES_PALETTE, 4, 1, pal_birdy_original6, _current_bank);
		SetPalette(SPRITES_PALETTE, 0, 1, pal_yellow_original6, _current_bank);
	}

	// 0-63:
	if (spr_camera->x > 0 && spr_camera->x <= 250 && nut_region <= 0) {
		//SpriteManagerAdd(SpriteBalloon, 7*8, 7*8);
		SpriteManagerAdd(SpriteBalloon, 13*8-2, 15*8);
		SpriteManagerAdd(SpritePuffLeft, 0*8, 13*8);
		SpriteManagerAdd(SpriteAcorn, 34*8, 12*8);
		SpriteManagerAdd(SpriteAcorn, 14*8, 10*8);
		SpriteManagerAdd(EnemyBirdy, 17*8, 10*8);
		SpriteManagerAdd(SpriteAcorn, 24*8, 10*8);
		SpriteManagerAdd(SpriteAcorn, 27*8, 10*8);
		SpriteManagerAdd(EnemyButterfly, 33*8, 7*8);
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_camera->x > 250 && spr_camera->x <= 500 && nut_region <= 1) {
		SpriteManagerAdd(SpriteAcorn, 52*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 60*8, 2*8);
		SpriteManagerAdd(SpriteAcorn, 63*8, 4*8);
		SpriteManagerAdd(SpriteAcorn, 66*8, 6*8);
		SpriteManagerAdd(SpriteBalloon, 71*8, 10*8);
    	nut_region = 2;
	}
	// Up to 125:
	else if (spr_camera->x > 500 && spr_camera->x <= 750 && nut_region <= 2) {
		SpriteManagerAdd(SpriteAcorn, 79*8, 3*8);
		SpriteManagerAdd(SpriteAcorn, 83*8, 8*8);
		SpriteManagerAdd(EnemyButterfly, 82*8, 8*8);
		SpriteManagerAdd(SpriteBalloon, 89*8, 14*8);
		SpriteManagerAdd(EnemyBirdy, 101*8, 5*8);
	    nut_region = 3;
	}
	// Up to 156:
	else if (spr_camera->x > 750 && spr_camera->x <= 1000 && nut_region <= 3) {
		SpriteManagerAdd(SpriteAcorn, 111*8, 7*8);
		SpriteManagerAdd(EnemyBirdy, 130*8, 9*8);
		SpriteManagerAdd(SpriteAcorn, 140*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 142*8, 7*8);
		SpriteManagerAdd(SpriteBalloon, 146*8, 9*8);
		SpriteManagerAdd(EnemyBirdy, 152*8, 5*8);
	    nut_region = 4;
	}
	// Up to 188:
	else if (spr_camera->x > 1000 && spr_camera->x <= 1250 && nut_region <= 4) {
		SpriteManagerAdd(SpriteBalloon, 163*8, 17*8);
		SpriteManagerAdd(EnemyButterfly, 184*8, 8*8);
		SpriteManagerAdd(SpriteAcorn, 185*8, 7*8);
		SpriteManagerAdd(SpriteAcorn, 185*8, 9*8);
	    nut_region = 5;
	}
	// Up to 219:
	else if (spr_camera->x > 1250 && spr_camera->x <= 1500 && nut_region <= 5) {
		SpriteManagerAdd(SpriteAcorn, 205*8, 12*8);
		SpriteManagerAdd(EnemyBirdy, 218*8, 10*8);
		SpriteManagerAdd(SpriteAcorn, 224*8, 7*8);
		nut_region = 6;
	}
	// Up to 250:
	else if (spr_camera->x > 1500 && spr_camera->x <= 1750 && nut_region <= 6) {
		SpriteManagerAdd(SpriteBalloon, 228*8, 16*8);
	    nut_region = 7;
	}
	else if (spr_camera->x > 1750 && spr_camera->x <= 2000 && nut_region <= 7) {
	    nut_region = 8;
	}
}