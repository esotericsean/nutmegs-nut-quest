#ifndef GLOBALVARS_H_
#define GLOBALVARS_H_

// Pull Sprite typedef/tag from engine for correct type matching
#include "SpriteManager.h"

//random typedefs

// Avoid redefining bool if included elsewhere
#ifndef __BOOLEAN_DEFINED
typedef enum { false, true } bool;
#define __BOOLEAN_DEFINED
#endif
typedef enum { grounded, inair } move_state;
typedef enum { disabled, enabled  } switcher;
typedef enum { right, left } direction;
typedef enum { full, low } amount;
typedef enum { vertical, horizontal } orientationE;

// set level.iceTileMin and level.iceTileMax to this value for no ice tiles
#define NO_ICE_TILES (255)

#define MAX_LEVEL_TRACKING (32)

typedef struct NutmegSpeed {
	// left right friction when 
	INT16 frictionX;
	
	// single increase while running
	INT16 runIncX;

	// max X while running
	INT16 runMaxX;

	INT16 walkIncX;
	INT16 walkMaxX;

	// MAX x in a cutscene
	INT16 cutsceneMaxX;

	// initial jump force off an enemy (positive)
	INT16 enemyBounceY;

	// inital jump force (positive)
	INT16 initJumpY;
	
	// single extra jump power while holding jump button (positive)
	INT16 jumpY;
	
	// Minimum Y upwards speed (positive)
	INT16 jumpYMax;

	// X friction while not on the ground (positive)
	INT16 airFrictionX;

	// initial fall speed, if nutmeg walks off an edge (positive)
	INT16 fallInitY;

	// single extra fall speed per frame
	INT16 fallIncY;

	// maximum fall speed
	INT16 fallMaxY;

	// maximum fall speed while gliding
	INT16 fallGlideMaxY;

} NutmegSpeedT;

typedef struct Nutmeg {

    const NutmegSpeedT *speeds;
	UINT8 lives;
	UINT8 acorns;
    UINT8 goldenAcorns;
	
	amount health;

	// Set to true if nutmeg is currently swimming
	bool isSwimming;
	
	// set to true if nutmeg is gliding
	bool isGliding;

	// set to true if nutmeg is standing on ice
	bool isOnIce;

	//which direction is nutmeg facing
	direction direction;
	move_state movestate;
	
	//powerups
	switcher powerupleaf; //enabled or disabled
	switcher powerupstar; //enabled or disabled

	//player movement physics
	INT16 speedX;
	INT16 speedY;

	// player movement offsets - 100 here = 1 pixel movement
	INT16 offsetX;
	INT16 offsetY;

	UINT8 jumpPeak;

	// initial jump force off an enemy (positive) (copies from current move speeds)
	INT16 enemyBounceY;

	// dealing with the bow

	// does nutmeg have a bow?
	bool hasbow;
	UINT8 bowanim;
	bool lostbow;
	UINT8 bow_counter;

	// DEATH vars
	// is nutmeg dying
	bool isDying;
    bool pendingDeath;

	// a death countdown timer
	UINT8 deathtimer;
    UINT8 pendingDeathTimer;

	// brief hurt flash / invincibility
	UINT8 hurtFlashCounter;
	bool isInvincible;

    // death handling helpers
    bool deathSoundPlayed;
    UINT16 deathFrames;
    UINT8 deathState; // 0=none,1=init,2=fall,3=done

	// --- Wall movement ---
	// automatic wall slide when airborne and touching a wall
	bool isWallSliding;
	// side of the wall we are sliding on (right/left)
	direction wallSide;
	// last contacted wall side for coyote timing
	direction lastWallSide;
	// few frames after leaving wall where wall-jump remains allowed
	UINT8 wallCoyoteFrames;
	// cooldown before being able to re-grab a wall after a wall jump
	UINT8 wallRegrabCooldown;
	// short lock to prevent immediate glide right after wall jump
	UINT8 wallJumpGlideLock;

	// pause frames when picking up a powerup (freezes movement even midair)
	UINT8 pickupPauseFrames;
} NutmegT;

extern NutmegT nutmeg;

//powerups

extern bool isPaused;

extern bool levelGoldenAcornFound;

extern bool levelCompleted[MAX_LEVEL_TRACKING];
extern bool levelGoldenCollected[MAX_LEVEL_TRACKING];

extern UINT8 level_playing;
extern UINT8 highest_level_completed;

void GameProgress_InitIfNeeded(void) BANKED;


