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
#include "SpriteNutmeg.h"

IMPORT_MAP (w1bossmap);

static UINT16 w1bosscounter = 0;

UINT8 handpos;
UINT8 handphase;
UINT8 handhurt;
bool abletohurthand;
UINT8 handhealth;
extern UINT8 collisionY;

static const UINT8 collision_tiles_levelw1b[] = {44,45,46,47,58,51,75, 0};
static const UINT8 collision_tiles_down_levelw1b[] = {0};

DECLARE_MUSIC(thehands2);
DECLARE_MUSIC(boss1win);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_hand;

static Sprite * spr_spatula;
static Sprite * spr_popsicle;

static UINT16 hand_defeat_x = (9 * 8) + 4;
static UINT16 hand_defeat_y = (8 * 8);
static const UINT16 nutmeg_center_x = (9 * 8) + 4;
static UINT16 nutmeg_victory_x = (9 * 8) + 4;
static UINT16 nutmeg_victory_y = (12 * 8);
static UINT8 handVictoryStage = 0;
static bool victoryBalloonsSpawned = false;

#ifdef CGB
static const UWORD pal_balloon_red[]  = { RGB(31, 31, 31), RGB(30, 27, 26), RGB(31, 7, 5), RGB(0, 0, 0) };
static const UWORD pal_balloon_blue[] = { RGB(31, 31, 31), RGB(20, 26, 31), RGB(9, 15, 31), RGB(0, 0, 0) };
#endif

static void Hand_EnableDamage(void) {
    abletohurthand = true;
}

static void Hand_DisableDamage(void) {
    abletohurthand = false;
}

static UINT16 clamp_sub_u16(UINT16 value, UINT8 dec) {
    return (value > dec) ? (value - dec) : value;
}

static const LevelT levelInfo = {
	.isWaterLevel = false,
	.isSpikeLevel = false,

	// No ice tiles and no solid water tiles in this boss level
	.iceTileMin = NO_ICE_TILES,
	.iceTileMax = NO_ICE_TILES,
	.waterSolidTileId = 0, // 0 means use default in code; we will override below at start

	// vertical or horizontal Level
	.orientation = horizontal,
	.isHorizontalGoalpost = false,

	// level timer info
	.hasTimer = false,
	.timer = 300,
	.timerclock = 0,
};

