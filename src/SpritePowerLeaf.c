#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

static const UINT8 powerleaf_bounce[] = {8, 0, 0, 0, 1, 2, 2, 2, 1};

void Start_SpritePowerLeaf (void) 
{
	THIS->lim_x = 9999;
	THIS->lim_y = 999;

	SetSpriteAnim(THIS, powerleaf_bounce, 16);
}

void Update_SpritePowerLeaf (void) 
{
}

void Destroy_SpritePowerLeaf (void) 
{
}