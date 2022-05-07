#include "Banks/SetBank2.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Sound.h"
#include "SpriteManager.h"

#include "../src/GlobalVars.h"

const UINT8 anim_nutmeg_idle_right2[] = {4, 1, 2, 3, 4};
const UINT8 anim_nutmeg_idle_left2[]  = {4, 1, 2, 3, 4};

const UINT8 anim_nutmeg_walk_right2[] = {4, 5, 6, 7, 8};
const UINT8 anim_nutmeg_walk_left2[]  = {4, 5, 6, 7, 8};

const UINT8 anim_nutmeg_jump_right2[] = {1, 9};
const UINT8 anim_nutmeg_jump_left2[]  = {1, 9};

const UINT8 anim_nutmeg_fall_right2[] = {1, 10};
const UINT8 anim_nutmeg_fall_left2[]  = {1, 10};

const UINT8 anim_nutmeg_land_right2[] = {1, 11};
const UINT8 anim_nutmeg_land_left2[]  = {1, 11};
   
const UINT8 anim_nutmeg_hurt_right2[] = {1, 12}; //flashes blank frame
const UINT8 anim_nutmeg_hurt_left2[]  = {1, 12};

// Declare a pointer to a sprite
struct Sprite * spr_nutmeg1;

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
}

void Start_SpriteNutmeg2() {
    THIS->coll_x = -3;
	THIS->coll_y = 8;
	THIS->coll_w = 6;
	THIS->coll_h = 8;

    ResetState();

    THIS->lim_x = 500;
	THIS->lim_y = 144;
}

