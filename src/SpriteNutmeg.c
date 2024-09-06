#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Sound.h"
#include "SpriteManager.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

// These speed structs are used by enemies fns, 
// so they need to live in ram (or in bank 0)

// all the speed parameters for nutmeg while she is in a normal level
NutmegSpeedT groundSpeed = {
	.frictionX = 30,
	.runIncX = 60,
	.runMaxX = 200,
	.walkIncX = 50,
	.walkMaxX = 200,
    .enemyBounceY = 500,
    .cutsceneMaxX = 100,
	.initJumpY = 150,
	.jumpY = 20,
	.jumpYMax = 330,
	.fallInitY = 100,
	.fallIncY = 20,
	.fallMaxY = 300,
	.fallGlideMaxY = 130
};

// all the speed parameters for nutmeg while she is in a normal level
NutmegSpeedT iceGroundSpeed = {
	.frictionX = 00,
	.runIncX = 3,
	.runMaxX = 200,
	.walkIncX = 5,
	.walkMaxX = 200,
    .enemyBounceY = 500,
    .cutsceneMaxX = 100,
	.initJumpY = 150,
	.jumpY = 20,
	.jumpYMax = 330,
	.fallInitY = 100,
	.fallIncY = 20,
	.fallMaxY = 300,
	.fallGlideMaxY = 130
};

// all the speed parameters for nutmeg while she is underwater
NutmegSpeedT waterSpeed = {
	.frictionX = 15,
	.runIncX = 50,
	.runMaxX = 160,
	.walkIncX = 40,
	.walkMaxX = 160,
    .cutsceneMaxX = 100,
    .enemyBounceY = 250,
	.initJumpY = 100,
	.jumpY = 20,
	.jumpYMax = 200,
	.fallInitY = 100,
	.fallIncY = 5,
	.fallMaxY = 150,
	.fallGlideMaxY = 100
};


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

static const UINT8 anim_nutmeg_glide[] = {1, 15};

static const UINT8 anim_nutmeg_swim[] = {2, 16, 17}; //The speed of the animation in SetSpriteAnim(THIS, anim_nutmeg_swim, 5); needs to be tested to see how fast it should animate

static const UINT8 anim_nutmeg_lostbow[] = {2, 11, 0};

extern Sprite *spr_nutmegbow;

// Declare a pointer to a sprite
Sprite * spr_camera;
Sprite * spr_nutmeg;

NutmegT nutmeg;

bool GameOver = false;

//cutscene mode!
switcher cutscenemode;
bool cutscenewalkleft;
bool cutscenewalkright;


//storing collisions around player after movement
UINT8 collisionX;
UINT8 collisionY;


bool isHorizontalGoalpost = false;

//if nutmeg loses her bow, add some kickback
UINT8 kickbackcounter;

//reset nutmeg's state back to default
void ResetState(void) {
    nutmeg.speedY = 0;
    nutmeg.speedX = 0;
    
    nutmeg.offsetX = 0;
    nutmeg.offsetY = 0;

    collisionX = 0;
    collisionY = 0;
    nutmeg.jumpPeak = 0;
    nutmeg.runJump = 0;
    nutmeg.movestate = grounded;

    nutmeg.direction = right;

    cutscenewalkleft = false;
    cutscenewalkright = false;

    nutmeg.deathtimer = 0;
    nutmeg.isDying = false;
    nutmeg.isPitDeath = false;
    GameOver = false;

    nutmeg.deathmove = 0;

    kickbackcounter = 0;

    // TESTING
    //nutmeg.isSwimming = true;
    //nutmeg.speeds = &waterSpeed;
    nutmeg.speeds = &groundSpeed;
}


void Start_SpriteNutmeg(void) {
    spr_nutmeg = THIS;

    ResetState();

    THIS->lim_x = 500;
	THIS->lim_y = 144;
    SetSpriteAnim(spr_nutmeg, anim_nutmeg_idle_left, 5);

    if (level.isWaterLevel)
    {
         nutmeg.speeds = &waterSpeed;
         nutmeg.isSwimming = true;
    }
    else
    {
         nutmeg.speeds = &groundSpeed;
         nutmeg.isSwimming = false;
    }
}

