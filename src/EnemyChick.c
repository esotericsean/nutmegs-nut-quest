#include "Banks/SetBank2.h"
#include "SpriteManager.h"
#include "Scroll.h"

const UINT8 anim_chick_walk[] = {2, 2, 2};

void Start_EnemyChick() {
	THIS->coll_x = 2;
	THIS->coll_y = 1;
	THIS->coll_w = 5;
	THIS->coll_h = 7;

	THIS->lim_x = 9999;
	THIS->lim_y = 999;

	SetSpriteAnim(THIS, anim_chick_walk, 6);
	SPRITE_SET_VMIRROR(THIS);
}

void Update_EnemyChick() {
	if (SPRITE_GET_VMIRROR(THIS)) {
		//moving left
		if (TranslateSprite(THIS, -1, 0)) {
			SPRITE_UNSET_VMIRROR(THIS); 
		} else	if (!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x) >> 3), (THIS->y >> 3) + 2u)]) {
			SPRITE_UNSET_VMIRROR(THIS);
		}
	} else {
		//moving right
		if (TranslateSprite(THIS, +1, 0)) {
			SPRITE_SET_VMIRROR(THIS);
		} else if (!scroll_collisions[GetScrollTile(((THIS->x + THIS->coll_x + THIS->coll_w) >> 3), (THIS->y >> 3) + 2u)]) {
			SPRITE_SET_VMIRROR(THIS);
		}
	}
}

void Destroy_EnemyChick() {
}