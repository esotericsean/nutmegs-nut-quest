#include "Banks/SetAutoBank.h"
#include "Sound.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "GlobalVars.h"

extern Sprite * spr_nutmeg;
extern Sprite * spr_nutmegbow;

static const UINT8 bow_idle[] = {1, 0};

void Start_SpriteBow(void) 
{
    THIS->lim_x = 9999;
    THIS->lim_y = 999;
    SetSpriteAnim(THIS, bow_idle, 8);
}

void Update_SpriteBow(void) 
{
    if (!spr_nutmeg) return;

    if (CheckCollision(THIS, spr_nutmeg)) {
        // Grant bow power
        nutmeg.hasbow = true;
        nutmeg.lostbow = false;
        nutmeg.bow_counter = 0;
        nutmeg.health = full;
        // Pause player briefly and flash
        nutmeg.pickupPauseFrames = 24;
        nutmeg.isInvincible = true;
        nutmeg.hurtFlashCounter = 24;

        // Spawn head bow sprite if not already present
        if (!spr_nutmegbow) {
            spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, spr_nutmeg->x, spr_nutmeg->y);
        }

        // SFX
        PlayFx(CHANNEL_1, 10, 0x00, 0x81, 0x83, 0xA3, 0x87);

        // Remove pickup sprite
        SpriteManagerRemoveSprite(THIS);
        return;
    }
}

void Destroy_SpriteBow(void) 
{
}