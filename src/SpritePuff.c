#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "SpriteManager.h"

static const UINT8 anim_puff_1[] = {7, 0, 1, 2, 3, 4, 5, 6};

void Start_SpritePuff(void) {
	THIS->mirror = NO_MIRROR;

	SetSpriteAnim (THIS, anim_puff_1, 32);
	THIS->custom_data[0] = 0; //death timer
	THIS->custom_data[1] = (INT8) -1; // x velocity
}

void Update_SpritePuff(void) {
	if (THIS->custom_data[0] >= 20) 
	{
		SpriteManagerRemoveSprite(THIS);
		return;
	}
	
	THIS->custom_data[0]++;
	THIS->x += (INT8) THIS->custom_data[1];
}

void Destroy_SpritePuff(void) {
}

void AddPuffPair (UINT16 x, UINT16 y) BANKED
{
	SpriteManagerAdd(SpritePuff, x, y);
	
	Sprite *r = SpriteManagerAdd(SpritePuff, x+8, y);
	r->custom_data[1] = 1;
	r->mirror = V_MIRROR;
}