#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
#include "Scroll.h"
#include "Keys.h"
#include "ZGBMain.h"

#include "../src/GlobalVars.h"

static const UINT8 anim_nutmegtiny_idle[] = {4, 0, 0, 0, 1};

void Start_SpriteNutmegTiny (void) 
{
	THIS->lim_x = 9999;
	THIS->lim_y = 999;

	SetSpriteAnim(THIS, anim_nutmegtiny_idle, 6);
}

void Update_SpriteNutmegTiny(void) 
{
}

void Destroy_SpriteNutmegTiny (void) 
{
}