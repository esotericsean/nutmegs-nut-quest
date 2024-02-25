#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_spatula_spin[]  = {14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

static UINT8 spatula_counter;

void START (void) 
{
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_spatula_spin, 10);

	spatula_counter = 0;
}

void UPDATE (void) 
{
	THIS->x = THIS->x - 1;

	//die if touch spatula
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg_death == false) {
		nutmeg_hit();
	}
}

void DESTROY (void) 
{
	spatula_counter = 0;
}