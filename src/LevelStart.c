#include "Banks/SetAutoBank.h"
#include <gb/cgb.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "../src/GlobalVars.h"


void LevelStart_Init (UINT8 xstart, UINT8 ystart) BANKED
{
	SpriteManagerAdd(SpriteLevelStart, xstart*8, ystart*8);
}
