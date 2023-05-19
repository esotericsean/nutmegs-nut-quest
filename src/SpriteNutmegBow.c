#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "../src/GlobalVars.h"

extern Sprite * nutmeg_sprite;

const UINT8 anim_nutmegbow_static[] = {1, 1};

const UINT8 anim_nutmegbow_idle_right[] = {4, 1, 2, 3, 4};
const UINT8 anim_nutmegbow_idle_left[]  = {4, 1, 2, 3, 4};

const UINT8 anim_nutmegbow_walk_right[] = {4, 5, 6, 7, 8};
const UINT8 anim_nutmegbow_walk_left[]  = {4, 5, 6, 7, 8};

const UINT8 anim_nutmegbow_jump_right[] = {1, 9};
const UINT8 anim_nutmegbow_jump_left[]  = {1, 9};

const UINT8 anim_nutmegbow_fall_right[] = {1, 10};
const UINT8 anim_nutmegbow_fall_left[]  = {1, 10};

// 0 = idle (5)
// 1 = walking (15)
// 2 = jump/fall (1)
// 3 = static (1)

UINT8 bowanim;

//UINT8 bow_x;
UINT8 bow_y;

UINT8 bow_counter;

//UINT8 bow_catch_x;

bool lostbow;

/* * * * * * * * * * * * */
/*        bowanim        */
/* * * * * * * * * * * * */

// 0 = idle_right (NO_MIRROR)
// 1 = idle_left (V_MIRROR)
// 2 = walk_right (NO_MIRROR)
// 3 = walk_left (V_MIRROR)
// 4 = jump_right (NO_MIRROR)
// 5 = jump_left (V_MIRROR)
// 6 = fall_right (NO_MIRROR)
// 7 = fall_left (V_MIRROR)

// 8 = drop_right (NO_MIRROR) // lost health
// 9 = drop_left (V_MIRROR)   // use anim_nutmegbow_static

// 10 = disabled

void Start_SpriteNutmegBow() {
	THIS->lim_x = 500;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_nutmegbow_idle_right, 5);
	bowanim = 0;

	//bow_x = 0;
	bow_y = 0;

	bow_counter = 0;
	//bow_catch_x = 0;
}

void Update_SpriteNutmegBow() {
	if (lostbow == false) {
		//lostbow = false;

		THIS->y = nutmeg_sprite->y-24;

		switch (bowanim) {
			case 0:
				THIS->x = nutmeg_sprite->x-8;
				SetSpriteAnim(THIS, anim_nutmegbow_idle_right, 5);
				THIS->mirror = NO_MIRROR;
				break;
			case 1:
				THIS->x = nutmeg_sprite->x+8;
				SetSpriteAnim(THIS, anim_nutmegbow_idle_left, 5);
				THIS->mirror = V_MIRROR;
				break;
			case 2:
				THIS->x = nutmeg_sprite->x-8;
				SetSpriteAnim(THIS, anim_nutmegbow_walk_right, 15);
				THIS->mirror = NO_MIRROR;
				break;
			case 3:
				THIS->x = nutmeg_sprite->x+8;
				SetSpriteAnim(THIS, anim_nutmegbow_walk_left, 15);
				THIS->mirror = V_MIRROR;
				break;
			case 4:
				THIS->x = nutmeg_sprite->x-8;
				SetSpriteAnim(THIS, anim_nutmegbow_jump_right, 1);
				THIS->mirror = NO_MIRROR;
				break;
			case 5:
				THIS->x = nutmeg_sprite->x+8;
				SetSpriteAnim(THIS, anim_nutmegbow_jump_left, 1);
				THIS->mirror = V_MIRROR;
				break;
			case 6:
				THIS->x = nutmeg_sprite->x-8;
				SetSpriteAnim(THIS, anim_nutmegbow_fall_right, 1);
				THIS->mirror = NO_MIRROR;
				break;
			case 7:
				THIS->x = nutmeg_sprite->x+8;
				SetSpriteAnim(THIS, anim_nutmegbow_fall_left, 1);
				THIS->mirror = V_MIRROR;
				break;
		}
	}
	else if (health == full && lostbow == true) {
		//lostbow = true;
		
		SetSpriteAnim(THIS, anim_nutmegbow_static, 1);
		
		if (bow_counter == 0) {
			//bow_x = 0;
			//bow_catch_x = nutmeg_sprite->x - 8;

			if (bowanim == 9) {
				//bow_catch_x = bow_catch_x + 16;
			}
		}

		if (bowanim == 8) { THIS->mirror = NO_MIRROR; }
		else if (bowanim == 9) { THIS->mirror = V_MIRROR; }

		switch (bow_counter) {
			case 1:  bow_y = -5; break;
			case 3:  bow_y = -4; break;
			case 5:  bow_y = -3; break;
			case 7:  bow_y = -2; break;
			case 9:  bow_y = -1; break;
			case 15: bow_y =  1; break;
			case 17: bow_y =  2; break;
			case 19: bow_y =  3; break;
			case 21: bow_y =  4; break;
			case 23: bow_y =  5; break;
			case 25: bow_y =  6; break;
			case 27: bow_y =  7; break;
			case 29: bow_y =  8; break;
			case 31: bow_y =  9; break;
			case 33: bow_y = 10; break;
			case 35: bow_y = 11; break;
			case 37: bow_y = 50; break;
			default: bow_y =  0; break;
		}

		TranslateSprite (THIS, 0, bow_y);

		bow_counter++;

		if (bow_counter >= 37) {
			health = low;
			bowanim = 10;
			SpriteManagerRemoveSprite(THIS);
		}
	}
}

void Destroy_SpriteNutmegBow() {
}