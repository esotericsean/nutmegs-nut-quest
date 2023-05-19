#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

const UINT8 anim_puff_1[] = {7, 0, 1, 2, 3, 4, 5, 6};

//UINT8 deathtimer3 = 0;

void Start_SpritePuffLeft() {
	THIS->lim_x = 200;
	THIS->lim_y = 144;

	THIS->mirror = NO_MIRROR;

	SetSpriteAnim (THIS, anim_puff_1, 32);

	//deathtimer3 = 0;

	THIS->custom_data[0] = 0; //deathtimer3
}

void Update_SpritePuffLeft() {
	if (THIS->custom_data[0] >= 20) SpriteManagerRemoveSprite(THIS);
	else THIS->custom_data[0]++;

	THIS->x--;
}

void Destroy_SpritePuffLeft() {
}