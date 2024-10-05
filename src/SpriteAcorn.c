#include "Banks/SetAutoBank.h"
#include "Sound.h"
#include "SpriteManager.h"
#include "GlobalVars.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_acorn_static[] = {1, 0};

static const INT8 acornMoveYAtTime [] = {0,0,0,1,1,0,0,0,-1,-1};

#define IS_STILL_POS (0)
#define MOVE_POS (1)
#define TIMER_POS (2)

// acorn moves once per this many frames
#define MOVE_SPEED (10)

void Start_SpriteAcorn(void) {
	if (level.orientation == horizontal) {
		THIS->lim_x = 350;
		THIS->lim_y = 144;
	}
	else if (level.orientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_acorn_static, MOVE_SPEED);
	
	// setup these variables so the defaults are all 0
	// because the actorPosT stuff is overriding all the custom data fields
	THIS->custom_data[IS_STILL_POS] = false;
	THIS->custom_data[MOVE_POS] = 0;
	THIS->custom_data[TIMER_POS] = 0;
}


void Update_SpriteAcorn(void) 
{
	if (THIS->custom_data[IS_STILL_POS] == false)
	{
		THIS->custom_data[TIMER_POS] ++;
		if (THIS->custom_data[TIMER_POS] >= MOVE_SPEED)
		{
			THIS->custom_data[TIMER_POS] = 0;

			THIS->y += acornMoveYAtTime[THIS->custom_data[MOVE_POS]];
			THIS->custom_data[MOVE_POS]++;

			if (THIS->custom_data[MOVE_POS] >= sizeof (acornMoveYAtTime))
			{
				THIS->custom_data[MOVE_POS] =0;
			}
		}
	}

	if (CheckCollision(THIS, spr_nutmeg)) {
		PlayFx(CHANNEL_1, 10, 0x00, 0x81, 0x83, 0xA3, 0x87);
		nutmeg.acorns++;
		SpriteManagerRemoveSprite (THIS);
	}
}

void Destroy_SpriteAcorn(void) 
{
}

void SpriteAcornFreeze(Sprite *acorn) BANKED 
{
	acorn->custom_data[IS_STILL_POS] = true;
}