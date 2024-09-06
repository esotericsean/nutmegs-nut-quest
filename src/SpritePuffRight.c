#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

const UINT8 anim_puff_2[] = {7, 0, 1, 2, 3, 4, 5, 6};

void Start_SpritePuffRight(void) {
	THIS->lim_x = 200;
	THIS->lim_y = 144;

	THIS->mirror = V_MIRROR;

	SetSpriteAnim(THIS, anim_puff_2, 32);

	THIS->custom_data[0] = 0; 
}

void Update_SpritePuffRight(void) { 
	if (THIS->custom_data[0] >= 20) 
	{
		SpriteManagerRemoveSprite(THIS);
		return;
	}
	
	THIS->custom_data[0]++;
	THIS->x++;
}

void Destroy_SpritePuffRight(void) {
}