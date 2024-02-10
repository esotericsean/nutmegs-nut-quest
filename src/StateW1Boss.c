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
#include "Hud.h"

IMPORT_MAP (w1bossmap);


UINT16 w1bosscounter = 0;

UINT8 handpos;
UINT8 handphase;
UINT8 handhurt;
bool abletohurthand;
UINT8 handhealth;

const UINT8 collision_tiles_levelw1b[] = {44,45,46,47,58,51,70,71,72,73,74,75,76,77,78,79,80,81,0};
const UINT8 collision_tiles_down_levelw1b[] = {0};

DECLARE_MUSIC(thehands2);
DECLARE_MUSIC(quickdeath);
DECLARE_MUSIC(boss1win);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_hand;

static Sprite * spr_spatula;
static Sprite * spr_popsicle;

void Start_StateW1Boss() {
	w1bosscounter = 0;
	levelorientation = horizontal;
	SPRITES_8x16;

	nut_region = 0;
	pitdeathactive = true;

	deathmusicplayed = false;

	PlayMusic(thehands2, 1);

	if (hasbow == true) { SpriteManagerAdd(SpriteNutmegBow, 5*8, 1*8); }
	
	spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 5*8, 1*8);
	spr_hand = SpriteManagerAdd(EnemyHand, 17*8+32, 11*8+6); //start on right side

	SpriteManagerAdd(SpriteAcorn, 1*8+2, 14*8-4);
	SpriteManagerAdd(SpriteAcorn, 18*8-2, 14*8-4);

	InitScrollTiles(0, &w1bosstiles);
	InitScroll(BANK(w1bossmap), &w1bossmap, collision_tiles_levelw1b, collision_tiles_down_levelw1b);
	Hud_Init(true);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving

	handpos = 0; //start on right side

	// hand position chart //
	
	// 0 = idle, facing left, right side of screen
	// 1 = start to open, facing left, right side
	// 2 = hand open karate chop, facing left, right side
	// 3 = start to close, facing left, right side
	// 4 = hurt, facing left, right side

	// 5 = idle, facing right, left side
	// 6 = start to open, facing right, left side
	// 7 = hand open karate chop, facing right, left side
	// 8 = start to close, facing right, left side
	// 9 = hurt, facing right, left side

	handphase = 0; // start with Phase 1a

	// hand phase chart //

	// 0 = Phase 1a (hand enters from right side, throws spatula)
	// 1 = Phase 1b (hand enters from left side)

	handhealth = 0; // start off hand with full health
	abletohurthand = true; // start off being able to hurt the hand (disable after one jump per phase)

	cutscenemode = disabled;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateW1Boss() {
	Hud_Update();

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

	if (spr_spatula->x < 0) { SpriteManagerRemoveSprite (spr_spatula); }
	if (spr_popsicle->x > 20*8) { SpriteManagerRemoveSprite (spr_popsicle); }

	/* * * * * * * * * * * * * */
	/*      P H A S E   1      */
	/* * * * * * * * * * * * * */

	if (handphase == 0 || handphase == 1) {
		// Phase 1a - Hand enters from right and throws an object
			// reset to start position:
			if (w1bosscounter == 100) {
				spr_hand->x = 17*8+32;
				spr_hand->y = 11*8+6;
				handpos = 0;
				abletohurthand = true;
				handphase = 0; //Phase 1a
			}
			// move in and animate opening hand
			else if (w1bosscounter > 100 && w1bosscounter < 130) {
				if (w1bosscounter == 115) {
					handpos = 1; //start to open
				}
				spr_hand->x--;
			}
			// replease enemy
			else if (w1bosscounter == 133) {
				spr_spatula = SpriteManagerAdd(EnemySpatula, 16*8, 11*8);
			}
			// start to close hand animation
			else if (w1bosscounter == 150) {
				handpos = 3; //close
			}
			// move out
			else if (w1bosscounter > 175 && w1bosscounter < 210) {
				spr_hand->x++;
			}
		// End Phase 1a

		// Phase 1b - Hand enters from left and throws object (part 2 of phase 1)
			// reset to start position (left side):
			else if (w1bosscounter == 310) {
				spr_hand->x = 1*8-40;
				spr_hand->y = 11*8+6;
				handpos = 5;
				abletohurthand = true;
				handphase = 1; //Phase 1b
			}
			// move in and animate opening hand
			else if (w1bosscounter > 310 && w1bosscounter < 340) {
				if (w1bosscounter == 325) {
					handpos = 6; //start to open
				}
				spr_hand->x++;
			}
			// replease enemy
			else if (w1bosscounter == 343) {
				spr_popsicle = SpriteManagerAdd(EnemyPopsicle, 2*8, 11*8);
			}
			// start to close hand animation
			else if (w1bosscounter == 360) {
				handpos = 8; //close
			}
			// move out
			else if (w1bosscounter > 385 && w1bosscounter < 420) {
				spr_hand->x--;
			}
		// End Phase 1b
	}

	/* * * * * * * * * * * * * */
	/*      P H A S E   2      */
	/* * * * * * * * * * * * * */

	// only enter phase 2 if hand is offscreen and spatula/popsicle are offscreen
	// check position of hand and wait a certain amount of time to make sure thrown items are gone

	else if (handphase == 2 || handphase == 3) {
		// Phase 2a - Cola cans fall from sky
			if (w1bosscounter == 100) { SpriteManagerAdd(EnemyCola, 9*8+4, 0); }
			else if (w1bosscounter == 125) { SpriteManagerAdd(EnemyCola, 5*8, 0); }
			else if (w1bosscounter == 150) { SpriteManagerAdd(EnemyCola, 13*8, 0); }
		// End Phase 2a
		
		// Phase 2b - Hand does karate chop downwards on right side
			// reset to start position
			if (w1bosscounter == 175) {
				spr_hand->x = 17*8+32;
				spr_hand->y = 1*8+6;
				handpos = 2; //karate chop
				handhurt = 0;
				abletohurthand = true;
				handphase = 2;
			}
			// move in
			else if (w1bosscounter > 175 && w1bosscounter < 205) {
				spr_hand->x--;
			}
			// karate chop down
			else if (w1bosscounter >= 205 && w1bosscounter < 240) {
				spr_hand->y = spr_hand->y + 2;
			}
			// move out
			else if (w1bosscounter > 270 && w1bosscounter < 305) {
				spr_hand->x++;
			}
		// End Phase 2b

		// Phase 2c
			//reset to start position
			if (w1bosscounter == 405) {
				spr_hand->x = 1*8-40;
				spr_hand->y = 1*8+6;
				handpos = 7;
				handhurt = 0;
				abletohurthand = true;
				handphase = 3;
			}
			// move in
			else if (w1bosscounter > 405 && w1bosscounter < 435) {
				spr_hand->x++;
			}
			// karate chop down
			else if (w1bosscounter >= 435 && w1bosscounter < 470) {
				spr_hand->y = spr_hand->y + 2;
			}
			// move out
			else if (w1bosscounter > 500 && w1bosscounter < 535) {
				spr_hand->x--;
			}

		// End Phase 2c
	}

	/* * * * * * * * * * * * * * * */
	/*      Y O U   W I N !        */
	/* * * * * * * * * * * * * * * */

	else if (handphase == 4) {
		if (w1bosscounter == 5) {
			cutscenemode = enabled;
			PlayMusic(boss1win, 0);
		}

		if (w1bosscounter == 15) {
			SpriteManagerAdd (SpriteStarLeft, 9*8+4, 8*8);
			SpriteManagerAdd (SpriteStarRight, 9*8+4, 8*8);
		}

		if (w1bosscounter == 45) {
			SpriteManagerAdd (SpriteStarLeft, 9*8+4, 6*8);
			SpriteManagerAdd (SpriteStarRight, 9*8+4, 6*8);
		}

		if (w1bosscounter == 75) {
			SpriteManagerAdd (SpriteStarLeft, 9*8+4, 4*8);
			SpriteManagerAdd (SpriteStarRight, 9*8+4, 4*8);
		}

		if (w1bosscounter == 100) {
			cutscenemode = false;
		}

		if (w1bosscounter == 200) {
			SetState (StateOverworld1);

			//flagpole_activated = 1;
			levelbeat = true;
			//endlevel_counter = 0;
			cutscenemode = enabled;
		}
	}

	/* * * * * * * * * * * * * * * * * * * * */
	/*      C O U N T E R    R E S E T       */
	/* * * * * * * * * * * * * * * * * * * * */

	w1bosscounter++; //65000

	// if you hurt the hand 3 times in phase 1, advance to phase 2
	if (handhealth >= 3 && handphase == 0) {
		if (w1bosscounter >= 210) { handphase = 2; w1bosscounter = 0; abletohurthand = true; }
	}
	else if (handhealth >= 3 && handphase == 1) {
		if (w1bosscounter >= 420) { handphase = 2; w1bosscounter = 0; abletohurthand = true; }
	}

	// if you're in phase 1 and you haven't hurt the hand, reset counter and start phase 1 again
	if (w1bosscounter >= 420 && handhealth < 3) {
		w1bosscounter = 0;
		abletohurthand = true;
	}

	// if you're in phase 2 and you haven't hurt the hand, reset counter and start phase 1 again
	if (w1bosscounter >= 635 && (handhealth >= 3 && handhealth < 6)) {
		w1bosscounter = 0;
		abletohurthand = true;
		handhurt = false;
		handphase = 0;
	}

	if (w1bosscounter >= 635 && handhealth >= 6) { w1bosscounter = 0; handphase = 4; }
}