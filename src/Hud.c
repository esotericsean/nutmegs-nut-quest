#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "GlobalVars.h"

IMPORT_MAP (hud);
IMPORT_MAP (hudboss);
IMPORT_MAP (hudDebug);

// Uncomment this next line for the debug HUD that shows nutmegs x and y position
// #define IS_DEBUG (true)

// in scroll.h - used to adjust the window when we pause
extern INT8 scroll_h_border;


// global variables for every level

// saved last drawn values, to work out what to update on hud
static UINT8 lastLives;
static UINT8 lastAcorn;
static UINT16 lastTimer;

static bool _isBoss = false;

void Hud_Init(bool isBoss) BANKED
{
    if (isBoss == true)
    {
        INIT_HUD(hudboss);
    }
    else
    {
#ifdef IS_DEBUG
        INIT_HUD(hudDebug);
#else
        INIT_HUD(hud);
#endif
    }

    // hide the paused text
    rWY = 144 - 8;
    scroll_h_border = 8;

    _isBoss = isBoss;
    level.timer = 300;
    level.timerclock = 0;

    // prime the last values so they all get updated
    lastLives = nutmeg.lives + 1;
    lastAcorn = nutmeg.acorns + 1;
    lastTimer = 0;
}

static UINT8 getTens (UINT8 full)
{
    UINT8 t = 0 ;
    while (full > 9)
    {
        full -= 10;
        t ++;
    }
    return t;
}


#ifdef IS_DEBUG

extern Sprite *spr_nutmeg;

static void PutU16 (UINT16 v, UINT8 at)
{
    UINT8 thous;
    UINT8 hundreds;
    UINT8 tens;
    UINT8 ones;

    thous = v / 1000;
    v -= thous*1000;
    hundreds = v/ 100;
    v -= hundreds * 100;
    tens = getTens((UINT8) v);
    ones = v - tens*10;

     UPDATE_HUD_TILE (at++, 0, 6 + thous);
     UPDATE_HUD_TILE (at++, 0, 6 + hundreds);
     UPDATE_HUD_TILE (at++, 0, 6 + tens);
     UPDATE_HUD_TILE (at++, 0, 6 + ones);
}

void Hud_UpdateDebug(void)
{
    PutU16 (spr_nutmeg->x, 2);
    PutU16 (spr_nutmeg->y, 16 );
    
    if (lastTimer != level.timer)
    {
        UINT16 working = level.timer;

        //timer 100s digit:
        if (level.timer == 300) 
        {
            UPDATE_HUD_TILE (10, 0, 9);
            working = 0;
        }
        else if (level.timer < 300 && level.timer >= 200)
        { 
            UPDATE_HUD_TILE (10, 0, 8);
            working = level.timer - 200;
        }
        else if (level.timer < 200 && level.timer >= 100) 
        {
            UPDATE_HUD_TILE (10, 0, 7);
            working = level.timer - 100;
        }
        else 
        {
            UPDATE_HUD_TILE (10, 0, 6);
            working = level.timer;
        }

        UINT8 tens = getTens(working);
        UINT8 ones = working - (tens * 10);

        UPDATE_HUD_TILE (11, 0, 6 + tens);
        UPDATE_HUD_TILE (12, 0, 6 + ones);
    }
}
#endif 


void Hud_Update(void) BANKED
{
    UINT8 tens;
    UINT8 ones;

#ifdef IS_DEBUG
    Hud_UpdateDebug();
    return;
#endif

    if (lastLives != nutmeg.lives)
    {
        // update HUD lives
        lastLives = nutmeg.lives;
        tens = getTens (nutmeg.lives);
        ones = nutmeg.lives - (tens * 10);
        UPDATE_HUD_TILE (3,0, 6 + tens);
        UPDATE_HUD_TILE (4,0, 6 + ones);
    }
    
    if (lastAcorn != nutmeg.acorns)
    {
        lastAcorn = nutmeg.acorns;
        tens = getTens(nutmeg.acorns);
        ones = nutmeg.acorns - (tens * 10);
        UPDATE_HUD_TILE (17, 0, 6 + tens);
        UPDATE_HUD_TILE (18, 0, 6 + ones);
    }
    
    if (_isBoss == true)
    {
        // boss levels we don't track time
        return;
    }

	if (cutscenemode == disabled) 
    { 
        level.timerclock ++; 
     
        //25 seems good
        if (level.timerclock == 25) {
            level.timerclock = 0;
            level.timer--;
	    }
    }

	if (lastTimer != level.timer)
    {
        UINT16 working = level.timer;

        //timer 100s digit:
        if (level.timer == 300) 
        {
            UPDATE_HUD_TILE (10, 0, 9);
            working = 0;
        }
        else if (level.timer < 300 && level.timer >= 200)
        { 
            UPDATE_HUD_TILE (10, 0, 8);
            working = level.timer - 200;
        }
        else if (level.timer < 200 && level.timer >= 100) 
        {
            UPDATE_HUD_TILE (10, 0, 7);
            working = level.timer - 100;
        }
        else 
        {
            UPDATE_HUD_TILE (10, 0, 6);
            working = level.timer;
        }

        tens = getTens(working);
        ones = working - (tens * 10);

        UPDATE_HUD_TILE (11, 0, 6 + tens);
        UPDATE_HUD_TILE (12, 0, 6 + ones);
    }
}

