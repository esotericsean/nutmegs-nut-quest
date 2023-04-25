#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "GlobalVars.h"

Sprite * spr_spatula;

const UINT8 anim_spatula_spin[]  = {14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

UINT8 spatula_counter;

void START() {
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_spatula_spin, 10);

	spatula_counter = 0;
}

void UPDATE() {
	//move every other frame
	/*
	if (spatula_counter == 0 || spatula_counter == 2) {
		//TranslateSprite (THIS, -1, 0); //checks for collisions
		THIS->x = THIS->x-1; //doesn't check for collisions
	}

	spatula_counter++;
	if (spatula_counter > 3) spatula_counter = 0;
	*/

	//move every frame
	THIS->x = THIS->x-1;
}

void DESTROY() {
	spatula_counter = 0;
}