// Create nutmeg sprite at x,y (and her bow if required)
Sprite *nutmeg_Add (uint16_t x, uint16_t y) BANKED
{
	if (nutmeg.hasbow == true) {
		spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, x, y);
	}
	
    spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, x, y);
    return spr_nutmeg;
}

static INT8 MoveX (void)
{
    INT8 r = 0;
    while (nutmeg.offsetX <= -100)
    {
        nutmeg.offsetX += 100;
        r --;
    }
    while (nutmeg.offsetX >= 100)
    {
        nutmeg.offsetX -= 100;
        r ++;
    }
    return r;
}

static INT8 MoveY (void)
{
    INT8 r = 0;
    while (nutmeg.offsetY <= -100)
    {
        nutmeg.offsetY += 100;
        r --;
    }
    while (nutmeg.offsetY >= 100)
    {
        nutmeg.offsetY -= 100;
        r ++;
    }
    return r;
}


void nutmegBow_update(void ) BANKED ;

// returns true if removed
static void update_whileDead(void)
{
    cutscenemode = enabled;

    nutmeg.deathmove++;

    if (nutmeg.direction == left) {
        SetSpriteAnim(THIS, anim_nutmeg_hurt_left, 10);
        
        if (nutmeg.deathmove < 10) nutmeg.speedX = nutmeg.speeds->cutsceneMaxX;
        else nutmeg.speedX = 0;
    }
    else if (nutmeg.direction == right) {
        SetSpriteAnim(THIS, anim_nutmeg_hurt_right, 10);

        if (nutmeg.deathmove < 10) nutmeg.speedX = -nutmeg.speeds->cutsceneMaxX;
        else nutmeg.speedX = 0;
    }

    if (nutmeg.isPitDeath == true) {
        SpriteManagerRemoveSprite(THIS);
    }
}

static void update_inCutscene(void)
{
    if (cutscenewalkright == true) 
    {
        nutmeg.direction = right;
        THIS->mirror = NO_MIRROR;

        nutmeg.speedX += nutmeg.speeds->walkIncX;
        if (nutmeg.speedX > nutmeg.speeds->cutsceneMaxX && nutmeg.movestate == grounded)
            nutmeg.speedX = nutmeg.speeds->cutsceneMaxX;

    }

    if (cutscenewalkleft == true) {
        nutmeg.direction = left;
        THIS->mirror = V_MIRROR;

        nutmeg.speedX -= nutmeg.speeds->walkIncX;
        if (nutmeg.speedX < -nutmeg.speeds->cutsceneMaxX && nutmeg.movestate == grounded)
            nutmeg.speedX = -nutmeg.speeds->cutsceneMaxX;
    }
  
    if (nutmeg.movestate == inair) {

        if (collisionY != 0) {
            nutmeg.jumpPeak = 1;
        }

        if (nutmeg.speedY < nutmeg.speeds->fallMaxY) {
            nutmeg.speedY += nutmeg.speeds->fallIncY;
            nutmeg.jumpPeak = 1;
        }

        if (nutmeg.speedX < -nutmeg.speeds->cutsceneMaxX) nutmeg.speedX = -nutmeg.speeds->cutsceneMaxX;
        if (nutmeg.speedX > nutmeg.speeds->cutsceneMaxX) nutmeg.speedX = nutmeg.speeds->cutsceneMaxX;
    }

    // apply speed to position
    nutmeg.offsetX += nutmeg.speedX;
    nutmeg.offsetY += nutmeg.speedY;

    INT8 delta = MoveX();
    collisionX = TranslateSprite(THIS, delta, 0);
    
    delta = MoveY();
    collisionY = TranslateSprite(THIS, 0, delta);

    if (collisionX != 0) {
        nutmeg.speedX = 0;
        nutmeg.offsetX = 0;
    }
    else if (cutscenewalkleft == false && cutscenewalkright == false) {
        if (nutmeg.speedX > 0) {
            if (nutmeg.speedX > nutmeg.speeds->frictionX) 
            {
                nutmeg.speedX -= nutmeg.speeds->frictionX;
            }
            else nutmeg.speedX = 0;
        }
        else if (nutmeg.speedX < 0) {
            if (nutmeg.speedX < -nutmeg.speeds->frictionX) 
            {
                nutmeg.speedX += nutmeg.speeds->frictionX;
            }
            else nutmeg.speedX = 0;
        }
    }


    if (collisionY == 0) {
        nutmeg.movestate = inair;
    }
    else {
        nutmeg.movestate = grounded;
        
        // We need to move down in order to hit the ground each turn
        nutmeg.speedY = 100;
        nutmeg.offsetY = 0;
    }

    if (nutmeg.isDying == false)
    {
        if (nutmeg.movestate == grounded) {
            if (nutmeg.speedX < nutmeg.speeds->cutsceneMaxX && nutmeg.speedX > -nutmeg.speeds->cutsceneMaxX) {
                if (nutmeg.direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_idle_right, 5);
                    nutmeg.bowanim = 0;
                }
                else {
                    SetSpriteAnim(THIS, anim_nutmeg_idle_left, 5);
                    nutmeg.bowanim = 1;
                }
            }
            else {
                if (nutmeg.direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_walk_right, 15);
                    nutmeg.bowanim = 2;
                }
                else {
                    SetSpriteAnim(THIS, anim_nutmeg_walk_left, 15);
                    nutmeg.bowanim = 3;
                }
            }
        }
        else if (nutmeg.movestate == inair) {
            if (nutmeg.speedY > 60) {
                if (nutmeg.direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_fall_right, 1);
                    nutmeg.bowanim = 6;
                }
                else  {
                    SetSpriteAnim(THIS, anim_nutmeg_fall_left, 1);
                    nutmeg.bowanim = 7;
                }
            }
            else if (nutmeg.speedY < -60) {
                if (nutmeg.direction == right) {
                    SetSpriteAnim(THIS, anim_nutmeg_jump_right, 1);
                    nutmeg.bowanim = 4;
                }
                else {
                    SetSpriteAnim(THIS, anim_nutmeg_jump_left, 1);
                    nutmeg.bowanim = 5;
                }
            }
        }
    }
}

