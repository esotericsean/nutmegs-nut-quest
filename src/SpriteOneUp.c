#include "Banks/SetAutoBank.h"
#include "Sound.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "GlobalVars.h"

extern Sprite * spr_nutmeg;

// Reuse nuthead tileset; animate idles or static with bobbing
static const UINT8 oneup_idle[] = {1, 0};

static const INT8 bobY[] = {0,0,0,1,1,0,0,0,-1,-1};

#define MOVE_POS (0)
#define TIMER_POS (1)

#define MOVE_SPEED (10)

void Start_SpriteOneUp(void) {
    THIS->lim_x = 9999;
    THIS->lim_y = 999;
    SetSpriteAnim(THIS, oneup_idle, 16);
    THIS->custom_data[MOVE_POS] = 0;
    THIS->custom_data[TIMER_POS] = 0;
}

void Update_SpriteOneUp(void) {
    // bob
    THIS->custom_data[TIMER_POS]++;
    if (THIS->custom_data[TIMER_POS] >= MOVE_SPEED) {
        THIS->custom_data[TIMER_POS] = 0;
        THIS->y += bobY[THIS->custom_data[MOVE_POS]];
        THIS->custom_data[MOVE_POS]++;
        if (THIS->custom_data[MOVE_POS] >= sizeof(bobY)) {
            THIS->custom_data[MOVE_POS] = 0;
        }
    }

    if (spr_nutmeg && CheckCollision(THIS, spr_nutmeg)) {
        if (nutmeg.lives < 99) nutmeg.lives++;
        // feedback
        nutmeg.pickupPauseFrames = 16;
        nutmeg.isInvincible = true;
        nutmeg.hurtFlashCounter = 16;
        PlayFx(CHANNEL_1, 10, 0x00, 0x81, 0x83, 0xA3, 0x87);
        gameStats.totalPowerups++;
        SpriteManagerRemoveSprite(THIS);
        return;
    }
}

void Destroy_SpriteOneUp(void) {
}


