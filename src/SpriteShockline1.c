#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"

static UINT8 shockline1counter;

static const UINT8 anim_shock1_flash[] = {2, 0, 1};
static const UINT8 anim_shock1_static[] = {1, 1};

void Start_SpriteShockline1(void) 
{
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_shock1_flash, 8);

	shockline1counter = 0;
}

void Update_SpriteShockline1(void) 
{
	if (shockline1counter < 100) 
	{
		shockline1counter++;
	}
	else 
	{
		SetSpriteAnim(THIS, anim_shock1_static, 1);
	}
}

void Destroy_SpriteShockline1(void) 
{
}