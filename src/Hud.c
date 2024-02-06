#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Scroll.h"

#include "GlobalVars.h"


// global variables for every level

// level timer countdown 
UINT16 timerlevel;

// frame counter for single timerlevel count
static UINT8 timerclock;

// saved last drawn values, to work out what to update on hud
static INT8 lastLives = 0;
static UINT8 lastAcorn = 0;
static UINT16 lastTimer = 0;


void Hud_Init(void) BANKED
{
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

void Hud_Update(void) BANKED
{
    UINT8 tens;
    UINT8 ones;

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