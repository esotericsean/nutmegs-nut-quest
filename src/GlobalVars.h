#ifndef GLOBALVARS_H_
#define GLOBALVARS_H_

//random typedefs

typedef enum { false, true } bool;
typedef enum { grounded, inair } move_state;
typedef enum { disabled, enabled  } switcher;
typedef enum { right, left } direction;
typedef enum { full, low } amount;
typedef enum { vertical, horizontal } orientation;


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

	// inital jump force (negative)
	INT16 initJumpY;
	
	// single extra jump power while holding jump button (positive)
	INT16 jumpY;
	
	// Minimum Y upwards speed (negative)
	INT16 jumpYMin;

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
    NutmegSpeedT *speeds;
	UINT8 lives;
	UINT8 acorns;
	
	amount health;

	// Set to true if nutmeg is currently swimming
	bool isSwimming;

	//which direction is nutmeg facing
	direction direction;
	move_state movestate;
	
	//powerups
	switcher powerupleaf; //enabled or disabled
	switcher powerupstar; //enabled or disabled

	//player movement physics
	INT16 accelX;
	INT16 accelY;
	UINT8 jumpPeak;
	UINT8 runJump;
	// dealing with the bow

	// does nutmeg have a bow?
	bool hasbow;
	UINT8 bowanim;
	bool lostbow;
	UINT8 bow_counter;

} NutmegT;

extern NutmegT nutmeg;

//powerups



extern bool firstplay;


// the level we are currently at / playing
extern UINT8 level_current;

// the level we are moving towards
extern UINT8 level_next;

// the highest level we have unlocked
extern UINT8 level_max;

//health system - reset to 0 in StateCutscene1

extern bool GameOver;


// level timer countdown - controlled by Hud.c
extern UINT16 timerlevel;



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

extern bool nutmeg_death;
extern bool nutmeg_pitdeath;
extern UINT8 nutmegdeathtimer;

/* * * * * * * * * * * * * * */
/*      c u t s c e n e      */
/*          m o d e          */
/*        g o r d o n        */
/* * * * * * * * * * * * * * */
extern switcher gordonmode; //cutscene or boss fight
extern bool gordonwalkleft;
extern bool gordonwalkright;
extern bool gordonrun;
extern bool gordonjump;

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

// if it is a spike level, and collision hurts nutmeg
extern bool isSpikeLevel;
extern bool isHorizontalGoalpost;

//Sprite Limits if Vertical or Horizontal Level
extern orientation levelorientation;

//nutmeg sprite region
extern UINT8 nut_region;

//Nutmeg Stop Moving After Dying
extern UINT8 nutmegdeathmove;

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