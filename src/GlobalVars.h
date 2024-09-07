#ifndef GLOBALVARS_H_
#define GLOBALVARS_H_

//random typedefs

typedef enum { false, true } bool;
typedef enum { grounded, inair } move_state;
typedef enum { disabled, enabled  } switcher;
typedef enum { right, left } direction;
typedef enum { full, low } amount;
typedef enum { vertical, horizontal } orientation;

// set level.iceTileMin and level.iceTileMax to this value for no ice tiles
#define NO_ICE_TILES (255)

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
	
	// is dying from falling in a pit?
	bool isPitDeath;

	// a counter to moving nutmeg a bit while dying
	UINT8 deathmove;

	// a death countdown timer
	UINT8 deathtimer;
} NutmegT;

extern NutmegT nutmeg;

//powerups



extern bool firstplay;


// Info about the current level
typedef struct {
	// Is the level a water level?
	bool isWaterLevel;

	// if it is a spike level, and collision hurts nutmeg
	bool isSpikeLevel;

	// Min tile number for slippery ice tiles (set to 255 for no ice)
	UINT8 iceTileMin;

	// Max tile number for slippery ice tiles (set to 255 for no ice)
	UINT8 iceTileMax;

	//Sprite Limits if Vertical or Horizontal Level
	orientation orientation;

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

//EnemyHand
extern UINT8 handpos;
extern UINT8 handphase;
extern bool abletohurthand;
extern UINT8 handhurt;
extern UINT8 handhealth;


// LEVEL SPECIFIC VARIABLES


extern bool isHorizontalGoalpost;



//nutmeg sprite region
extern UINT8 nut_region;

extern bool deathmusicplayed;
extern bool pitdeathactive;

// END OF LEVEL SPECIFIC VARIABLES

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

#endif