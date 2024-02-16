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

// global variables for every level

// level timer countdown 
UINT16 timerlevel;

// frame counter for single timerlevel count
static UINT8 timerclock;

// saved last drawn values, to work out what to update on hud
static UINT8 lastLives = 0;
static UINT8 lastAcorn = 0;
static UINT16 lastTimer = 0;

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

    _isBoss = isBoss;
    timerlevel = 300;
    timerclock = 0;

    // prime the last values so they all get updated
    lastLives = nutmeglives + 1;
    lastAcorn = acorncounter + 1;
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
    
    if (lastTimer != timerlevel)
    {
        UINT16 working = timerlevel;

        //timer 100s digit:
        if (timerlevel == 300) 
        {
            UPDATE_HUD_TILE (10, 0, 9);
            working = 0;
        }
        else if (timerlevel < 300 && timerlevel >= 200)
        { 
            UPDATE_HUD_TILE (10, 0, 8);
            working = timerlevel - 200;
        }
        else if (timerlevel < 200 && timerlevel >= 100) 
        {
            UPDATE_HUD_TILE (10, 0, 7);
            working = timerlevel - 100;
        }
        else 
        {
            UPDATE_HUD_TILE (10, 0, 6);
            working = timerlevel;
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

    if (lastLives != nutmeglives)
    {
        // update HUD lives
        lastLives = nutmeglives;
        tens = getTens (nutmeglives);
        ones = nutmeglives - (tens * 10);
        UPDATE_HUD_TILE (3,0, 6 + tens);
        UPDATE_HUD_TILE (4,0, 6 + ones);
    }
    
    if (lastAcorn != acorncounter)
    {
        lastAcorn = acorncounter;
        tens = getTens(acorncounter);
        ones = acorncounter - (tens * 10);
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
        timerclock ++; 
     
        //25 seems good
        if (timerclock == 25) {
            timerclock = 0;
            timerlevel--;
	    }
    }

	if (lastTimer != timerlevel)
    {
        UINT16 working = timerlevel;

        //timer 100s digit:
        if (timerlevel == 300) 
        {
            UPDATE_HUD_TILE (10, 0, 9);
            working = 0;
        }
        else if (timerlevel < 300 && timerlevel >= 200)
        { 
            UPDATE_HUD_TILE (10, 0, 8);
            working = timerlevel - 200;
        }
        else if (timerlevel < 200 && timerlevel >= 100) 
        {
            UPDATE_HUD_TILE (10, 0, 7);
            working = timerlevel - 100;
        }
        else 
        {
            UPDATE_HUD_TILE (10, 0, 6);
            working = timerlevel;
        }

        tens = getTens(working);
        ones = working - (tens * 10);

        UPDATE_HUD_TILE (11, 0, 6 + tens);
        UPDATE_HUD_TILE (12, 0, 6 + ones);
    }
}

