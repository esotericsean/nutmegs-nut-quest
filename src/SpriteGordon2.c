#include "Banks/SetAutoBank.h"

#include <gb/gb.h>

#include "ZGBMain.h"
#include "SpriteManager.h"

#include "../src/GlobalVars.h"

static const UINT8 anim_gordon_idle_right2[] = {2, 0, 1};
static const UINT8 anim_gordon_idle_left2[]  = {2, 0, 1};

static const UINT8 anim_gordon_walk_right2[] = {4, 0, 0, 1, 2};
static const UINT8 anim_gordon_walk_left2[]  = {4, 0, 0, 1, 2};

static UINT8 gordoncounter2;
static direction gordon_direction2;

void Start_SpriteGordon2(void) 
{
    gordon_direction2 = left;
    gordoncounter2 = 0;
    
    SetSpriteAnim(THIS, anim_gordon_walk_left2, 4);

    THIS->lim_x = 500;
	THIS->lim_y = 144;
}

void Update_SpriteGordon2(void) 
{
    if (gordonwalkright == true) {
        if (gordon_direction2 == left) {
            TranslateSprite(THIS, -16, 0);
            //SPRITE_UNSET_VMIRROR(THIS);
            THIS->mirror = NO_MIRROR;
        }
        
        gordon_direction2 = right;

        //SPRITE_SET_VMIRROR(THIS);
        THIS->mirror = V_MIRROR;

        SetSpriteAnim(THIS, anim_gordon_walk_right2, 8);
        
        if (gordoncounter2 == 1 || gordoncounter2 == 3 || gordoncounter2 == 5) {
            TranslateSprite (THIS, 1, 0);
        }
    }
    else if (gordonwalkleft == true) {
        if (gordon_direction2 == right) {
            TranslateSprite(THIS, 16, 0);
        }
        
        gordon_direction2 = left;

        //SPRITE_UNSET_VMIRROR(THIS);
        THIS->mirror = NO_MIRROR;

        SetSpriteAnim(THIS, anim_gordon_walk_left2, 8);

        if (gordoncounter2 == 1 || gordoncounter2 == 3 || gordoncounter2 == 5) {
            TranslateSprite (THIS, -1, 0);
        }
    }
    else if (gordonwalkleft == false && gordonwalkright == false) {
        if (gordon_direction == left) {
            SetSpriteAnim(THIS, anim_gordon_idle_left2, 2);
        }
        else if (gordon_direction == right) {
            SetSpriteAnim(THIS, anim_gordon_idle_right2, 2);
        }
    }

    gordoncounter2++;

    if (gordoncounter2 >= 6) gordoncounter2 = 0;
}

void Destroy_SpriteGordon2(void) 
{
}