void update_aliveInControl (void)
{ 
    // death from falling off the bottom of the screen
    if (THIS->y >= 176 && THIS->y <= 200 && pitdeathactive == true) {
        nutmeg.isDying = true;
        nutmeg.isPitDeath = true;
        nutmeg.deathtimer = 0;

        if (nutmeg.lives <= 0) { GameOver = true; }
        else { nutmeg.lives--; }
    }

    /* * * * * * * * * * * * * * * * * * * */
    /* left and right directional movement */
    /* * * * * * * * * * * * * * * * * * * */
    if (KEY_PRESSED(J_RIGHT)) {
        //sets it to the direction you pressed
        nutmeg.direction = right;
        //makes sure the sprites are facing the right way
        THIS->mirror = NO_MIRROR;

        //while moving if you press b then run, otherwise walk
        if (KEY_PRESSED(J_B)) {
            nutmeg.speedX += nutmeg.speeds->runIncX;
            if (nutmeg.speedX > nutmeg.speeds->runMaxX && nutmeg.movestate == grounded)
                nutmeg.speedX = nutmeg.speeds->runMaxX;
        }
        else {
            nutmeg.speedX += nutmeg.speeds->walkIncX;
            if (nutmeg.speedX > nutmeg.speeds->walkMaxX && nutmeg.movestate == grounded)
                nutmeg.speedX = nutmeg.speeds->walkMaxX;
        }
    }

    if (KEY_PRESSED(J_LEFT)) {
        nutmeg.direction = left;
        //SPRITE_SET_VMIRROR(THIS);
        THIS->mirror = V_MIRROR;

        //run, otherwise walk
        if (KEY_PRESSED(J_B)) {
            nutmeg.speedX -= nutmeg.speeds->runIncX;
            if (nutmeg.speedX < -nutmeg.speeds->runMaxX && nutmeg.movestate == grounded)
                nutmeg.speedX = -nutmeg.speeds->runMaxX;
        }
        else {
            nutmeg.speedX -= nutmeg.speeds->walkIncX;
            if (nutmeg.speedX < -nutmeg.speeds->walkMaxX && nutmeg.movestate == grounded)
                nutmeg.speedX = -nutmeg.speeds->walkMaxX;
        }
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
    if (nutmeg.movestate == grounded) {
        if (KEY_TICKED(J_A)) {
            nutmeg.speedY = -nutmeg.speeds->initJumpY;
            nutmeg.jumpPeak = 0;
            nutmeg.movestate = inair;
            nutmeg.runJump = KEY_PRESSED(J_B) ? 1 : 0;
            
            //PlayFx(CHANNEL_1, 5, 0x71, 0x03, 0x44, 0xc8, 0x80);
            PlayFx(CHANNEL_1, 5, 0x17, 0x9f, 0xf3, 0xc9, 0xc4);

            //display a puff when jumping
            if (nutmeg.direction == right) {
                SpriteManagerAdd(SpritePuffLeft, THIS->x-2, THIS->y-2);
            }
            else {
                SpriteManagerAdd(SpritePuffRight, THIS->x+10, THIS->y-2);
            }
        }
    }
    else if (nutmeg.movestate == inair) {
        if (collisionY != 0) {
            nutmeg.jumpPeak = 1;
        }

        if (nutmeg.jumpPeak == 0 && KEY_PRESSED(J_A) && nutmeg.speedY > -nutmeg.speeds->jumpYMax) {
            nutmeg.speedY -= nutmeg.speeds->jumpY;
        }
        else if (nutmeg.speedY < nutmeg.speeds->fallMaxY) {
            nutmeg.speedY += nutmeg.speeds->fallIncY;
            nutmeg.jumpPeak = 1;
        }
        
        // if nutmeg is swimming, she can "jump" again once she starts falling a little bit
        if ((nutmeg.isSwimming == true) && (nutmeg.jumpPeak == 1) 
            && (nutmeg.speedY > 50) && (KEY_TICKED(J_A))) {
            nutmeg.speedY = -nutmeg.speeds->initJumpY;
            nutmeg.jumpPeak = 0;
            nutmeg.movestate = inair;
            nutmeg.runJump = KEY_PRESSED(J_B) ? 1 : 0;
            
            //PlayFx(CHANNEL_1, 5, 0x71, 0x03, 0x44, 0xc8, 0x80);
            PlayFx(CHANNEL_1, 5, 0x17, 0x9f, 0xf3, 0xc9, 0xc4);

            //display a puff when jumping
            if (nutmeg.direction == right) {
                SpriteManagerAdd(SpritePuffLeft, THIS->x-2, THIS->y-2);
            }
            else {
                SpriteManagerAdd(SpritePuffRight, THIS->x+10, THIS->y-2);
            }
        }

        nutmeg.isGliding = false;
        if (KEY_PRESSED(J_B) && nutmeg.speedY > 0)
        {
            nutmeg.isGliding = true;
            // this will slow nutmeg down to 1 pixel drop per second
            if (nutmeg.speedY > nutmeg.speeds->fallGlideMaxY){
                nutmeg.speedY = nutmeg.speeds->fallGlideMaxY;
            }
        }

        if (nutmeg.runJump) {
            if (nutmeg.speedX < -nutmeg.speeds->runMaxX) nutmeg.speedX = -nutmeg.speeds->runMaxX;
            if (nutmeg.speedX > nutmeg.speeds->runMaxX) nutmeg.speedX = nutmeg.speeds->runMaxX;
        }
        else {
            if (nutmeg.speedX < -nutmeg.speeds->walkMaxX) nutmeg.speedX = -nutmeg.speeds->walkMaxX;
            if (nutmeg.speedX > nutmeg.speeds->walkMaxX) nutmeg.speedX = nutmeg.speeds->walkMaxX;
        }
    }

    /* * * * * * * * * * * * * * * * * * * */
    /*                move                 */
    /* * * * * * * * * * * * * * * * * * * */
    // Move player and check for collisions

        // apply speed to position
    nutmeg.offsetX += nutmeg.speedX;
    nutmeg.offsetY += nutmeg.speedY;

    INT8 delta = MoveX();
    // Do two movements to get colliders from both directions
    collisionX = TranslateSprite(THIS, delta, 0);
    delta = MoveY();
    collisionY = TranslateSprite(THIS, 0, delta);

    if (level.isWaterLevel)
    {
        nutmeg.speeds = &waterSpeed;
    }
    else
    {
        nutmeg.speeds = &groundSpeed;
        nutmeg.isOnIce = false;
        if ((collisionY >= level.iceTileMin) && (collisionY <= level.iceTileMax))
        {
            nutmeg.speeds = &iceGroundSpeed;
            nutmeg.isOnIce = true;
        }   
    } 
   
    /* * * * * * * * * * * * * * * * * * * */
    /*             X physics               */
    /* * * * * * * * * * * * * * * * * * * */
    // X physics
    // Stop movement if we hit something
    // Otherwise drag
    if (collisionX != 0) {
        nutmeg.speedX = 0;
        if ((level.isSpikeLevel == true) && (collisionX == 2))
        {
            // Get hit!
            nutmeg_hit();
            if (nutmeg.isDying == false)
            {
                // bounce upwards on hit
                nutmeg.speedY = - nutmeg.speeds->fallMaxY;
            }
        }
    }
    else if (!KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT)) 
    {
        if (nutmeg.speedX > 0) {
            if (nutmeg.speedX > nutmeg.speeds->frictionX)
            {
                 nutmeg.speedX -= nutmeg.speeds->frictionX;
            }
            else 
            {
                nutmeg.speedX = 0;
            }
        }
        else if (nutmeg.speedX < 0) {
            if (nutmeg.speedX < -nutmeg.speeds->frictionX) 
            {
                nutmeg.speedX += nutmeg.speeds->frictionX;
            }
            else 
            {
                nutmeg.speedX = 0;
            }
        }
    }

    /* * * * * * * * * * * * * * * * * * * */
    /*             Y physics               */
    /* * * * * * * * * * * * * * * * * * * */
    // Y physics
    // Drop down if we don't have ground under
    // Play audio on land
    // Start from step sound 6 on land to have start playing stepping audio when we walk quickly
    if (nutmeg.speedY > 0) {
        if (collisionY == 0) {
            nutmeg.movestate = inair;
        }
        else {
            if (nutmeg.movestate == inair) {
                //PlayFx(CHANNEL_4, 4, 0x32, 0x71, 0x73, 0x80);
                nutmeg.movestate = grounded;
            }

            nutmeg.speedY =  nutmeg.speeds->fallInitY;
        }
    }
    else {
        nutmeg.movestate = inair;
    }

    // check for up/down spike collisions
    if ((level.isSpikeLevel == true) && (collisionY == 2))
    {
        // Get hit!
        nutmeg_hit();
        if (nutmeg.isDying == false)
        {
            // bounce upwards on hit
            nutmeg.speedY = - nutmeg.speeds->fallMaxY;
        }
    }


    /* * * * * * * * * * * * * * * * * * * */
    /*      kickback from losing bow       */
    /* * * * * * * * * * * * * * * * * * * */
    if (nutmeg.health == full && nutmeg.lostbow == true) {
        if (kickbackcounter < 25) {
            SetSpriteAnim(THIS, anim_nutmeg_lostbow, 30);

            if (nutmeg.direction == left) {
                TranslateSprite (THIS, 1, 0);
            }
            else if (nutmeg.direction == right) {
                TranslateSprite (THIS, -1, 0);
            }

            kickbackcounter++;
        }
    }
}



