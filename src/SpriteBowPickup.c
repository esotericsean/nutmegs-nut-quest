#include "Banks/SetAutoBank.h"
#include "Sound.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "GlobalVars.h"

extern Sprite * spr_nutmeg;
extern Sprite * spr_nutmegbow;

// Simple idle frame from nutmegbow tileset (matches small yellow bow)
static const UINT8 bow_pickup_static[] = {1, 1};

// Up/down bob like the acorn collectible
static const INT8 bowMoveYAtTime [] = {0,0,0,1,1,0,0,0,-1,-1};

#define IS_STILL_POS (0)
#define MOVE_POS (1)
#define TIMER_POS (2)

#define MOVE_SPEED (10)

void Start_SpriteBowPickup(void) {
    // Large limits so it isn't culled too early
    THIS->lim_x = 9999;
    THIS->lim_y = 999;

    // Bobbing state init
    THIS->custom_data[IS_STILL_POS] = false;
    THIS->custom_data[MOVE_POS] = 0;
    THIS->custom_data[TIMER_POS] = 0;

    // Display small yellow bow static frame
    SetSpriteAnim(THIS, bow_pickup_static, 16);
}

void Update_SpriteBowPickup(void) {
    // Bob up/down
    if (THIS->custom_data[IS_STILL_POS] == false) {
        THIS->custom_data[TIMER_POS] ++;
        if (THIS->custom_data[TIMER_POS] >= MOVE_SPEED) {
            THIS->custom_data[TIMER_POS] = 0;
            THIS->y += bowMoveYAtTime[THIS->custom_data[MOVE_POS]];
            THIS->custom_data[MOVE_POS]++;
            if (THIS->custom_data[MOVE_POS] >= sizeof(bowMoveYAtTime)) {
                THIS->custom_data[MOVE_POS] = 0;
            }
        }
    }

    // Pickup
    if (spr_nutmeg && CheckCollision(THIS, spr_nutmeg)) {
        // Grant bow power
        nutmeg.hasbow = true;
        nutmeg.lostbow = false;
        nutmeg.bow_counter = 0;
        nutmeg.health = full;

        // Pickup pause and flash
        nutmeg.pickupPauseFrames = 24;
        nutmeg.isInvincible = true;
        nutmeg.hurtFlashCounter = 24;

        // If a hidden preloaded bow exists, enable it; else spawn one now
        if (spr_nutmegbow) {
            spr_nutmegbow->custom_data[0] = 0; // enable following/visibility
            spr_nutmegbow->x = spr_nutmeg->x;
            spr_nutmegbow->y = spr_nutmeg->y;
        } else {
            spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, spr_nutmeg->x, spr_nutmeg->y);
        }

        // SFX
        PlayFx(CHANNEL_1, 10, 0x00, 0x81, 0x83, 0xA3, 0x87);
        gameStats.totalPowerups++;

        // Remove pickup
        SpriteManagerRemoveSprite(THIS);
        return;
    }
}

void Destroy_SpriteBowPickup(void) {
}


