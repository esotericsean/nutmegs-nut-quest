#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Keys.h"
#include "Sound.h"
#include "SpriteManager.h"

#include "../src/GlobalVars.h"

static const UINT8 anim_gordon_idle_right[] = {2, 0, 2};
static const UINT8 anim_gordon_idle_left[]  = {2, 0, 2};

static const UINT8 anim_gordon_walk_right[] = {4, 0, 1, 2, 3};
static const UINT8 anim_gordon_walk_left[]  = {4, 0, 1, 2, 3};


//cutscene mode!

// global variables
bool gordonwalkleft;
bool gordonwalkright;
direction gordon_direction;

// Declare a pointer to a sprite
struct Sprite * spr_gordon2;


static UINT8 gordoncounter;

void Start_SpriteGordon1(void) {
    SetSpriteAnim(THIS, anim_gordon_idle_left, 1);

    gordoncounter = 0;

    gordonwalkleft = false;
    gordonwalkright = false;
    gordon_direction = left;

    THIS->lim_x = 500;
	THIS->lim_y = 144;
}

void Update_SpriteGordon1(void) {
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

void Destroy_SpriteGordon1(void) {
}