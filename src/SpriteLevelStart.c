#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "../src/GlobalVars.h"

// move the level start sprite offscreeen to make it "blink"
// save the old y pos so we can move it back
static UINT16 oldY;

void Start_SpriteLevelStart(void) 
{
    THIS->custom_data[0] = 0;
}

void Update_SpriteLevelStart(void) 
{
    
    if (THIS->custom_data[0] == 0)
    {
        oldY = THIS->y;
        THIS-> y = (UINT16) -20;
    }
    else if (THIS->custom_data[0] == 10)
    {
        THIS->y = oldY;
    }
    else if (THIS->custom_data[0] == 40)
    {
        THIS-> y = (UINT16) -20;
    }
    else if (THIS->custom_data[0] == 70)
    {
        THIS->y = oldY;
    }
    else if (THIS->custom_data[0] == 100)
    {
        SpriteManagerRemoveSprite(THIS);
    }

    THIS->custom_data[0] ++;
}

void Destroy_SpriteLevelStart(void) 
{
}