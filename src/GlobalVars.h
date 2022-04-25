#ifndef GLOBALVARS_H
#define GLOBALVARS_H

// Nutmeg Physics Old
//#define walkSpeed 100
//#define runSpeed 200
//#define walkIncrease 50
//#define runIncrease 60
//#define slowDownSpeed 10
//#define respawnMoveSpeed 3

// Nutmeg Physics New
#define walkSpeed 200
#define runSpeed 200
#define walkIncrease 50
#define runIncrease 60
#define slowDownSpeed 10 //lower number for ice level
#define respawnMoveSpeed 3 //unused

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
typedef enum { full, low } amount;

//powerups
extern amount health;
extern UINT8 bowanim;
extern UINT8 acorncounter;
extern switcher powerupleaf;
extern switcher powerupstar;
extern UINT8 nutmeglives;

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
extern bool levelbeat;
extern UINT8 distance;
extern UINT8 W1LevelSelection;
extern UINT8 W2LevelSelection;

//nutmeg sprite region
extern UINT8 nut_region;

//world 1 things
extern const unsigned char level_water1[];
extern const unsigned char level_water2[];
extern const unsigned char level_water3[];
extern const unsigned char level_water_anim1[];
extern const unsigned char level_water_anim2[];
extern const unsigned char level_water_anim3[];
extern const unsigned char grey_33[];
extern const unsigned char grey_34[];
extern const unsigned char grey_35[];
extern const unsigned char grey_36[];
extern const unsigned char pink_37[];
extern const unsigned char pink_38[];
extern const unsigned char pink_39[];
extern const unsigned char pink_40[];
extern const unsigned char grey_41[];
extern const unsigned char grey_42[];
extern const unsigned char grey_43[];
extern const unsigned char grey_44[];
extern const unsigned char pink_45[];
extern const unsigned char pink_46[];
extern const unsigned char pink_47[];
extern const unsigned char pink_48[];
extern const unsigned char flagpole1[];
extern const unsigned char flagpole2[];
extern const unsigned char flagpole3[];
extern const unsigned char UpperL[];
extern const unsigned char LowerE[];
extern const unsigned char LowerV[];
extern const unsigned char LowerL[];
extern const unsigned char UpperS[];
extern const unsigned char LowerT[];
extern const unsigned char LowerA[];
extern const unsigned char LowerR[];
extern const unsigned char Exclam[];
extern const unsigned char BlankSky[];
extern const unsigned char Letter1[];
extern const unsigned char Letter2[];
extern const unsigned char Letter3[];
extern const unsigned char Letter4[];
extern const unsigned char Letter5[];
extern const unsigned char Letter6[];
extern const unsigned char Letter7[];
extern const unsigned char Letter8[];
extern const unsigned char Letter9[];
extern const unsigned char Letter10[];
extern const unsigned char Letter11[];
extern const UINT8 collision_tiles_level1[];
extern const UWORD pal_pink[];
extern const UINT16 bg_palette_level1[];
extern const UINT16 sprites_palette_level1[];

#endif