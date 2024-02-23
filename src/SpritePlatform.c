#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
#include "../src/GlobalVars.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_mushroom_moving[] = {1, 0};

#define PLAT_UPDOWN (0)
#define PLAY_LEFTRIGHT (1)

#define PLATFORM_TYPE_POS (0)
#define PLATFORM_STEPS (1)
#define PLATFORM_CURRENT_DIRECTION (2)
#define PLATFORM_COUNT (3)

void Start_SpritePlatform(void) 
{
    THIS->lim_x = 256 * 8;
	THIS->lim_y = 144;

    SetSpriteAnim(THIS, anim_mushroom_moving, 10);
    THIS->custom_data[PLATFORM_TYPE_POS] = PLAT_UPDOWN;
    THIS->custom_data[PLATFORM_STEPS] = 100;
    THIS->custom_data[PLATFORM_CURRENT_DIRECTION] = 0;
    THIS->custom_data[PLATFORM_COUNT] = 0;
}

void Update_SpritePlatform(void) 
{
    if (THIS->custom_data[PLATFORM_CURRENT_DIRECTION] == 0)
    {
        THIS->y --;
    }
    else 
    {
        THIS->y ++;
    }

    THIS->custom_data[PLATFORM_COUNT]++;
    if (THIS->custom_data[PLATFORM_COUNT] == THIS->custom_data[PLATFORM_STEPS])
    {
        THIS->custom_data[PLATFORM_COUNT] = 0;
        THIS->custom_data[PLATFORM_CURRENT_DIRECTION] = 1 - THIS->custom_data[PLATFORM_CURRENT_DIRECTION];
    }

    // If nutmeg is inside sprite (plus an extra pixel upwads), and nutmeg is falling, 
    // then stick nutmeg to the platform, and stop accel (and rechoose the sprite?)
    // was 14
    if ((spr_nutmeg->x + 8 > THIS->x)
        && (spr_nutmeg->x < THIS->x + 22)
        && (accelY >= 0)
        && (spr_nutmeg->y + 10 > THIS->y)
        && (spr_nutmeg->y < THIS->y)
        )
    {
        movestate = grounded;
        accelY = 0;
        spr_nutmeg->y = THIS->y - 8;
    }
}

void Destroy_SpritePlatform(void) 
{
}