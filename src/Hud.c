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
static UINT8 lastGolden;

// HUD tileset indices for the golden acorn indicator cell
#define HUD_GOLDEN_X          (13)
#define HUD_TILE_ACORN        (4)
#define HUD_TILE_BLANK_LINE   (1)

static UINT16 hudWorking;
static UINT8 tens;
static UINT8 ones;

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

static void updateTimeOnHud(void)
{
    hudWorking = level.timer;

    //timer 100s digit:
    if (level.timer == 300) 
    {
        UPDATE_HUD_TILE (10, 0, 9);
        hudWorking = 0;
    }
    else if (level.timer < 300 && level.timer >= 200)
    { 
        UPDATE_HUD_TILE (10, 0, 8);
        hudWorking = level.timer - 200;
    }
    else if (level.timer < 200 && level.timer >= 100) 
    {
        UPDATE_HUD_TILE (10, 0, 7);
        hudWorking = level.timer - 100;
    }
    else 
    {
        UPDATE_HUD_TILE (10, 0, 6);
        hudWorking = level.timer;
    }

    tens = getTens(hudWorking);
    ones = hudWorking - (tens * 10);

    UPDATE_HUD_TILE (11, 0, 6 + tens);
    UPDATE_HUD_TILE (12, 0, 6 + ones);
}

void Hud_Init(void) BANKED
{
    if (level.isOverworld)
    {
        INIT_HUD(hudboss);
        // Show tiny nut head and X/lives for overworld only
        UPDATE_HUD_TILE (2, 0, 3); // 'X' tile index in HUD tileset
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
    rWY = (INT8) (144 - 8);
    scroll_h_border = 8;
 
    // prime the last values so they all get updated
    lastLives = nutmeg.lives + 1;
    lastAcorn = nutmeg.acorns + 1;
    lastGolden = 0xFF;

    if (level.hasTimer)
    {
        updateTimeOnHud();
    }
}


#ifdef IS_DEBUG

extern Sprite *spr_nutmeg;

static void PutU16 (UINT16 v, UINT8 at)
{
    UINT8 thous;
    UINT8 hundreds;

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
    // show X and Y
    PutU16 (spr_nutmeg->x, 2);
    PutU16 (spr_nutmeg->y, 16 );
    // show death FSM state and timers
    UPDATE_HUD_TILE (2, 1, 6 + 0); // 'D'
    UPDATE_HUD_TILE (3, 1, 6 + nutmeg.deathState);
    PutU16 (nutmeg.deathtimer, 6);
    PutU16 (nutmeg.deathFrames, 12);
}
#endif 


void Hud_Update(void) BANKED
{
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

    // Overworld: show bow on tiny nutmeg head if possessed
    if (level.isOverworld) // overworld HUD variant
    {
        // The HUD tileset packs the tiny head at a fixed tile; set an attribute tile next to it
        // If your tiles for head-with-bow differ, replace indices below
        UINT8 headTile = 4;      // base tiny head tile index
        UINT8 headBowTile = 5;   // head-with-bow tile index
        UPDATE_HUD_TILE (2,0, nutmeg.hasbow ? headBowTile : headTile);
    }
    
    if (lastAcorn != nutmeg.acorns)
    {
        lastAcorn = nutmeg.acorns;
        tens = getTens(nutmeg.acorns);
        ones = nutmeg.acorns - (tens * 10);
        UPDATE_HUD_TILE (17, 0, 6 + tens);
        UPDATE_HUD_TILE (18, 0, 6 + ones);
    }
    
    if (level.isOverworld)
    {
        // all done if we aren't tracking time
        return;
    }

    // show a small acorn when this level's golden acorn has been collected
    // (either just now, or on a previous run)
    {
        UINT8 golden = (levelGoldenAcornFound
            || ((level_playing < MAX_LEVEL_TRACKING) && levelGoldenCollected[level_playing])) ? 1 : 0;
        if (golden != lastGolden)
        {
            lastGolden = golden;
            UPDATE_HUD_TILE (HUD_GOLDEN_X, 0, golden ? HUD_TILE_ACORN : HUD_TILE_BLANK_LINE);
        }
    }

	if (cutscenemode == disabled) 
    { 
        level.timerclock ++; 
     
        // 25 seems good
        if (level.timerclock == 25) {
            level.timerclock = 0;

            if (level.timer > 0)
            {
                level.timer--;
                updateTimeOnHud();
            }
	    }
    }
}