void Update_SpriteNutmeg(void) {
    
    // extra life from 100 acorns
    if (nutmeg.acorns == 100) {
        nutmeg.lives++;
        // TODO - PLAY FUN SOUND HERE!
        nutmeg.acorns = 0;
        if (nutmeg.lives > 99) 
        {
            nutmeg.lives = 99;
        }
    }

    // death
    if (nutmeg.isDying == true) {
        update_whileDead();
    }

    /* * * * * * * * * * * * * * * * * * * */
    /*           normal mode               */
    /* * * * * * * * * * * * * * * * * * * */
    if ((cutscenemode == disabled) && (nutmeg.isDying == false))
    {
        update_aliveInControl ();
    }

    else if (cutscenemode == enabled) 
    {
        update_inCutscene();
    }
}

void Destroy_SpriteNutmeg(void) {
    spr_nutmeg = 0;
}

void nutmeg_SetupGame(void) BANKED
{
    //health system
       
    // TESTING - Should be 3 lives
    nutmeg.lives = 99; 
    nutmeg.acorns = 0;
  
    nutmeg.isOnIce = false;

    level_current = 0;
	level_next = 0;
	level_max = 0;
    
    // advance to the first level
    levelbeat = true;

    W1LevelSelection = 0;

    nutmeg_setupNewLife();
}

