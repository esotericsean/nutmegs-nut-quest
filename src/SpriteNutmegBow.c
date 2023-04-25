#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"

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

// Nutmeg's head moves in a pattern of up, down, down, up

// When idle 	 speed is 	5
// When walking	 speed is 	15
// When running	 speed is 	50

// When jumping, falling, landing, or hurt, Nutmeg's head is static

// 0 = idle (5)
// 1 = walking (15)
// 2 = jump/fall (1)
// 3 = static (1)

UINT8 bowanim;

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

void Start_SpriteNutmegBow() {
	THIS->lim_x = 500;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_nutmegbow_idle_right, 5);
	bowanim = 0;
}

void Update_SpriteNutmegBow() {
	switch (bowanim) {
		case 0:
			THIS->x = nutmeg_sprite->x-8;
			THIS->y = nutmeg_sprite->y-24;
			SetSpriteAnim(THIS, anim_nutmegbow_idle_right, 5);
			THIS->mirror = NO_MIRROR;
			break;
		case 1:
			THIS->x = nutmeg_sprite->x+8;
			THIS->y = nutmeg_sprite->y-24;
			SetSpriteAnim(THIS, anim_nutmegbow_idle_left, 5);
			THIS->mirror = V_MIRROR;
			break;
		case 2:
			THIS->x = nutmeg_sprite->x-8;
			THIS->y = nutmeg_sprite->y-24;
			SetSpriteAnim(THIS, anim_nutmegbow_walk_right, 15);
			THIS->mirror = NO_MIRROR;
			break;
		case 3:
			THIS->x = nutmeg_sprite->x+8;
			THIS->y = nutmeg_sprite->y-24;
			SetSpriteAnim(THIS, anim_nutmegbow_walk_left, 15);
			THIS->mirror = V_MIRROR;
			break;
		case 4:
			THIS->x = nutmeg_sprite->x-8;
			THIS->y = nutmeg_sprite->y-24;
			SetSpriteAnim(THIS, anim_nutmegbow_jump_right, 1);
			THIS->mirror = NO_MIRROR;
			break;
		case 5:
			THIS->x = nutmeg_sprite->x+8;
			THIS->y = nutmeg_sprite->y-24;
			SetSpriteAnim(THIS, anim_nutmegbow_jump_left, 1);
			THIS->mirror = V_MIRROR;
			break;
		case 6:
			THIS->x = nutmeg_sprite->x-8;
			THIS->y = nutmeg_sprite->y-24;
			SetSpriteAnim(THIS, anim_nutmegbow_fall_right, 1);
			THIS->mirror = NO_MIRROR;
			break;
		case 7:
			THIS->x = nutmeg_sprite->x+8;
			THIS->y = nutmeg_sprite->y-24;
			SetSpriteAnim(THIS, anim_nutmegbow_fall_left, 1);
			THIS->mirror = V_MIRROR;
			break;
	}
}

void Destroy_SpriteNutmegBow() {
}