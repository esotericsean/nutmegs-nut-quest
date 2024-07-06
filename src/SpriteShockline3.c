#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"

static UINT8 shockline3counter;

static const UINT8 anim_shock3_flash[] = {2, 0, 1};
static const UINT8 anim_shock3_static[] = {1, 1};

void Start_SpriteShockline3(void) 
{
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_shock3_flash, 8);

	shockline3counter = 0;
}

void Update_SpriteShockline3(void) 
{
	if (shockline3counter < 100) 
	{
		shockline3counter++;
	}
	else
	{
		SetSpriteAnim(THIS, anim_shock3_static, 1);
	}
}

void Destroy_SpriteShockline3(void) 
{
}