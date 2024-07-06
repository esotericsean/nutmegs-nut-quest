#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
#include "Scroll.h"
#include "Keys.h"

const UINT8 anim_nuthead_idle[] = {33,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
									0, 0, 0, 0, 0, 0, 1};

void Start_SpriteNutHead(void) 
{
	THIS->lim_x = 9999;
	THIS->lim_y = 999;

	SetSpriteAnim(THIS, anim_nuthead_idle, 9);
}

void Update_SpriteNutHead(void) 
{
}

void Destroy_SpriteNutHead(void) 
{
}