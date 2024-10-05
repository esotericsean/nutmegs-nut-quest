#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "../src/GlobalVars.h"

void Start_SpriteLevelStart(void) 
{
    THIS->custom_data[0] = 0;
}

void Update_SpriteLevelStart(void) 
{
    THIS->custom_data[0] ++;
    if (THIS->custom_data[0] == 101)
    {
        SpriteManagerRemoveSprite(THIS);
    }
}

void Destroy_SpriteLevelStart(void) 
{
}