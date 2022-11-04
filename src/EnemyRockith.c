#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

UINT16 rockithcounter = 0;
UINT8 rockithdirection = 0; // 0 is left, 1 is right

// 0 is blank
// 1 is rock form
// 2 is eye open
// 3 is stand up (walk frame 1)
// 4 is walk frame 2
// 5 is flatten
// 6, 7, 8 is death poof
const UINT8 anim_rockith_idle[]  	 = {1, 1};
const UINT8 anim_rockith_eyeball[]   = {1, 2};
const UINT8 anim_rockith_stand[] 	 = {8, 2, 2, 2, 2, 3, 3, 3, 3};
const UINT8 anim_rockith_walk[]  	 = {2, 3, 4};
const UINT8 anim_rockith_death[] 	 = {13, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0};
const UINT8 anim_rockith_death_alt[] = {16, 5, 5, 5, 5, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0};

void Start_EnemyRockith() {
	/*THIS->coll_x = 0;
	THIS->coll_y = 3;
	THIS->coll_w = 8;
	THIS->coll_h = 5;*/

	THIS->lim_x = 400;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_rockith_idle, 1);
	//SPRITE_UNSET_VMIRROR(THIS);
	THIS->mirror = NO_MIRROR;

	rockithcounter = 0;
}

void Update_EnemyRockith() {
	if (rockithcounter == 0) {
		SetSpriteAnim(THIS, anim_rockith_idle, 1);
	}
	else if (rockithcounter >= 250 && rockithcounter < 300) {
		SetSpriteAnim(THIS, anim_rockith_eyeball, 1);
	}
	else if (rockithcounter >= 300 && rockithcounter < 350) {
		SetSpriteAnim(THIS, anim_rockith_stand, 5);
	}
	else if (rockithcounter > 350 && rockithcounter < 400) {
		SetSpriteAnim(THIS, anim_rockith_walk, 5);
		if (rockithdirection == 0) TranslateSprite (THIS, -1, 0);
		else if (rockithdirection == 1) TranslateSprite (THIS, 1, 0);
	}
	else if (rockithcounter >= 400) {
		SetSpriteAnim(THIS, anim_rockith_idle, 1);
		TranslateSprite (THIS, 0, 0);
	}

	rockithcounter++;

	if (rockithcounter > 500) {
		if (rockithdirection == 0) {
			rockithdirection = 1;
			//SPRITE_SET_VMIRROR(THIS);
			THIS->mirror = V_MIRROR;
		}
		else if (rockithdirection == 1) {
			rockithdirection = 0;
			//SPRITE_UNSET_VMIRROR(THIS);
			THIS->mirror = NO_MIRROR;
		}

		rockithcounter = 0;
	}
}

void Destroy_EnemyRockith() {
}