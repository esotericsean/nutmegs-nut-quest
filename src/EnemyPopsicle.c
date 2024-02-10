#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_popsicle_spin[]  = {8, 0, 1, 2, 3, 4, 5, 6, 7};

UINT8 popsicle_counter;

void START() {
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_popsicle_spin, 10);

	popsicle_counter = 0;
}

void UPDATE() {
	THIS->x = THIS->x+1;

	//die if touch popsicle
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg_death == false) {
		nutmeg_hit();
	}
}

void DESTROY() {
	popsicle_counter = 0;
}