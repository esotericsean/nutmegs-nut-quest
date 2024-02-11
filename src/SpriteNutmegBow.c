#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "../src/GlobalVars.h"

extern Sprite * spr_nutmeg;
Sprite *spr_nutmegbow = 0;

static const UINT8 anim_nutmegbow_static[] = {1, 1};

static const UINT8 anim_nutmegbow_idle_right[] = {4, 1, 2, 3, 4};
static const UINT8 anim_nutmegbow_idle_left[]  = {4, 1, 2, 3, 4};

static const UINT8 anim_nutmegbow_walk_right[] = {4, 5, 6, 7, 8};
static const UINT8 anim_nutmegbow_walk_left[]  = {4, 5, 6, 7, 8};

static const UINT8 anim_nutmegbow_jump_right[] = {1, 9};
static const UINT8 anim_nutmegbow_jump_left[]  = {1, 9};

static const UINT8 anim_nutmegbow_fall_right[] = {1, 10};
static const UINT8 anim_nutmegbow_fall_left[]  = {1, 10};

// 0 = idle (5)
// 1 = walking (15)
// 2 = jump/fall (1)
// 3 = static (1)

UINT8 bowanim;
UINT8 bow_y;
UINT8 bow_counter;
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
	bow_y = 0;

	bow_counter = 0;
	spr_nutmegbow = THIS;
}

// the falling speed of the box at each bow_counter frame
const INT8 Y_OFFSET_AT_COUNTER [] = {
	0,
	-5,
	-4,
	-3,
	-2,
	-1,
	-1,
	0,
	0,
	1,
	1,
	2,
	2,
	3,
	3,
	4,
	4,
	5,
	5,
	6,
	6,
	7,
	7,
	8,
	8,
	9,
	9,
	10,
	10,
	11,
	11,
	12,
	12,
	13,
	13,
	14,
	14,
	0,
};

// returns false if the bow sprite has been destroyed
// can't use THIS, because it is called fromthe spr_nutmeg update fn
void nutmegBow_update(void ) BANKED 
{
	if (lostbow == false) {
		spr_nutmegbow->y = spr_nutmeg->y-24;

		switch (bowanim) {
			case 0:
				spr_nutmegbow->x = spr_nutmeg->x-8;
				SetSpriteAnim(spr_nutmegbow, anim_nutmegbow_idle_right, 5);
				spr_nutmegbow->mirror = NO_MIRROR;
				break;
			case 1:
				spr_nutmegbow->x = spr_nutmeg->x+8;
				SetSpriteAnim(spr_nutmegbow, anim_nutmegbow_idle_left, 5);
				spr_nutmegbow->mirror = V_MIRROR;
				break;
			case 2:
				spr_nutmegbow->x = spr_nutmeg->x-8;
				SetSpriteAnim(spr_nutmegbow, anim_nutmegbow_walk_right, 15);
				spr_nutmegbow->mirror = NO_MIRROR;
				break;
			case 3:
				spr_nutmegbow->x = spr_nutmeg->x+8;
				SetSpriteAnim(spr_nutmegbow, anim_nutmegbow_walk_left, 15);
				spr_nutmegbow->mirror = V_MIRROR;
				break;
			case 4:
				spr_nutmegbow->x = spr_nutmeg->x-8;
				SetSpriteAnim(spr_nutmegbow, anim_nutmegbow_jump_right, 1);
				spr_nutmegbow->mirror = NO_MIRROR;
				break;
			case 5:
				spr_nutmegbow->x = spr_nutmeg->x+8;
				SetSpriteAnim(spr_nutmegbow, anim_nutmegbow_jump_left, 1);
				spr_nutmegbow->mirror = V_MIRROR;
				break;
			case 6:
				spr_nutmegbow->x = spr_nutmeg->x-8;
				SetSpriteAnim(spr_nutmegbow, anim_nutmegbow_fall_right, 1);
				spr_nutmegbow->mirror = NO_MIRROR;
				break;
			case 7:
				spr_nutmegbow->x = spr_nutmeg->x+8;
				SetSpriteAnim(spr_nutmegbow, anim_nutmegbow_fall_left, 1);
				spr_nutmegbow->mirror = V_MIRROR;
				break;
		}
	}
	else if (health == full && lostbow == true) {
		SetSpriteAnim(spr_nutmegbow, anim_nutmegbow_static, 1);
	
		if (bowanim == 8) { spr_nutmegbow->mirror = NO_MIRROR; }
		else { spr_nutmegbow->mirror = V_MIRROR; }

		bow_y = Y_OFFSET_AT_COUNTER[bow_counter];
		TranslateSprite (spr_nutmegbow, 0, bow_y);

		bow_counter++;

		if (bow_counter >= 37) {
			health = low;
			bowanim = 10;
			SpriteManagerRemoveSprite(spr_nutmegbow);
		}
	}
}

void Update_SpriteNutmegBow() {
	// updates are done from the spr_nutmeg
}


void Destroy_SpriteNutmegBow() {
	spr_nutmegbow = 0;
}