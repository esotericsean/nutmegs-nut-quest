#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Keys.h"
#include "Sound.h"
#include "SpriteManager.h"

#include "../src/GlobalVars.h"

const UINT8 anim_gordon_idle_right[] = {2, 0, 2};
const UINT8 anim_gordon_idle_left[]  = {2, 0, 2};

const UINT8 anim_gordon_walk_right[] = {4, 0, 1, 2, 3};
const UINT8 anim_gordon_walk_left[]  = {4, 0, 1, 2, 3};

//Gordon is grounded or inair
move_state Gmovestate;

//player movement physics
INT16 GaccelY;
INT16 GaccelX;

//storing collisions around player after movement
UINT8 GcollisionX;
UINT8 GcollisionY;
UINT8 GgroundCollision;

//cutscene mode!
switcher gordonmode;
bool gordonwalkleft;
bool gordonwalkright;
bool gordonrun;
bool gordonjump;

// Declare a pointer to a sprite
struct Sprite * spr_gordon2;

direction gordon_direction;
bool Gisjumping = true;

UINT8 gordoncounter;

void Start_SpriteGordon1() {
    SetSpriteAnim(THIS, anim_gordon_idle_left, 1);

    gordoncounter = 0;

    GaccelY = 0;
    GaccelX = 0;
    GcollisionX = 0;
    GcollisionY = 0;
    GgroundCollision = 0;
    //GjumpPeak = 0;
    //GrunJump = 0;

    Gmovestate = inair;

    gordonmode = disabled;
    gordonwalkleft = false;
    gordonwalkright = false;
    gordonrun = false;
    gordonjump = false;

    gordon_direction = left;
    Gisjumping = false;

    THIS->lim_x = 500;
	THIS->lim_y = 144;
}

void Update_SpriteGordon1() {
    if (gordonwalkright == true) {
        if (gordon_direction == left) {
            TranslateSprite(THIS, 16, 0);
        }
        
        gordon_direction = right;

        //SPRITE_SET_VMIRROR(THIS);
        THIS->mirror = V_MIRROR;

        SetSpriteAnim(THIS, anim_gordon_walk_right, 8);
        
        if (gordoncounter == 1 || gordoncounter == 3 || gordoncounter == 5) {
            TranslateSprite (THIS, 1, 0);
        }
    }
    else if (gordonwalkleft == true) {
        if (gordon_direction == right) {
            TranslateSprite(THIS, -16, 0);
        }
        
        gordon_direction = left;

        //SPRITE_UNSET_VMIRROR(THIS);
        THIS->mirror = NO_MIRROR;

        SetSpriteAnim(THIS, anim_gordon_walk_left, 8);

        if (gordoncounter == 1 || gordoncounter == 3 || gordoncounter == 5) {
            TranslateSprite (THIS, -1, 0);
        }
    }
    else if (gordonwalkleft == false && gordonwalkright == false) {
        if (gordon_direction == left) {
            SetSpriteAnim(THIS, anim_gordon_idle_left, 2);
        }
        else if (gordon_direction == right) {
            SetSpriteAnim(THIS, anim_gordon_idle_right, 2);
        }
    }

    gordoncounter++;

    if (gordoncounter >= 6) gordoncounter = 0;
}

void Destroy_SpriteGordon1() {
}