void Start_StateW1Boss (void) 
{
    level = levelInfo;
    // Explicitly disable solid water tile detection and overworld HUD in this level
    level.isOverworld = false;
    level.waterSolidTileId = NO_ICE_TILES;

    nut_region = 0;
    cutscenemode = disabled;
    handVictoryStage = 0;

	PlayMusic(thehands2, 1);

	nutmeg_Add(5*8, 1*8);
	spr_hand = SpriteManagerAdd(EnemyHand, 17*8+32, 11*8+6); //start on right side

	SpriteManagerAdd(SpriteAcorn, 1*8+2, 14*8-4);
	SpriteManagerAdd(SpriteAcorn, 18*8-2, 14*8-4);

	InitScrollTiles(0, &w1bosstiles);
	InitScroll(BANK(w1bossmap), &w1bossmap, collision_tiles_levelw1b, collision_tiles_down_levelw1b);
	Hud_Init();

	
	w1bosscounter = 0;

	handpos = 0; //start on right side
    victoryBalloonsSpawned = false;

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
	Hand_EnableDamage(); // start off being able to hurt the hand (disable after one jump per phase)

	SPRITES_8x16;
	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateW1Boss (void) 
{
	Hud_Update();

	if (spr_spatula && spr_spatula->x <= 8u) { SpriteManagerRemoveSprite (spr_spatula); spr_spatula = 0; }
	if (spr_popsicle && spr_popsicle->x > 20*8) { SpriteManagerRemoveSprite (spr_popsicle); spr_popsicle = 0; }

    // Final blow: immediately transition to win phase with FX at the hand location
    if ((handhealth >= 6) && (handphase != 4)) {
        handphase = 4;
        w1bosscounter = 0;
        Hand_DisableDamage();
        handhurt = 1;

        // Remember where the hand was defeated so we can play effects there
        if (spr_hand) {
            hand_defeat_x = spr_hand->x;
            hand_defeat_y = spr_hand->y;
            SpriteManagerRemoveSprite(spr_hand);
            spr_hand = 0;
        } else {
            hand_defeat_x = nutmeg_victory_x;
            hand_defeat_y = nutmeg_victory_y;
        }

        // Single celebratory star at hand location
        AddStarPair(hand_defeat_x, hand_defeat_y);

        // Prepare a victory bounce; lock controls via cutscene mode until she lands
        cutscenemode = enabled;
        cutscenewalkleft = false;
        cutscenewalkright = false;
        handVictoryStage = 0;
        INT16 launchSpeedX = 120; // moderate horizontal shove toward center
        INT16 shove = (hand_defeat_x > nutmeg_center_x) ? -launchSpeedX : launchSpeedX;
        nutmeg.speedX = shove;
        if (nutmeg.speedX > nutmeg.speeds->runMaxX) nutmeg.speedX = nutmeg.speeds->runMaxX;
        if (nutmeg.speedX < -nutmeg.speeds->runMaxX) nutmeg.speedX = -nutmeg.speeds->runMaxX;
        if (nutmeg.speedY > -260) nutmeg.speedY = -260; // ensure an upward arc without shooting too high
        if (nutmeg.speedX > 0) {
            cutscenewalkright = true;
            cutscenewalkleft = false;
        } else if (nutmeg.speedX < 0) {
            cutscenewalkleft = true;
            cutscenewalkright = false;
        }
        nutmeg.jumpPeak = 0;
        nutmeg.movestate = inair;
        nutmeg.wallCoyoteFrames = 0;
        nutmeg.isGliding = false;
        nutmeg.direction = (nutmeg.speedX >= 0) ? right : left;
        collisionY = 0; // allow airborne arc
    }

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
				Hand_EnableDamage();
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
				Hand_EnableDamage();
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
				Hand_EnableDamage();
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
				Hand_EnableDamage();
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
        if (handVictoryStage == 0) {
            // Wait for Nutmeg to land from the celebration bounce
            if (nutmeg.movestate == grounded && nutmeg.speedY >= 0) {
                handVictoryStage = 1;
                w1bosscounter = 0; // start post-landing timeline
                if (spr_nutmeg) {
                    nutmeg_victory_x = spr_nutmeg->x;
                    nutmeg_victory_y = (spr_nutmeg->y > 2u) ? (spr_nutmeg->y - 2u) : spr_nutmeg->y;
                    spr_nutmeg->x = nutmeg_victory_x;
                    spr_nutmeg->y = nutmeg_victory_y;
                }
                nutmeg_SetIdlePose();
                nutmeg.speedX = 0;
                nutmeg.speedY = 0;
                nutmeg.offsetX = 0;
                nutmeg.offsetY = 0;
                nutmeg.movestate = grounded;
                nutmeg.jumpPeak = 1;
                nutmeg.wallCoyoteFrames = 0;
                nutmeg.isGliding = false;
                nutmeg.direction = right;
                collisionY = 1;
                cutscenewalkleft = false;
                cutscenewalkright = false;
            }
        } else {
            // Hold Nutmeg in place during the victory cutscene
            if (spr_nutmeg) {
                spr_nutmeg->x = nutmeg_victory_x;
                spr_nutmeg->y = nutmeg_victory_y;
            }
            nutmeg.speedX = 0;
            nutmeg.speedY = 0;
            nutmeg.offsetX = 0;
            nutmeg.offsetY = 0;
            nutmeg.movestate = grounded;
            nutmeg.jumpPeak = 1;
            nutmeg.wallCoyoteFrames = 0;
            nutmeg.isGliding = false;
            nutmeg.direction = right;
            collisionY = 1;
        }

        if (handVictoryStage >= 1) {
            if (w1bosscounter == 40) {
                PlayMusic(boss1win, 0);
            }

            if (!victoryBalloonsSpawned && w1bosscounter >= 30) {
#ifdef CGB
                SetPalette(SPRITES_PALETTE, 5, 1, pal_balloon_red, _current_bank);
                SetPalette(SPRITES_PALETTE, 6, 1, pal_balloon_blue, _current_bank);
#endif
                UINT16 balloonY = clamp_sub_u16(nutmeg_victory_y, 8);
                bool spawnedAny = false;
                Sprite* balloonLeft = SpriteManagerAdd(SpriteBalloon, clamp_sub_u16(nutmeg_victory_x, 12), balloonY);
                if (balloonLeft) {
#ifdef CGB
                    SPRITE_SET_CGB_PALETTE(balloonLeft, 5);
#endif
                    balloonLeft->custom_data[0] = 0;
                    spawnedAny = true;
                }
                Sprite* balloonRight = SpriteManagerAdd(SpriteBalloon, nutmeg_victory_x + 16u, clamp_sub_u16(balloonY, 4));
#ifdef CGB
                if (balloonRight) { SPRITE_SET_CGB_PALETTE(balloonRight, 6); }
#endif
                if (balloonRight) {
                    balloonRight->custom_data[0] = 2; // BALLOON_FLAG_SLOW_RISE
                    spawnedAny = true;
                }
                if (spawnedAny) {
                    victoryBalloonsSpawned = true;
                }
            }

            if (w1bosscounter == 240) {
                SetState (StateOverworld);

                //flagpole_activated = 1;
                levelbeat = true;
                cutscenemode = enabled;
            }
        }
	}

	/* * * * * * * * * * * * * * * * * * * * */
	/*      C O U N T E R    R E S E T       */
	/* * * * * * * * * * * * * * * * * * * * */

	w1bosscounter++; //65000

	// if you hurt the hand 3 times in phase 1, advance to phase 2
	if (handhealth >= 3 && handphase == 0) {
		if (w1bosscounter >= 210) { handphase = 2; w1bosscounter = 0; Hand_EnableDamage(); }
	}
	else if (handhealth >= 3 && handphase == 1) {
		if (w1bosscounter >= 420) { handphase = 2; w1bosscounter = 0; Hand_EnableDamage(); }
	}

	// if you're in phase 1 and you haven't hurt the hand, reset counter and start phase 1 again
	if (w1bosscounter >= 420 && handhealth < 3) {
		w1bosscounter = 0;
		Hand_EnableDamage();
	}

	// if you're in phase 2 and you haven't hurt the hand, reset counter and start phase 1 again
	if (w1bosscounter >= 635 && (handhealth >= 3 && handhealth < 6)) {
		w1bosscounter = 0;
		Hand_EnableDamage();
		handhurt = false;
		handphase = 0;
	}

	if ((handphase != 4) && w1bosscounter >= 635 && handhealth >= 6) { w1bosscounter = 0; handphase = 4; }
}