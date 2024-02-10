#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Sound.h"
#include "SpriteManager.h"
#include "../src/GlobalVars.h"

static const UINT8 anim_nutmeg_idle_right[] = {4, 1, 2, 3, 4};
static const UINT8 anim_nutmeg_idle_left[]  = {4, 1, 2, 3, 4};

static const UINT8 anim_nutmeg_walk_right[] = {4, 5, 6, 7, 8};
static const UINT8 anim_nutmeg_walk_left[]  = {4, 5, 6, 7, 8};

static const UINT8 anim_nutmeg_jump_right[] = {1, 9};
static const UINT8 anim_nutmeg_jump_left[]  = {1, 9};

static const UINT8 anim_nutmeg_fall_right[] = {1, 10};
static const UINT8 anim_nutmeg_fall_left[]  = {1, 10};

static const UINT8 anim_nutmeg_land_right[] = {1, 11};
static const UINT8 anim_nutmeg_land_left[]  = {1, 11};
   
static const UINT8 anim_nutmeg_hurt_right[] = {14, 12, 12, 12, 12, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14};
static const UINT8 anim_nutmeg_hurt_left[]  = {14, 12, 12, 12, 12, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14};

static const UINT8 anim_nutmeg_lostbow[] = {2, 11, 0};

extern Sprite *spr_nutmegbow;

// Declare a pointer to a sprite
Sprite * spr_camera;
Sprite * spr_nutmeg;

UINT8 nutmeglives;
UINT8 acorncounter;

// does nutmeg have a bow?
bool hasbow = true;

direction nutmeg_direction;
bool isjumping = true;

bool nutmeg_death = false;
bool nutmeg_pitdeath = false;
UINT8 nutmegdeathtimer = 0;
bool GameOver = false;

//cutscene mode!
switcher cutscenemode;
bool cutscenewalkleft;
bool cutscenewalkright;
bool cutscenerun;
bool cutscenejump;

//movement states
move_state movestate; //nutmeg starts in the air and falls to the ground

//player movement physics
INT16 accelY;
INT16 accelX;
UINT8 jumpPeak;
UINT8 runJump;

//storing collisions around player after movement
UINT8 collisionX;
UINT8 collisionY;
UINT8 groundCollision;

//powerups
amount health; //full or low
switcher powerupleaf; //enabled or disabled
switcher powerupstar; //enabled or disabled



UINT8 nutmegdeathmove = 0;

//if nutmeg loses her bow, add some kickback
UINT8 kickbackcounter;

//reset nutmeg's state back to default
void ResetState() {
    accelY = 0;
    accelX = 0;
    collisionX = 0;
    collisionY = 0;
    groundCollision = 0;
    jumpPeak = 0;
    runJump = 0;
    movestate = grounded;

    nutmeg_direction = right;

    cutscenewalkleft = false;
    cutscenewalkright = false;
    cutscenejump = false;
    cutscenerun = false;

    nutmegdeathtimer = 0;
    nutmeg_death = false;
    nutmeg_pitdeath = false;
    GameOver = false;

    nutmegdeathmove = 0;

    kickbackcounter = 0;
}

void Start_SpriteNutmeg() {
    spr_nutmeg = THIS;

    ResetState();

    THIS->lim_x = 500;
	THIS->lim_y = 144;
}

bool nutmegBow_update(void ) BANKED ;

