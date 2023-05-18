#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"

const UINT8 anim_star_1[] = {6, 2, 2, 1, 0, 0, 0};

//UINT8 deathtimer = 0;
//THIS->custom_data[0] = 0;

void Start_SpriteStarLeft() {
	THIS->lim_x = 200;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_star_1, 12);

	THIS->custom_data[0] = 0;
}

void Update_SpriteStarLeft() {
	if (THIS->custom_data[0] >= 35) SpriteManagerRemoveSprite(THIS);
	else THIS->custom_data[0]++;

	THIS->x--;
}

void Destroy_SpriteStarLeft() {
}