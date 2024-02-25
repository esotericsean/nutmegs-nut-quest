#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_popsicle_spin[]  = {8, 0, 1, 2, 3, 4, 5, 6, 7};

void START (void)
{
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_popsicle_spin, 10);
}

void UPDATE (void) 
{
	THIS->x = THIS->x+1;

	//die if touch popsicle
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg_death == false) {
		nutmeg_hit();
	}
}

void DESTROY (void) 
{
}