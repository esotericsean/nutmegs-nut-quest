#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Sfx.h"
#include "../src/GlobalVars.h"

extern Sprite * spr_nutmeg;

#define BALLOON_FLAGS         0
#define BALLOON_JUMP          1
#define BALLOON_SPRING        2
#define BALLOON_POPCOUNT      3
#define BALLOON_ALLOW_BOUNCE  4
#define BALLOON_COUNTER       5

#define BALLOON_FLAG_DRIFT_RIGHT (1u)
#define BALLOON_FLAG_SLOW_RISE   (2u)

static const UINT8 anim_balloon_empty[]  = {1, 0};
static const UINT8 anim_balloon_static[] = {1, 1};
static const UINT8 anim_balloon_jumped[] = {1, 2};
static const UINT8 anim_balloon_popped[] = {9, 2, 2, 3, 4, 0, 0, 0, 0, 0};

void Start_SpriteBalloon(void) 
{
	if (level.orientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (level.orientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_balloon_static, 1);

	THIS->custom_data[BALLOON_FLAGS] = 0;
	THIS->custom_data[BALLOON_JUMP] = 0;
	THIS->custom_data[BALLOON_SPRING] = 0;
	THIS->custom_data[BALLOON_POPCOUNT] = 0;
	THIS->custom_data[BALLOON_ALLOW_BOUNCE] = 1;
	THIS->custom_data[BALLOON_COUNTER] = 0;
}

void Update_SpriteBalloon(void) 
{
	UINT8 jump = THIS->custom_data[BALLOON_JUMP];

	// Rise until popped (each balloon tracks its own counter)
	if (jump < 2) {
		UINT8 flags = THIS->custom_data[BALLOON_FLAGS];
		UINT8 counter = THIS->custom_data[BALLOON_COUNTER] + 1;
		if (counter > 14) {
			counter = 0;
		}
		THIS->custom_data[BALLOON_COUNTER] = counter;

		if ((flags & BALLOON_FLAG_SLOW_RISE) != 0) {
			if ((counter & 3) == 0) {
				TranslateSprite(THIS, 0, -1);
			}
			if ((flags & BALLOON_FLAG_DRIFT_RIGHT) != 0 && (counter & 3) == 0) {
				TranslateSprite(THIS, 1, 0);
			}
		} else {
			// Default 1-6 drift: mostly up, occasional up-right (classic cycle)
			switch (counter) {
				case 7:
					TranslateSprite(THIS, 0, -1);
					break;
				case 14:
					TranslateSprite(THIS, 1, -1);
					break;
				default:
					break;
			}
		}
	}

	if (jump == 0) {
		SetSpriteAnim(THIS, anim_balloon_static, 1);
	}
	else if (jump == 1) {
		if (THIS->custom_data[BALLOON_SPRING] == 0) {
			SetSpriteAnim(THIS, anim_balloon_jumped, 1);
		} else if (THIS->custom_data[BALLOON_SPRING] >= 20) {
			SetSpriteAnim(THIS, anim_balloon_static, 1);
		}

		if (THIS->custom_data[BALLOON_SPRING] < 21) {
			THIS->custom_data[BALLOON_SPRING]++;
		}
	}
	else if (jump == 2) {
		SetSpriteAnim(THIS, anim_balloon_popped, 20);

		if (THIS->custom_data[BALLOON_POPCOUNT] == 0) {
			Sfx_BalloonPop();
		}
		if (THIS->custom_data[BALLOON_POPCOUNT] < 25) {
			THIS->custom_data[BALLOON_POPCOUNT]++;
		}

		if (THIS->custom_data[BALLOON_POPCOUNT] >= 20) {
			SetSpriteAnim(THIS, anim_balloon_empty, 1);
			SpriteManagerRemoveSprite(THIS);
			return;
		}
	}

	if (CheckCollision(THIS, spr_nutmeg)) {
		if (THIS->custom_data[BALLOON_ALLOW_BOUNCE]) {
			THIS->custom_data[BALLOON_ALLOW_BOUNCE] = 0;
			if (jump < 2) {
				Sfx_Stomp();
			}
			nutmeg.jumpPeak = 0;
			nutmeg.movestate = inair;

			if (jump == 0) {
				nutmeg.speedY = -(nutmeg.enemyBounceY >> 1);
				THIS->custom_data[BALLOON_JUMP] = 1;
			} else if (jump == 1) {
				nutmeg.speedY = -nutmeg.enemyBounceY;
				THIS->custom_data[BALLOON_JUMP] = 2;
			}
		}
	} else if (nutmeg.speedY >= 0) {
		THIS->custom_data[BALLOON_ALLOW_BOUNCE] = 1;
	}
}

void Destroy_SpriteBalloon(void) 
{
}
