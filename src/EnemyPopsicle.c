#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "GlobalVars.h"

Sprite * spr_popsicle;

const UINT8 anim_popsicle_spin[]  = {8, 0, 1, 2, 3, 4, 5, 6, 7};

UINT8 popsicle_counter;

void START() {
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_popsicle_spin, 10);

	popsicle_counter = 0;
}

void UPDATE() {
	//move every other frame
	/*
	if (popsicle_counter == 0 || popsicle_counter == 2) {
		//TranslateSprite (THIS, 1, 0); //checks for collisions
		THIS->x = THIS->x+1; //doesn't check for collisions
	}

	popsicle_counter++;
	if (popsicle_counter > 3) popsicle_counter = 0;
	*/

	//move every frame
	THIS->x = THIS->x+1;
}

void DESTROY() {
}