// Info about the current level
typedef struct {
	// Is the level a water level?
	bool isWaterLevel;

	// Is this the overworld (map) state? Used for HUD behavior
	bool isOverworld;

	// if it is a spike level, and collision hurts nutmeg
	bool isSpikeLevel;

	// Min tile number for slippery ice tiles (set to 255 for no ice)
	UINT8 iceTileMin;

	// Max tile number for slippery ice tiles (set to 255 for no ice)
	UINT8 iceTileMax;

	// Optional per-level solid water tile id (VRAM tile id for water fill). 0 uses default
	UINT8 waterSolidTileId;

	//Sprite Limits if Vertical or Horizontal Level
	orientationE orientation;

	// Is the goalpost in this level horizontal?
	bool isHorizontalGoalpost;

	// Does this level have a timer
	bool hasTimer;

	// level timer countdown 
	UINT16 timer;

	// frame counter for single timerlevel count
	UINT8 timerclock;
} LevelT;

extern LevelT level;

// the level we are currently at / playing
extern UINT8 level_current;

// the level we are moving towards
extern UINT8 level_next;

// the highest level we have unlocked
extern UINT8 level_max;

//health system - reset to 0 in StateCutscene1

extern bool GameOver;

//which direction is gordon facing
extern direction gordon_direction;

// Global game stats (persist across levels until new game)
typedef struct GameStats {
    // Total acorns collected across the whole game
    UINT32 totalAcorns;
    // Total enemies defeated (any kill source)
    UINT32 totalEnemyKills;
    // Number of times the player took damage (hit events)
    UINT32 totalDamageTaken;
    // Total deaths (life losses)
    UINT32 totalDeaths;
    // Total completed levels (incremented when returning to overworld after a clear)
    UINT32 totalLevelsCompleted;
    // Total powerups collected (bow, 1-ups, etc.)
    UINT32 totalPowerups;
    UINT16 totalGoldenAcorns;
} GameStatsT;

extern GameStatsT gameStats;



/* * * * * * * * * * * * * * */
/*      c u t s c e n e      */
/*          m o d e          */
/*        n u t m e g        */
/* * * * * * * * * * * * * * */
extern switcher cutscenemode;
extern bool cutscenewalkleft;
extern bool cutscenewalkright;


/* * * * * * * * * * * * * * */
/*      c u t s c e n e      */
/*          m o d e          */
/*        g o r d o n        */
/* * * * * * * * * * * * * * */
extern bool gordonwalkleft;
extern bool gordonwalkright;

//level selection
extern bool levelbeat;
extern UINT8 W1LevelSelection;

extern UINT16 levelStartCounter;
extern UINT8 levelEndCounter;

// frames to wait at the flagpole (victory music playing) before returning to
// the overworld - must stay below the 250 cap used when incrementing
#define LEVEL_END_DELAY (200)

//EnemyHand
extern UINT8 handpos;
extern UINT8 handphase;
extern bool abletohurthand;
extern UINT8 handhurt;
extern UINT8 handhealth;


// LEVEL SPECIFIC VARIABLES

//nutmeg sprite region
extern UINT8 nut_region;

// END OF LEVEL SPECIFIC VARIABLES

// Wind system (used in windy levels like 1-5)
extern bool windEnabled;
extern INT8 windGroundIdle;
extern INT8 windGroundRight;
extern INT8 windGroundLeft;
extern INT8 windAirNone;
extern INT8 windAirRight;
extern INT8 windAirLeft;
extern UINT8 windGroundMaxForward; // 0 = no cap; else max speedX when walking into wind on ground

typedef struct {
	UINT8 x;
	UINT8 y;
} nutPosT;


// PLATFORMS
#define PLATFORM_TYPE_BACK_AND_FORTH (0)
#define PLATFORM_TYPE_WRAP_TOP_BOTTOM (1)
#define PLATFORM_TYPE_WAITING_TO_DROP (2)
#define PLATFORM_TYPE_SHAKING (3)
#define PLATFORM_TYPE_DROPPING (4)

void Platform_Setup (Sprite *s, INT8 x, INT8 y, UINT8 type, UINT8 steps) BANKED;
void SpriteAcornFreeze(Sprite *acorn) BANKED;

// in SpriteStar.c - Add a pair of left and right stars
void AddStarPair (UINT16 x, UINT16 y) BANKED;
void AddStarPairWide (UINT16 x, UINT16 y) BANKED;

void AddPuffPair (UINT16 x, UINT16 y) BANKED;
#endif