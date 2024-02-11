#ifndef GLOBALVARS_H_
#define GLOBALVARS_H_

// Nutmeg Physics Old
//#define walkSpeed 100
//#define runSpeed 200
//#define walkIncrease 50
//#define runIncrease 60
//#define slowDownSpeed 10
//#define respawnMoveSpeed 3

// Nutmeg Physics New
#define walkSpeed 200   // accelX = 200 as a max speed. This gets divided by 100, which is 2 pixels at a time movement speed.
#define runSpeed 200    // if you do any number between 100 and 199, it gives you 1 pixel at a time.
#define walkIncrease 50 //50
#define runIncrease 60
#define slowDownSpeed 10 //lower number for ice level
//#define respawnMoveSpeed 3 //unused

//player movement physics
extern INT16 accelY;
extern INT16 accelX;
extern UINT8 jumpPeak;
extern UINT8 runJump;

//random typedefs

typedef enum { false, true } bool;
typedef enum { grounded, inair } move_state;
typedef enum { enabled, disabled } switcher;
typedef enum { right, left } direction;
typedef enum { full, low } amount;
typedef enum { vertical, horizontal } orientation;

//powerups
extern amount health;
extern bool hasbow;

extern UINT8 bowanim;
extern bool lostbow;

extern UINT8 bow_counter;
extern switcher powerupleaf;
extern switcher powerupstar;

extern bool firstplay;


// the level we are currently at / playing
extern UINT8 level_current;

// the level we are moving towards
extern UINT8 level_next;

// the highest level we have unlocked
extern UINT8 level_max;

//health system - reset to 0 in StateCutscene1
//start with 0 acorns and 3 lives
extern UINT8 acorncounter;
extern UINT8 nutmeglives;
extern bool GameOver;
extern bool deathmusicplayed;
extern bool pitdeathactive;

// level timer countdown - controlled by Hud.c
extern UINT16 timerlevel;

//acorn animation
extern bool isAcornMoving;

//which direction is nutmeg facing
extern direction nutmeg_direction;

//which direction is gordon facing
extern direction gordon_direction;

extern move_state movestate;

/* * * * * * * * * * * * * * */
/*      c u t s c e n e      */
/*          m o d e          */
/*        n u t m e g        */
/* * * * * * * * * * * * * * */
extern switcher cutscenemode;
extern bool cutscenewalkleft;
extern bool cutscenewalkright;
extern bool cutscenerun;
extern bool cutscenejump;
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


//nutmeg sprite region
extern UINT8 nut_region;

//fish color palette location based on level
extern UINT8 fish_pal_loc;

//Nutmeg Stop Moving After Dying
extern UINT8 nutmegdeathmove;

//Sprite Limits if Vertical or Horizontal Level
extern orientation levelorientation;

//EnemyHand
extern UINT8 handpos;
extern UINT8 handphase;
extern bool abletohurthand;
extern UINT8 handhurt;
extern UINT8 handhealth;

#endif