#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "ZGBMain.h"

const UINT8 anim_star_1[] = {6, 2, 2, 1, 0, 0, 0};

void Start_SpriteStar(void) 
{
	THIS->lim_x = 200;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_star_1, 12);

	THIS->custom_data[0] = 0;
	THIS->custom_data[1] = (UINT8) (-1);
}

void Update_SpriteStar(void) 
{
	if (THIS->custom_data[0] >= 35) 
	{
		SpriteManagerRemoveSprite(THIS);
		return;
	}
	
	THIS->custom_data[0] ++;
	

	THIS->x += (INT8) THIS->custom_data[1];
}

void Destroy_SpriteStar(void) 
{
}

// Add a pair of star travelling left and right,
void AddStarPair (UINT16 x, UINT16 y) BANKED
{
	SpriteManagerAdd(SpriteStar, x, y);
	
	Sprite *r = SpriteManagerAdd(SpriteStar, x, y);
	r->custom_data[1] = 1;
}

// Add a pair of star travelling left and right, left at pos, right = x + 8
void AddStarPairWide (UINT16 x, UINT16 y) BANKED
{
	SpriteManagerAdd(SpriteStar, x, y);
	
	Sprite *r = SpriteManagerAdd(SpriteStar, x+8, y);
	r->custom_data[1] = 1;
}