#include "Banks/SetBank2.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Sound.h"
#include "SpriteManager.h"

#include "../src/GlobalVars.h"
//#include "../res/src/nutmegbow.h"
#include "../res/src/star.h"

const UINT8 anim_nutmeg_idle_right[] = {4, 1, 2, 3, 4};
const UINT8 anim_nutmeg_idle_left[]  = {4, 1, 2, 3, 4};

const UINT8 anim_nutmeg_walk_right[] = {4, 5, 6, 7, 8};
const UINT8 anim_nutmeg_walk_left[]  = {4, 5, 6, 7, 8};

const UINT8 anim_nutmeg_jump_right[] = {1, 9};
const UINT8 anim_nutmeg_jump_left[]  = {1, 9};

const UINT8 anim_nutmeg_fall_right[] = {1, 10};
const UINT8 anim_nutmeg_fall_left[]  = {1, 10};

const UINT8 anim_nutmeg_land_right[] = {1, 11};
const UINT8 anim_nutmeg_land_left[]  = {1, 11};
   
const UINT8 anim_nutmeg_hurt_right[] = {2, 12, 0}; //flashes blank frame
const UINT8 anim_nutmeg_hurt_left[]  = {2, 12, 0};

direction nutmeg_direction;
bool isjumping = true;

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

//scoring
UINT8 getAcorns = 0;

//powerups
amount health; //full or low
UINT8 acorncounter; //100 resets to 0 and adds to nutmeglives
switcher powerupleaf; //enabled or disabled
switcher powerupstar; //enabled or disabled
UINT8 nutmeglives; //start with 3

// Declare a pointer to a sprite
struct Sprite * spr_nutmeg2;
struct Sprite * spr_camera;
//extern struct Sprite * spr_nutmegbow;

// 0 = idle (5)
// 1 = walking (15)
// 2 = running (50)
// 3 = static (0)
//extern UINT8 bowanim;
//INT8 bowoffsetX;
//INT8 bowoffsetY;

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

    //bowoffsetX = 0;
    //bowoffsetY = 0;
}

void Start_SpriteNutmeg1() {
    THIS->coll_x = 13;
	THIS->coll_y = 8;
	THIS->coll_w = 6;
	THIS->coll_h = 8;

    //movestate = inair;
    //spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, THIS->x + 11, THIS->y);

    ResetState();

    //NR52_REG = 0x80; //Enables sound, you should always setup this first
	//NR51_REG = 0xFF; //Enables all channels (left and right)
	//NR50_REG = 0x77; //Max volume
}

