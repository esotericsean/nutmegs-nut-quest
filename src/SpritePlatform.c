#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
#include "../src/GlobalVars.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_mushroom_moving[] = {1, 0};

#define PLAT_STATE_MOVE (0)
// Allow the platform to wait for 2 seconds at either end of its journey
#define PLAT_STATE_WAIT (1)

#
#define PLATFORM_X (0)
#define PLATFORM_Y (1)
#define PLATFORM_STEPS (2)
#define PLATFORM_COUNT (3)
#define PLATFORM_STATE (4)

void Start_SpritePlatform(void) 
{
    THIS->lim_x = 256*8;
	THIS->lim_y = 144;

    SetSpriteAnim(THIS, anim_mushroom_moving, 10);
    THIS->custom_data[PLATFORM_X] = 1;
    THIS->custom_data[PLATFORM_Y] = (UINT8) (-1);
    THIS->custom_data[PLATFORM_STEPS] = 100;
    THIS->custom_data[PLATFORM_COUNT] = 0;
    THIS->custom_data[PLATFORM_STATE] = PLAT_STATE_MOVE;
}

void Update_SpritePlatform(void) 
{
    if (THIS->custom_data[PLATFORM_STATE] == PLAT_STATE_MOVE)
    {
        THIS->x += (INT8) (THIS->custom_data[PLATFORM_X]);
        THIS->y += (INT8) (THIS->custom_data[PLATFORM_Y]);
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

        // nutmeg gets moved with the platform
        if (THIS->custom_data[PLATFORM_STATE] == PLAT_STATE_MOVE)
        {
            spr_nutmeg->x += (INT8) (THIS->custom_data[PLATFORM_X]);
            
            // y movement is already taken care of above
            //spr_nutmeg->y += (INT8) (THIS->custom_data[PLATFORM_Y]);
        }
    }

   
    THIS->custom_data[PLATFORM_COUNT]++;
    if (THIS->custom_data[PLATFORM_STEPS] == 255)
    {
        if ((INT8) (THIS->custom_data[PLATFORM_Y]) < 0)
        {
            if (THIS->y > 60000)
            {
                THIS->y = 17 * 8;
            }
        }
        else 
        {
            if ((THIS->y > 17 * 8) && (THIS->y < 1000))
            {
                THIS->y = 65530;
            }
        }
    }
    else if (THIS->custom_data[PLATFORM_STATE] == PLAT_STATE_MOVE)
    {
         // check if we flip direction
        if (THIS->custom_data[PLATFORM_COUNT] == THIS->custom_data[PLATFORM_STEPS])
        {
            THIS->custom_data[PLATFORM_COUNT] = 0;
            THIS->custom_data[PLATFORM_X] = 0 - THIS->custom_data[PLATFORM_X];
            THIS->custom_data[PLATFORM_Y] = 0 - THIS->custom_data[PLATFORM_Y];
            THIS->custom_data[PLATFORM_STATE] = PLAT_STATE_WAIT;
        }   
    }
    else
    {
        if (THIS->custom_data[PLATFORM_COUNT] == 90)
        {
            THIS->custom_data[PLATFORM_STATE] = PLAT_STATE_MOVE;
            THIS->custom_data[PLATFORM_COUNT] = 0;
        }
    }
}

void Destroy_SpritePlatform(void) 
{
}

void Platform_Setup (Sprite *s, INT8 x, INT8 y, UINT8 steps) BANKED
{
    s->custom_data[PLATFORM_X] = x;
    s->custom_data[PLATFORM_Y] = y;
    s->custom_data[PLATFORM_STEPS] = steps;
}