// setup variables for the next life
void nutmeg_setupNewLife (void) BANKED
{
    // start each life with a bow
    nutmeg.health = full;
    nutmeg.hasbow = true;
    nutmeg.lostbow = false;
}

// call this when nutmeg has been hit
void nutmeg_hit(void) BANKED
{
    if (nutmeg.hasbow == true)
    {
        nutmeg.hasbow = false;
        nutmeg.lostbow = true;
        nutmeg.bow_counter = 0;
        if (nutmeg.direction == right) { nutmeg.bowanim = 8; }
        else if (nutmeg.direction == left) { nutmeg.bowanim = 9; }

        // health gets set low after bow loss I guess (this provides some invincibility)
    }
    else if (nutmeg.health == low) {
        nutmeg.isDying = true;
        nutmeg.deathtimer = 0;
        
        if (nutmeg.lives <= 0) { GameOver = true; }
        else { nutmeg.lives--; }
    }
}

bool nutmeg_isInsideXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) BANKED
{
    if ((spr_nutmeg->x > x1)
      && (spr_nutmeg->x < x2)
      && (spr_nutmeg->y > y1)
      && (spr_nutmeg->y < y2))
    {
        return true;
    }
    return false;
}

// WARNING - Not called with THIS pointing to spr_nutmeg
void nutmeg_Animate(void) BANKED
{
    if (nutmeg.isDying == true) {
        return;
    }
    
     /* * * * * * * * * * * * * * * * * * * */
    /*             animation               */
    /* * * * * * * * * * * * * * * * * * * */
    // play correct animation based on current state & input
    // Idle if our movement is zero, or we are sliding and not pressing left or right
    if (nutmeg.movestate == grounded) {
        if (((nutmeg.isOnIce == true) && !KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT))
           || (nutmeg.isOnIce == false && nutmeg.speedX < 100 && nutmeg.speedX > -100)) 
        {
            if (nutmeg.direction == right) {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_idle_right, 5);
                nutmeg.bowanim = 0;
            }
            if (nutmeg.direction == left) {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_idle_left, 5);
                nutmeg.bowanim = 1;
            }
        }
        else {
            if (nutmeg.direction == right) {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_walk_right, 15);
                nutmeg.bowanim = 2;
            }
            if (nutmeg.direction == left) {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_walk_left, 15);
                nutmeg.bowanim = 3;
            }
        }
    }
    else if (nutmeg.movestate == inair) {
        if (nutmeg.isGliding)
        {
            if (nutmeg.direction == right)
            {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_glide, 1);
                nutmeg.bowanim = 11;
            }
            else
            {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_glide, 1);
                nutmeg.bowanim = 12;
            }
        }
        else if (nutmeg.speedY > 60) {
            if (nutmeg.direction == right) {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_fall_right, 1);
                nutmeg.bowanim = 6;
            }
            if (nutmeg.direction == left) {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_fall_left, 1);
                nutmeg.bowanim = 7;
            }
        }
        else if (nutmeg.speedY < -60) {
            if (nutmeg.direction == right) {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_jump_right, 1);
                nutmeg.bowanim = 4;
            }
            if (nutmeg.direction == left) {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_jump_left, 1);
                nutmeg.bowanim = 5;
            }
        }
    }

    // update the bow after we are done updating, so the x & y positions can track us correctly
    if (spr_nutmegbow != 0)
    {
        nutmegBow_update();
    }
}