void Update_SpriteNutmeg1() {
    UINT8 i;
    struct Sprite* spr;
    
    /*
    if (movestate == inair) {
        bowoffsetX += accelX/100;
        bowoffsetY += accelY/100;
    }
    */
    /*
    if (movestate == inair) {
        //bowoffsetX += accelX/100;
        bowoffsetY -= jumpPeak;
    }
    */
    //spr_nutmegbow->x = THIS->x + bowoffsetX;
	//spr_nutmegbow->y = THIS->y + bowoffsetY;

    /*
    if (nutmeg_direction == right) {
        SPRITE_UNSET_VMIRROR(spr_nutmegbow);
        spr_nutmegbow->x = THIS->x + bowoffsetX;
	    spr_nutmegbow->y = THIS->y + bowoffsetY;
    }
    else if (nutmeg_direction == left) {
        SPRITE_SET_VMIRROR(spr_nutmegbow);
        spr_nutmegbow->x = THIS->x - bowoffsetX;
	    spr_nutmegbow->y = THIS->y + bowoffsetY;
    }
    */

    if (cutscenemode == disabled) {
        /* * * * * * * * * * * * * * * * * * * */
        /* left and right directional movement */
        /* * * * * * * * * * * * * * * * * * * */
        if (KEY_PRESSED(J_RIGHT)) {
            //this flips it if it was facing the other way
            if (nutmeg_direction == left) {
                THIS->coll_x = 13;
                THIS->coll_y = 8;
                THIS->coll_w = 6;
                THIS->coll_h = 8;

                TranslateSprite(THIS, -16, 0);
            }
            
            //sets it to the direction you pressed
            nutmeg_direction = right;
            //makes sure the sprites are facing the right way
            SPRITE_UNSET_VMIRROR(THIS);

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
            if (nutmeg_direction == right) {
                THIS->coll_x = -5;
                THIS->coll_y = 8;
                THIS->coll_w = 6;
                THIS->coll_h = 8;

                TranslateSprite(THIS, 16, 0);
            }

            nutmeg_direction = left;
            SPRITE_SET_VMIRROR(THIS);

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
            //SetSpriteAnim(THIS, anim_nutmeg_idle_right, 5);
            SPRITE_UNSET_VMIRROR(THIS);
            //bowanim = 0;
        }
        if (keys == 0 && nutmeg_direction == left) {
            //SetSpriteAnim(THIS, anim_nutmeg_idle_left, 5);
            SPRITE_SET_VMIRROR(THIS);
            //bowanim = 0;
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
            if (KEY_TICKED(J_A)) {
                isjumping = true;
                accelY = -150;
                jumpPeak = 0;
                movestate = inair;
                runJump = KEY_PRESSED(J_B) ? 1 : 0;
                //PlayFx(CHANNEL_1, 5, 0x71, 0x03, 0x44, 0xc8, 0x80);
                PlayFx(CHANNEL_1, 5, 0x17, 0x9f, 0xf3, 0xc9, 0xc4);
                
                /*
                //display a star when jumping
                if (nutmeg_direction == right) SpriteManagerAdd(SpriteStarLeft, THIS->x+8, THIS->y+8);
                else SpriteManagerAdd(SpriteStarRight, THIS->x, THIS->y+8);
                */

                //display a puff when jumping
                if (nutmeg_direction == right) {
                    SpriteManagerAdd(SpritePuffLeft, THIS->x+8, THIS->y+7);
                }
                else {
                    SpriteManagerAdd(SpritePuffRight, THIS->x, THIS->y+7);
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
                    PlayFx(CHANNEL_4, 4, 0x32, 0x71, 0x73, 0x80);
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
        if (movestate == grounded) {
            if (accelX < 100 && accelX > -100) {
                if (nutmeg_direction == right) {
                    //bowanim = 0;
                    //spr_nutmegbow->x = THIS->x + 11;
	                //spr_nutmegbow->y = THIS->y;
                    //bowoffsetX = 11;
                    //bowoffsetY = 0;
                    //SPRITE_UNSET_VMIRROR(spr_nutmegbow);
                    SetSpriteAnim(THIS, anim_nutmeg_idle_right, 5);
                }
                if (nutmeg_direction == left) {
                    //bowanim = 0;
                    //spr_nutmegbow->x = THIS->x - 3;
	                //spr_nutmegbow->y = THIS->y;
                    //bowoffsetX = -3;
                    //bowoffsetY = 0;
                    //SPRITE_SET_VMIRROR(spr_nutmegbow);
                    SetSpriteAnim(THIS, anim_nutmeg_idle_left, 5);
                }
            }
            else if (KEY_PRESSED(J_B)) {
                if (nutmeg_direction == right) {
                    //bowanim = 2;
                    //bowoffsetX = 20;
                    //bowoffsetY = 1;
                    //SPRITE_UNSET_VMIRROR(spr_nutmegbow);
                    SetSpriteAnim(THIS, anim_nutmeg_walk_right, 15);
                }
                if (nutmeg_direction == left) {
                    //bowanim = 2;
                    //bowoffsetX = -12;
                    //bowoffsetY = 1;
                    //SPRITE_SET_VMIRROR(spr_nutmegbow);
                    SetSpriteAnim(THIS, anim_nutmeg_walk_left, 15);
                }
            }
            else {
                if (nutmeg_direction == right) {
                    //bowanim = 1;
                    //bowoffsetX = 18;
                    //bowoffsetY = 1;
                    //SPRITE_UNSET_VMIRROR(spr_nutmegbow);
                    SetSpriteAnim(THIS, anim_nutmeg_walk_right, 15);
                }
                if (nutmeg_direction == left) {
                    //bowanim = 1;
                    //bowoffsetX = -10;
                    //bowoffsetY = 1;
                    //SPRITE_SET_VMIRROR(spr_nutmegbow);
                    SetSpriteAnim(THIS, anim_nutmeg_walk_left, 15);
                }
            }
        }
        else {
            if (accelY > 60) {
                if (nutmeg_direction == right) {
                    //bowanim = 3;
                    //bowoffsetX = 11;
                    //bowoffsetY = 0;
                    //SPRITE_UNSET_VMIRROR(spr_nutmegbow);
                    SetSpriteAnim(THIS, anim_nutmeg_fall_right, 1);
                }
                if (nutmeg_direction == left) {
                    //bowanim = 3;
                    //bowoffsetX = -3;
                    //bowoffsetY = 0;
                    //SPRITE_SET_VMIRROR(spr_nutmegbow);
                    SetSpriteAnim(THIS, anim_nutmeg_fall_left, 1);
                }
            }
            else if (accelY < -60) {
                if (nutmeg_direction == right) {
                    //bowanim = 3;
                    //bowoffsetX = 11;
                    //bowoffsetY = 0;
                    //SPRITE_UNSET_VMIRROR(spr_nutmegbow);
                    SetSpriteAnim(THIS, anim_nutmeg_jump_right, 1);
                }
                if (nutmeg_direction == left) {
                    //bowanim = 3;
                    //bowoffsetX = -3;
                    //bowoffsetY = 0;
                    //SPRITE_SET_VMIRROR(spr_nutmegbow);
                    SetSpriteAnim(THIS, anim_nutmeg_jump_left, 1);
                }
            }
        }
        
        /* * * * * * * * * * * * * * * * * * * * */
        /*             right side                */
        /* * * * * * * * * * * * * * * * * * * * */
        if (nutmeg_direction == right) {
            spr_nutmeg2->x = THIS->x + 16;
            spr_nutmeg2->y = THIS->y;
        }
        else if (nutmeg_direction == left) {
            spr_nutmeg2->x = THIS->x - 16;
            spr_nutmeg2->y = THIS->y;
        }

        if (nutmeg_direction == right) {
            spr_camera->x = THIS->x;
            spr_camera->y = THIS->y;
        }
        else if (nutmeg_direction == left) {
            spr_camera->x = THIS->x - 16;
            spr_camera->y = THIS->y;
        }
        //end
    }
    /* * * * * * * * * * * * * * * * * * * */
    /*           cutscenemode              */
    /* * * * * * * * * * * * * * * * * * * */
    else if (cutscenemode == enabled) {
        if (cutscenewalkright == true) {
            if (nutmeg_direction == left) {
                THIS->coll_x = 13;
                THIS->coll_y = 8;
                THIS->coll_w = 6;
                THIS->coll_h = 8;

                TranslateSprite(THIS, -16, 0);
            }
            
            nutmeg_direction = right;
            SPRITE_UNSET_VMIRROR(THIS);

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
            if (nutmeg_direction == right) {
                THIS->coll_x = -5;
                THIS->coll_y = 8;
                THIS->coll_w = 6;
                THIS->coll_h = 8;

                TranslateSprite(THIS, 16, 0);
            }

            nutmeg_direction = left;
            SPRITE_SET_VMIRROR(THIS);

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
            SPRITE_UNSET_VMIRROR(THIS);
        }
        if (cutscenewalkleft == false && cutscenewalkright == false && nutmeg_direction == left) {
            SPRITE_SET_VMIRROR(THIS);
        }

        if (movestate == grounded) {
            //disable jumping
            /*
            if (KEY_TICKED(J_A)) {
                isjumping = true;
                accelY = -150;
                jumpPeak = 0;
                movestate = inair;
                runJump = KEY_PRESSED(J_B) ? 1 : 0;
                PlayFx(CHANNEL_1, 5, 0x17, 0x9f, 0xf3, 0xc9, 0xc4);
                
                if (nutmeg_direction == right) SpriteManagerAdd(SpritePuffLeft, THIS->x+8, THIS->y+7);
                else SpriteManagerAdd(SpritePuffRight, THIS->x, THIS->y+7);
            }
            */
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
                    PlayFx(CHANNEL_4, 4, 0x32, 0x71, 0x73, 0x80);
                    movestate = grounded;
                }
                accelY = 100;
            }
        }
        else {
            groundCollision = 0;
            movestate = inair;
        }

        if (movestate == grounded) {
            if (accelX < 100 && accelX > -100) {
                if (nutmeg_direction == right) {
                    //bowanim = 0;
                    SetSpriteAnim(THIS, anim_nutmeg_idle_right, 5);
                }
                if (nutmeg_direction == left) {
                    //bowanim = 0;
                    SetSpriteAnim(THIS, anim_nutmeg_idle_left, 5);
                }
            }
            else if (KEY_PRESSED(J_B)) {
                if (nutmeg_direction == right) {
                    //bowanim = 1;
                    SetSpriteAnim(THIS, anim_nutmeg_walk_right, 15); //change to walk speed
                }
                if (nutmeg_direction == left) {
                    //bowanim = 1;
                    SetSpriteAnim(THIS, anim_nutmeg_walk_left, 15);   //run is speed 50
                }
            }
            else {
                if (nutmeg_direction == right) {
                    //bowanim = 1;
                    SetSpriteAnim(THIS, anim_nutmeg_walk_right, 15);
                }
                if (nutmeg_direction == left) {
                    //bowanim = 1;
                    SetSpriteAnim(THIS, anim_nutmeg_walk_left, 15);
                }
            }
        }
        else {
            if (accelY > 60) {
                if (nutmeg_direction == right) {
                    //bowanim = 3;
                    SetSpriteAnim(THIS, anim_nutmeg_fall_right, 1);
                }
                if (nutmeg_direction == left) {
                    //bowanim = 3;
                    SetSpriteAnim(THIS, anim_nutmeg_fall_left, 1);
                }
            }
            else if (accelY < -60) {
                if (nutmeg_direction == right) {
                    //bowanim = 3;
                    SetSpriteAnim(THIS, anim_nutmeg_jump_right, 1);
                }
                if (nutmeg_direction == left) {
                    //bowanim = 3;
                    SetSpriteAnim(THIS, anim_nutmeg_jump_left, 1);
                }
            }
        }
        
        if (nutmeg_direction == right) {
            spr_nutmeg2->x = THIS->x + 16;
            spr_nutmeg2->y = THIS->y;
        }
        else if (nutmeg_direction == left) {
            spr_nutmeg2->x = THIS->x - 16;
            spr_nutmeg2->y = THIS->y;
        }

        if (nutmeg_direction == right) {
            spr_camera->x = THIS->x;
            spr_camera->y = THIS->y;
        }
        else if (nutmeg_direction == left) {
            spr_camera->x = THIS->x - 16;
            spr_camera->y = THIS->y;
        }
    }
    //end movement

    /* * * * * * * * * * * * * * * * * * * */
    /*         items and enemies           */
    /* * * * * * * * * * * * * * * * * * * */
    SPRITEMANAGER_ITERATE(i, spr) {
        if (spr->type == SpriteAcorn) {
            if (CheckCollision(THIS, spr)) {
                SpriteManagerRemove(i);
                getAcorns += 1;
                PlayFx(CHANNEL_1, 10, 0x00, 0x81, 0x83, 0xA3, 0x87);
                //PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
                //PlayFx(CHANNEL_4, 4, 0x0C, 0x41, 0x30, 0xC0);
            }
        }

        /*
        if (spr->type == SpritePowerLeaf) {
            if (CheckCollision(THIS, spr)) {
                SpriteManagerRemove(i);
                //getAcorns += 1;
                PlayFx(CHANNEL_1, 10, 0x00, 0x81, 0x83, 0xA3, 0x87);
                PlayFx(CHANNEL_4, 4, 0x0C, 0x41, 0x30, 0xC0);
            }
        }
        */

        //kill butterfly if jump on it
        if (spr->type == EnemyButterfly && movestate == inair && accelY > 0) {
            if (CheckCollision(THIS, spr)) {
                SpriteManagerRemove(i);
                PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
                isjumping = true;
                accelY = -600;
                jumpPeak = 0;
                movestate = inair;
                runJump = KEY_PRESSED(J_B) ? 1 : 0;
                
                if (nutmeg_direction == right) {
                    SpriteManagerAdd(SpriteStarLeft, THIS->x+16, THIS->y+8);
                    SpriteManagerAdd(SpriteStarRight, THIS->x+16, THIS->y+8);
                }
                else if (nutmeg_direction == left) {
                    SpriteManagerAdd(SpriteStarLeft, THIS->x-4, THIS->y+8);
                    SpriteManagerAdd(SpriteStarRight, THIS->x-4, THIS->y+8);
                }
            }
        }
        //die if touch butterfly
        else if (spr->type == EnemyButterfly && accelY < 0) {
            if (CheckCollision(THIS, spr)) {
                SetState(StateOverworld1);
            }
        }

        //kill bunny if jump on it
        if (spr->type == EnemyBunny && movestate == inair && accelY > 0) {
            if (CheckCollision(THIS, spr)) {
                SpriteManagerRemove(i);
                PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
                isjumping = true;
                accelY = -600;
                jumpPeak = 0;
                movestate = inair;
                runJump = KEY_PRESSED(J_B) ? 1 : 0;

            if (nutmeg_direction == right) {
                SpriteManagerAdd(SpriteStarLeft, THIS->x+16, THIS->y+8);
                SpriteManagerAdd(SpriteStarRight, THIS->x+16, THIS->y+8);
            }
            else if (nutmeg_direction == left) {
                SpriteManagerAdd(SpriteStarLeft, THIS->x-4, THIS->y+8);
                SpriteManagerAdd(SpriteStarRight, THIS->x-4, THIS->y+8);
            }
            }
        }
        //die if touch bunny
        else if (spr->type == EnemyBunny && movestate == grounded) {
            if (CheckCollision(THIS, spr)) {
                SetState(StateOverworld1);
            }
        }

        /*
        if (spr->type == EnemyFish && movestate == inair && accelY > 0) {
            if (CheckCollision(THIS, spr)) {
                SpriteManagerRemove(i);
                PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
                isjumping = true;
                accelY = -250;
                jumpPeak = 0;
                movestate = inair;
                runJump = KEY_PRESSED(J_B) ? 1 : 0;

            if (nutmeg_direction == right) {
                SpriteManagerAdd(SpriteStarLeft, THIS->x+16, THIS->y+8);
                SpriteManagerAdd(SpriteStarRight, THIS->x+16, THIS->y+8);
            }
            else if (nutmeg_direction == left) {
                SpriteManagerAdd(SpriteStarLeft, THIS->x-4, THIS->y+8);
                SpriteManagerAdd(SpriteStarRight, THIS->x-4, THIS->y+8);
            }
            }
        }
        */
    }
}

void Destroy_SpriteNutmeg1() {
}