void Update_SpriteNutmeg() {
    
    
    // extra life from 100 acorns
    if (acorncounter == 100) {
        nutmeglives++;
        // TODO - PLAY FUN SOUND HERE!
        acorncounter = 0;
        if (nutmeglives > 99) nutmeglives = 99;
    }

    // death
    if (nutmeg_death == true) {
        cutscenemode = true;

        nutmegdeathmove++;

        if (nutmeg_direction == left) {
            SetSpriteAnim(THIS, anim_nutmeg_hurt_left, 10);
            
            if (nutmegdeathmove < 10) accelX = 100;
            else accelX = 0;
        }
        else if (nutmeg_direction == right) {
            SetSpriteAnim(THIS, anim_nutmeg_hurt_right, 10);

            if (nutmegdeathmove < 10) accelX = -100;
            else accelX = 0;
        }

        if (nutmeg_pitdeath == true) {
            //remove bow if have it
            if (health == full) {
                lostbow = true;
                bow_counter = 0;
                if (nutmeg_direction == right) { bowanim = 8; }
                else if (nutmeg_direction == left) { bowanim = 9; }
            }

            SpriteManagerRemoveSprite(THIS);
        }
    }

    /* * * * * * * * * * * * * * * * * * * */
    /*           normal mode               */
    /* * * * * * * * * * * * * * * * * * * */
    if (cutscenemode == disabled) {
        // death from falling into pit/water
        // normally set to 126 and 200, testing 176 and 200
        if (THIS->y >= 176 && THIS->y <= 200 && nutmeg_death == false && pitdeathactive == true) {
            nutmeg_death = true;
            nutmeg_pitdeath = true;
            nutmegdeathtimer = 0;

            if (nutmeglives <= 0) { GameOver = true; }
            else { nutmeglives--; }
        }

        /* * * * * * * * * * * * * * * * * * * */
        /* left and right directional movement */
        /* * * * * * * * * * * * * * * * * * * */
        if (KEY_PRESSED(J_RIGHT)) {
            //sets it to the direction you pressed
            nutmeg_direction = right;
            //makes sure the sprites are facing the right way
            //SPRITE_UNSET_VMIRROR(THIS);
            THIS->mirror = NO_MIRROR;

            //while moving if you press b then run, otherwise walk
            if (KEY_PRESSED(J_B)) {
                accelX += runIncrease;
                if (accelX > runSpeed && movestate == grounded)
                    accelX = runSpeed;
            }
            else {
                accelX += walkIncrease;
                if (accelX > walkSpeed && movestate == grounded)
                    accelX = walkSpeed;
            }
        }

        if (KEY_PRESSED(J_LEFT)) {
            nutmeg_direction = left;
            //SPRITE_SET_VMIRROR(THIS);
            THIS->mirror = V_MIRROR;

            //run, otherwise walk
            if (KEY_PRESSED(J_B)) {
                accelX -= runIncrease;
                if (accelX < -runSpeed && movestate == grounded)
                    accelX = -runSpeed;
            }
            else {
                accelX -= walkIncrease;
                if (accelX < -walkSpeed && movestate == grounded)
                    accelX = -walkSpeed;
            }
        }

        /* * * * * * * * * * * * * * * * * * * */
        /*                 idle                */
        /* * * * * * * * * * * * * * * * * * * */
        if (keys == 0 && nutmeg_direction == right) {
            THIS->mirror = NO_MIRROR;
        }
        if (keys == 0 && nutmeg_direction == left) {
            THIS->mirror = V_MIRROR;
        }

        /* * * * * * * * * * * * * * * * * * * */
        /*                jump                 */
        /* * * * * * * * * * * * * * * * * * * */
        // If we are on ground and A is pressed, jump
        // Jump sound is played on every successful jump
        // Jump is controlled by reaching high enought acceleration
        // or hitting a wall with head
        // In both cases, we set peak to true and start falling
        // Note that we can't start running when jumping,
        // but we can keep the running speed if we start the jump from run
        if (movestate == grounded) {
            if (KEY_TICKED(J_A) && (nutmeg_death == false)) {
                isjumping = true;
                accelY = -150;
                jumpPeak = 0;
                movestate = inair;
                runJump = KEY_PRESSED(J_B) ? 1 : 0;
                //PlayFx(CHANNEL_1, 5, 0x71, 0x03, 0x44, 0xc8, 0x80);
                PlayFx(CHANNEL_1, 5, 0x17, 0x9f, 0xf3, 0xc9, 0xc4);

                //display a puff when jumping
                if (nutmeg_direction == right) {
                    SpriteManagerAdd(SpritePuffLeft, THIS->x-2, THIS->y-2);
                }
                else {
                    SpriteManagerAdd(SpritePuffRight, THIS->x+10, THIS->y-2);
                }
            }
        }
        else if (movestate == inair) {
            isjumping = true;

            if (collisionY != 0) {
                jumpPeak = 1;
            }

            if (jumpPeak == 0 && KEY_PRESSED(J_A) && accelY > -350) {
                accelY -= 20;
            }
            else if (accelY < 300) {
                accelY += 20;
                jumpPeak = 1;
            }

            if (runJump) {
                if (accelX < -runSpeed) accelX = -runSpeed;
                if (accelX > runSpeed) accelX = runSpeed;
            }
            else {
                if (accelX < -walkSpeed) accelX = -walkSpeed;
                if (accelX > walkSpeed) accelX = walkSpeed;
            }
        }

        /* * * * * * * * * * * * * * * * * * * */
        /*                move                 */
        /* * * * * * * * * * * * * * * * * * * */
        // Move player and check for collisions
        // Do two movements to get colliders from both directions
        collisionX = TranslateSprite(THIS, accelX / 100, 0);
        collisionY = TranslateSprite(THIS, 0, accelY / 100);

        /* * * * * * * * * * * * * * * * * * * */
        /*             X physics               */
        /* * * * * * * * * * * * * * * * * * * */
        // X physics
        // Stop movement if we hit something
        // Otherwise drag
        if (collisionX != 0) {
            accelX = 0;
        }
        else if (!KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT)) {
            if (accelX > 0) {
                if (accelX > slowDownSpeed) accelX -= slowDownSpeed;
                else accelX = 0;
            }
            else if (accelX < 0) {
                if (accelX < -slowDownSpeed) accelX += slowDownSpeed;
                else accelX = 0;
            }
        }

        /* * * * * * * * * * * * * * * * * * * */
        /*             Y physics               */
        /* * * * * * * * * * * * * * * * * * * */
        // Y physics
        // Drop down if we don't have ground under
        // Play audio on land
        // Start from step sound 6 on land to have start playing stepping audio when we walk quickly
        if (accelY > 0) {
            groundCollision = collisionY;

            if (groundCollision == 0) {
                movestate = inair;
                isjumping = true;
            }
            else {
                if (movestate == inair) {
                    //PlayFx(CHANNEL_4, 4, 0x32, 0x71, 0x73, 0x80);
                    movestate = grounded;
                }
                accelY = 100;
            }
        }
        else {
            groundCollision = 0;
            movestate = inair;
        }

        /* * * * * * * * * * * * * * * * * * * */
        /*             animation               */
        /* * * * * * * * * * * * * * * * * * * */
        //play correct animation based on current state & input
        if (movestate == grounded && nutmeg_death == false) {
            if (accelX < 100 && accelX > -100) {
                if (nutmeg_direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_idle_right, 5);
                    if (lostbow == false) { bowanim = 0; }
                }
                if (nutmeg_direction == left) {
                    SetSpriteAnim(THIS, anim_nutmeg_idle_left, 5);
                    if (lostbow == false) { bowanim = 1; }
                }
            }
            else if (KEY_PRESSED(J_B)) {
                if (nutmeg_direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_walk_right, 15);
                    if (lostbow == false) { bowanim = 2; }
                }
                if (nutmeg_direction == left) {
                    SetSpriteAnim(THIS, anim_nutmeg_walk_left, 15);
                    if (lostbow == false) { bowanim = 3; }
                }
            }
            else {
                if (nutmeg_direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_walk_right, 15);
                    if (lostbow == false) { bowanim = 2; }
                }
                if (nutmeg_direction == left) {
                    SetSpriteAnim(THIS, anim_nutmeg_walk_left, 15);
                    if (lostbow == false) { bowanim = 3; }
                }
            }
        }
        else if (movestate == inair && nutmeg_death == false) {
            if (accelY > 60) {
                if (nutmeg_direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_fall_right, 1);
                    if (lostbow == false) { bowanim = 6; }
                }
                if (nutmeg_direction == left) {
                    SetSpriteAnim(THIS, anim_nutmeg_fall_left, 1);
                    if (lostbow == false) { bowanim = 7; }
                }
            }
            else if (accelY < -60) {
                if (nutmeg_direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_jump_right, 1);
                    if (lostbow == false) { bowanim = 4; }
                }
                if (nutmeg_direction == left) {
                    SetSpriteAnim(THIS, anim_nutmeg_jump_left, 1);
                    if (lostbow == false) { bowanim = 5; }
                }
            }
        }

        /* * * * * * * * * * * * * * * * * * * */
        /*      kickback from losing bow       */
        /* * * * * * * * * * * * * * * * * * * */
        if (health == full && lostbow == true) {
            if (kickbackcounter < 25) {
                SetSpriteAnim(THIS, anim_nutmeg_lostbow, 30);

                if (nutmeg_direction == left) {
                    TranslateSprite (THIS, 1, 0);
                }
                else if (nutmeg_direction == right) {
                    TranslateSprite (THIS, -1, 0);
                }

                kickbackcounter++;
            }
        }
    }
    /* * * * * * * * * * * * * * * * * * * */
    /*           cutscenemode              */
    /* * * * * * * * * * * * * * * * * * * */
    else if (cutscenemode == enabled) {
        if (cutscenewalkright == true) {
            nutmeg_direction = right;
            THIS->mirror = NO_MIRROR;

            if (cutscenerun == true) {
                accelX += runIncrease;
                if (accelX > runSpeed && movestate == grounded)
                    accelX = runSpeed;
            }
            else {
                accelX += walkIncrease;
                if (accelX > 100 && movestate == grounded)
                    accelX = 100;
            }
        }

        if (cutscenewalkleft == true) {
            nutmeg_direction = left;
            THIS->mirror = V_MIRROR;

            if (cutscenerun == true) {
                accelX -= runIncrease;
                if (accelX < -runSpeed && movestate == grounded)
                    accelX = -runSpeed;
            }
            else {
                accelX -= walkIncrease;
                if (accelX < -100 && movestate == grounded)
                    accelX = -100;
            }
        }

        if (cutscenewalkleft == false && cutscenewalkright == false && nutmeg_direction == right) {
            THIS->mirror = NO_MIRROR;
        }
        if (cutscenewalkleft == false && cutscenewalkright == false && nutmeg_direction == left) {
            THIS->mirror = V_MIRROR;
        }

        if (movestate == inair) {
            isjumping = true;

            if (collisionY != 0) {
                jumpPeak = 1;
            }

            if (jumpPeak == 0 && KEY_PRESSED(J_A) && accelY > -350) {
                accelY -= 20;
            }
            else if (accelY < 300) {
                accelY += 20;
                jumpPeak = 1;
            }

            if (runJump) {
                if (accelX < -runSpeed) accelX = -runSpeed;
                if (accelX > runSpeed) accelX = runSpeed;
            }
            else {
                if (accelX < -100) accelX = -100;
                if (accelX > 100) accelX = 100;
            }
        }

        collisionX = TranslateSprite(THIS, accelX / 100, 0);
        collisionY = TranslateSprite(THIS, 0, accelY / 100);

        if (collisionX != 0) {
            accelX = 0;
        }
        else if (cutscenewalkleft == false && cutscenewalkright == false) {
            if (accelX > 0) {
                if (accelX > slowDownSpeed) accelX -= slowDownSpeed;
                else accelX = 0;
            }
            else if (accelX < 0) {
                if (accelX < -slowDownSpeed) accelX += slowDownSpeed;
                else accelX = 0;
            }
        }

        if (accelY > 0) {
            groundCollision = collisionY;

            if (groundCollision == 0) {
                movestate = inair;
                isjumping = true;
            }
            else {
                if (movestate == inair) {
                    //PlayFx(CHANNEL_4, 4, 0x32, 0x71, 0x73, 0x80);
                    movestate = grounded;
                }
                accelY = 100;
            }
        }
        else {
            groundCollision = 0;
            movestate = inair;
        }

        if (movestate == grounded && nutmeg_death == false) {
            if (accelX < 100 && accelX > -100) {
                if (nutmeg_direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_idle_right, 5);
                    if (lostbow == false) { bowanim = 0; }
                }
                if (nutmeg_direction == left) {
                    SetSpriteAnim(THIS, anim_nutmeg_idle_left, 5);
                    if (lostbow == false) { bowanim = 1; }
                }
            }
            else if (KEY_PRESSED(J_B)) {
                if (nutmeg_direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_walk_right, 15); //change to walk speed
                    if (lostbow == false) { bowanim = 2; }
                }
                if (nutmeg_direction == left) {
                    SetSpriteAnim(THIS, anim_nutmeg_walk_left, 15);   //run is speed 50
                    if (lostbow == false) { bowanim = 3; }
                }
            }
            else {
                if (nutmeg_direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_walk_right, 15);
                    if (lostbow == false) { bowanim = 2; }
                }
                if (nutmeg_direction == left) {
                    SetSpriteAnim(THIS, anim_nutmeg_walk_left, 15);
                    if (lostbow == false) { bowanim = 3; }
                }
            }
        }
        else if (movestate == inair && nutmeg_death == false) {
            if (accelY > 60) {
                if (nutmeg_direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_fall_right, 1);
                    if (lostbow == false) { bowanim = 6; }
                }
                if (nutmeg_direction == left) {
                    SetSpriteAnim(THIS, anim_nutmeg_fall_left, 1);
                    if (lostbow == false) { bowanim = 7; }
                }
            }
            else if (accelY < -60) {
                if (nutmeg_direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_jump_right, 1);
                    if (lostbow == false) { bowanim = 4; }
                }
                if (nutmeg_direction == left) {
                    SetSpriteAnim(THIS, anim_nutmeg_jump_left, 1);
                    if (lostbow == false) { bowanim = 5; }
                }
            }
        }
    }

    /*
    // update the bow after we are done updating, so the x & y positions can track us correctly
    if (spr_nutmegbow != NULL)
    {
        if (nutmegBow_update() == true);
        spr_nutmegbow = NULL;
    }
    */
}

void Destroy_SpriteNutmeg() {
}

void nutmeg_SetupGame(void) BANKED
{
    //health system
    acorncounter = 0;
    
    // TESTING - Should be 3 lives
    nutmeglives = 99; 

    health = full;
    lostbow = false;

    level_current = 0;
	level_next = 0;
	level_max = 0;
    
    // advance to the first level
    levelbeat = true;

    W1LevelSelection = 0;

    accelY = 0;
    accelX = 0;
    jumpPeak = 0;
    runJump = 0;
    nutmeg_direction = right;
    movestate = grounded;
    isjumping = false;
}

// call this when nutmeg has been hit
void nutmeg_hit(void) BANKED
{
    if (health == full) {
        lostbow = true;
        bow_counter = 0;
        if (nutmeg_direction == right) { bowanim = 8; }
        else if (nutmeg_direction == left) { bowanim = 9; }
    }
    else if (health == low) {
        nutmeg_death = true;
        nutmegdeathtimer = 0;
        
        if (nutmeglives <= 0) { GameOver = true; }
        else { nutmeglives--; }
    }
}