void Update_SpriteNutmeg2() {
    if (cutscenemode == disabled) {
        if (KEY_PRESSED(J_RIGHT)) {
            if (nutmeg_direction == left) {
                THIS->coll_x = -3;
                THIS->coll_y = 8;
                THIS->coll_w = 6;
                THIS->coll_h = 8;
            }

            SPRITE_UNSET_VMIRROR(THIS);
        }

        if (KEY_PRESSED(J_LEFT)) {
            if (nutmeg_direction == right) {
                THIS->coll_x = 11;
                THIS->coll_y = 8;
                THIS->coll_w = 6;
                THIS->coll_h = 8;
            }

            SPRITE_SET_VMIRROR(THIS);
        }

        if (keys == 0 && nutmeg_direction == right) {
            SPRITE_UNSET_VMIRROR(THIS);
        }
        if (keys == 0 && nutmeg_direction == left) {
            SPRITE_SET_VMIRROR(THIS);
        }

        collisionX = TranslateSprite(THIS, accelX / 100, 0);
        collisionY = TranslateSprite(THIS, 0, accelY / 100);

        if (movestate == grounded) {
            if (accelX < 100 && accelX > -100) {
                if (nutmeg_direction == right)
                    SetSpriteAnim(THIS, anim_nutmeg_idle_right2, 5);
                if (nutmeg_direction == left)
                    SetSpriteAnim(THIS, anim_nutmeg_idle_left2, 5);
            }
            else if (KEY_PRESSED(J_B)) {
                if (nutmeg_direction == right)
                    SetSpriteAnim(THIS, anim_nutmeg_walk_right2, 15);
                if (nutmeg_direction == left)
                    SetSpriteAnim(THIS, anim_nutmeg_walk_left2, 15);
            }
            else {
                if (nutmeg_direction == right)
                    SetSpriteAnim(THIS, anim_nutmeg_walk_right2, 15);
                if (nutmeg_direction == left)
                    SetSpriteAnim(THIS, anim_nutmeg_walk_left2, 15);
            }
        }
        else {
            if (accelY > 60) {
                if (nutmeg_direction == right)
                    SetSpriteAnim(THIS, anim_nutmeg_fall_right2, 1);
                if (nutmeg_direction == left)
                    SetSpriteAnim(THIS, anim_nutmeg_fall_left2, 1);
            }
            else if (accelY < -60) {
                if (nutmeg_direction == right)
                    SetSpriteAnim(THIS, anim_nutmeg_jump_right2, 1);
                if (nutmeg_direction == left)
                    SetSpriteAnim(THIS, anim_nutmeg_jump_left2, 1);
            }
        }

        if (nutmeg_direction == right) {
            THIS->x = spr_nutmeg1->x + 16;
            THIS->y = spr_nutmeg1->y;
        }
        else if (nutmeg_direction == left) {
            THIS->x = spr_nutmeg1->x - 16;
            THIS->y = spr_nutmeg1->y;
        }
    }
    else if (cutscenemode == enabled) {
        if (cutscenewalkright == true) {
            if (nutmeg_direction == left) {
                THIS->coll_x = -3;
                THIS->coll_y = 8;
                THIS->coll_w = 6;
                THIS->coll_h = 8;
            }

            SPRITE_UNSET_VMIRROR(THIS);
        }

        if (cutscenewalkleft == true) {
            if (nutmeg_direction == right) {
                THIS->coll_x = 11;
                THIS->coll_y = 8;
                THIS->coll_w = 6;
                THIS->coll_h = 8;
            }

            SPRITE_SET_VMIRROR(THIS);
        }

        if (keys == 0 && nutmeg_direction == right) {
            SPRITE_UNSET_VMIRROR(THIS);
        }
        if (keys == 0 && nutmeg_direction == left) {
            SPRITE_SET_VMIRROR(THIS);
        }

        collisionX = TranslateSprite(THIS, accelX / 100, 0);
        collisionY = TranslateSprite(THIS, 0, accelY / 100);

        if (movestate == grounded) {
            if (accelX < 100 && accelX > -100) {
                if (nutmeg_direction == right)
                    SetSpriteAnim(THIS, anim_nutmeg_idle_right2, 5);
                if (nutmeg_direction == left)
                    SetSpriteAnim(THIS, anim_nutmeg_idle_left2, 5);
            }
            else if (KEY_PRESSED(J_B)) {
                if (nutmeg_direction == right)
                    SetSpriteAnim(THIS, anim_nutmeg_walk_right2, 15);
                if (nutmeg_direction == left)
                    SetSpriteAnim(THIS, anim_nutmeg_walk_left2, 15);
            }
            else {
                if (nutmeg_direction == right)
                    SetSpriteAnim(THIS, anim_nutmeg_walk_right2, 15);
                if (nutmeg_direction == left)
                    SetSpriteAnim(THIS, anim_nutmeg_walk_left2, 15);
            }
        }
        else {
            if (accelY > 60) {
                if (nutmeg_direction == right)
                    SetSpriteAnim(THIS, anim_nutmeg_fall_right2, 1);
                if (nutmeg_direction == left)
                    SetSpriteAnim(THIS, anim_nutmeg_fall_left2, 1);
            }
            else if (accelY < -60) {
                if (nutmeg_direction == right)
                    SetSpriteAnim(THIS, anim_nutmeg_jump_right2, 1);
                if (nutmeg_direction == left)
                    SetSpriteAnim(THIS, anim_nutmeg_jump_left2, 1);
            }
        }

        if (nutmeg_direction == right) {
            THIS->x = spr_nutmeg1->x + 16;
            THIS->y = spr_nutmeg1->y;
        }
        else if (nutmeg_direction == left) {
            THIS->x = spr_nutmeg1->x - 16;
            THIS->y = spr_nutmeg1->y;
        }

        if (nutmeg_death == true) {
            if (nutmeg_direction == left) SetSpriteAnim(THIS, anim_nutmeg_hurt_left2, 1);
            else if (nutmeg_direction == right) SetSpriteAnim(THIS, anim_nutmeg_hurt_right2, 1);
        }
    }
}

void Destroy_SpriteNutmeg2() {
}