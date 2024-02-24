#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
#include "../src/GlobalVars.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_mushroom_moving[] = {1, 0};

#define PLAT_UPDOWN (0)
#define PLAY_LEFTRIGHT (1)

#define PLATFORM_X (0)
#define PLATFORM_Y (1)
#define PLATFORM_STEPS (2)
#define PLATFORM_COUNT (3)

void Start_SpritePlatform(void) 
{
    THIS->lim_x = 256 * 8;
	THIS->lim_y = 144;

    SetSpriteAnim(THIS, anim_mushroom_moving, 10);
    THIS->custom_data[PLATFORM_X] = 1;
    THIS->custom_data[PLATFORM_Y] = -1;
    THIS->custom_data[PLATFORM_STEPS] = 100;
    THIS->custom_data[PLATFORM_COUNT] = 0;
}

void Update_SpritePlatform(void) 
{
    THIS->x += (INT8) (THIS->custom_data[PLATFORM_X]);
    THIS->y += (INT8) (THIS->custom_data[PLATFORM_Y]);


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

        // nutmeg gets moved with the platform
        spr_nutmeg->x += (INT8) (THIS->custom_data[PLATFORM_X]);
        // y movement is already taken care of above
        //spr_nutmeg->y += (INT8) (THIS->custom_data[PLATFORM_Y]);
    }


    // check if we flip direction
    THIS->custom_data[PLATFORM_COUNT]++;
    if (THIS->custom_data[PLATFORM_COUNT] == THIS->custom_data[PLATFORM_STEPS])
    {
        THIS->custom_data[PLATFORM_COUNT] = 0;
        THIS->custom_data[PLATFORM_X] = 0 - THIS->custom_data[PLATFORM_X];
        THIS->custom_data[PLATFORM_Y] = 0 - THIS->custom_data[PLATFORM_Y];
    }
}

void Destroy_SpritePlatform(void) 
{
}