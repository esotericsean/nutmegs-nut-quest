#include "Banks/SetAutoBank.h"
#include "Sound.h"
#include "SpriteManager.h"
#include "GlobalVars.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_acorn_moving[] = {8, 0, 0, 0, 1, 2, 2, 2, 1};
static const UINT8 anim_acorn_static[] = {1, 0};

void Start_SpriteAcorn(void) {
	if (level.orientation == horizontal) {
		THIS->lim_x = 350;
		THIS->lim_y = 144;
	}
	else if (level.orientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_acorn_moving, 10);
}

void Update_SpriteAcorn(void) 
{
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
	SetSpriteAnim(acorn, anim_acorn_static, 1);
}