#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"

static UINT8 shockline2counter;

static const UINT8 anim_shock2_flash[] = {2, 0, 1};
static const UINT8 anim_shock2_static[] = {1, 1};

void Start_SpriteShockline2(void) 
{
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_shock2_flash, 8);

	shockline2counter = 0;
}

void Update_SpriteShockline2(void) 
{
	if (shockline2counter < 100)
	{ 
		shockline2counter++;
	}
	else
	{
		SetSpriteAnim(THIS, anim_shock2_static, 1);
	}
}

void Destroy_SpriteShockline2(void) 
{
}