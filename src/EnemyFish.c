#include "Banks/SetBank4.h"
#include "SpriteManager.h"

UINT8 fishcounter = 0; // counter

const UINT8 anim_fish_idle[] = {1, 0};

void Start_EnemyFish() {
	THIS->coll_x = 3;
	THIS->coll_y = 3;
	THIS->coll_w = 13;
	THIS->coll_h = 12;

	THIS->lim_x = 2000;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_fish_idle, 1);
	SPRITE_SET_VMIRROR(THIS);

	fishcounter = 0;
}

void Update_EnemyFish() {
	if (fishcounter >=  0 && fishcounter < 30) TranslateSprite(THIS, 0, -2);
	if (fishcounter >= 30 && fishcounter < 40) TranslateSprite(THIS, 0, -1);
	if (fishcounter >= 42 && fishcounter < 52) TranslateSprite(THIS, 0, 1);
	if (fishcounter >= 52 && fishcounter < 82) TranslateSprite(THIS, 0, 2);

	if (fishcounter >=  0 && fishcounter < 20) SPRITE_SET_VMIRROR(THIS);
	if (fishcounter >= 20 && fishcounter < 41) SPRITE_UNSET_VMIRROR(THIS);
	if (fishcounter >= 41 && fishcounter < 61) SPRITE_SET_VMIRROR(THIS);
	if (fishcounter >= 61 && fishcounter < 81) SPRITE_UNSET_VMIRROR(THIS);

	fishcounter++;

	if (fishcounter >= 156) fishcounter = 0;
}

void Destroy_EnemyFish() {
}