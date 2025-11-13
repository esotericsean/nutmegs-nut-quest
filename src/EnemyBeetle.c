#include "Banks/SetAutoBank.h"
#ifdef USE_CBT_FX
#include "Sound.h"
#undef PlayFx
#define PlayFx(...) do {} while(0)
#endif
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Sfx.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"
#include "StateLevel1b.h"

extern Sprite* spr_nutmeg;

#define BEETLE_STATE_WITH_SHELL 0u
#define BEETLE_STATE_BARE       1u

static const UINT8 anim_beetle_shell_walk[] = {4, 0, 1, 2, 3};
static const UINT8 anim_beetle_bare_walk[]  = {4, 4, 5, 4, 5};

static INT8 get_direction(Sprite* spr) {
    return (spr->custom_data[1] == 0u) ? -1 : 1;
}

static void reverse_direction(Sprite* spr) {
    spr->custom_data[1] = (spr->custom_data[1] == 0u) ? 1u : 0u;
    if (spr->custom_data[1] == 0u) {
        spr->mirror = V_MIRROR;
    } else {
        spr->mirror = NO_MIRROR;
    }
}

void Start_EnemyBeetle(void) {
    if (level.orientation == horizontal) {
        THIS->lim_x = 9999;
        THIS->lim_y = 144;
    } else if (level.orientation == vertical) {
        THIS->lim_x = 288;
        THIS->lim_y = 250;
    }

    SetSpriteAnim(THIS, anim_beetle_shell_walk, 12);
    THIS->custom_data[0] = BEETLE_STATE_WITH_SHELL;
    THIS->custom_data[1] = 0;      // 0 = moving left, 1 = right
    THIS->custom_data[2] = 0xFF;   // optional spawn index
    THIS->custom_data[3] = 0u;     // step timer for slower movement
    THIS->mirror = V_MIRROR;

    UINT8 drop_safety = 0u;
    while ((drop_safety < 32u) && !TranslateSprite(THIS, 0, 1)) {
        drop_safety++;
    }
}

void Update_EnemyBeetle(void) {
    INT8 dir = get_direction(THIS);
    UINT8 step_counter = THIS->custom_data[3]++;
    UINT8 do_move = ((step_counter & 1u) == 0u);
    UINT8 collided = 0u;

    if (do_move) {
        collided = TranslateSprite(THIS, dir, 0);
    }

    if (collided) {
        TranslateSprite(THIS, -dir, 0);
        reverse_direction(THIS);
        dir = get_direction(THIS);
    }

    UINT8 grounded = TranslateSprite(THIS, 0, 1);
    if (!grounded) {
        TranslateSprite(THIS, 0, -1);
        if (do_move) {
            TranslateSprite(THIS, -dir, 0);
        }
        reverse_direction(THIS);
        dir = get_direction(THIS);
    }

    if (THIS->custom_data[0] == BEETLE_STATE_WITH_SHELL) {
        SetSpriteAnim(THIS, anim_beetle_shell_walk, 12);
    } else {
        SetSpriteAnim(THIS, anim_beetle_bare_walk, 12);
    }

    if (CheckCollision(THIS, spr_nutmeg) && !nutmeg.isDying) {
        if ((nutmeg.movestate == inair) && (nutmeg.speedY > 0)) {
#ifdef USE_CBT_FX
            Sfx_Stomp();
#endif
            nutmeg.speedY = -nutmeg.enemyBounceY;
            nutmeg.jumpPeak = 0;

            if (THIS->custom_data[0] == BEETLE_STATE_WITH_SHELL) {
                THIS->custom_data[0] = BEETLE_STATE_BARE;
                SetSpriteAnim(THIS, anim_beetle_bare_walk, 12);
            } else {
                if (nutmeg.direction == right) {
                    AddStarPair(THIS->x, THIS->y + 1u);
                } else {
                    AddStarPair(THIS->x - 6, THIS->y + 1u);
                }
                if (THIS->custom_data[2] != 0xFF) {
                    Level1b_MarkSpawnCollected(THIS->custom_data[2]);
                }
                SpriteManagerRemoveSprite(THIS);
                gameStats.totalEnemyKills++;
            }
        } else {
            nutmeg_hit();
        }
    }
}

void Destroy_EnemyBeetle(void) {
    if (THIS->custom_data[2] != 0xFF) {
        Level1b_ReleaseSpawn(THIS->custom_data[2]);
    }
}

