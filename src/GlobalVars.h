#ifndef GLOBALVARS_H
#define GLOBALVARS_H

// Nutmeg Physics
#define walkSpeed 100
#define runSpeed 200
#define walkIncrease 50
#define runIncrease 60
#define slowDownSpeed 10
#define respawnMoveSpeed 3

//player movement physics
extern INT16 accelY;
extern INT16 accelX;
extern UINT8 jumpPeak;
extern UINT8 runJump;

//storing collisions around player after movement
extern UINT8 collisionX;
extern UINT8 collisionY;
extern UINT8 groundCollision;

//random typedefs
typedef enum { true, false } bool;
typedef enum { grounded, inair } move_state;
typedef enum { enabled, disabled } switcher;
typedef enum { right, left } direction;

//first time visiting overworld1
extern bool overworld1visited;

//acorn animation
extern bool isAcornMoving;

//which direction is nutmeg facing
extern direction nutmeg_direction;

//which direction is gordon facing
extern direction gordon_direction;

extern move_state movestate;
extern bool isjumping;

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
extern UINT8 W1LevelSelection;
extern UINT8 W2LevelSelection;

#endif