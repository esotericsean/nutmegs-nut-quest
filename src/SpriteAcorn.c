#include "Banks/SetAutoBank.h"
#include "Sound.h"
#include "SpriteManager.h"
#include "GlobalVars.h"

bool isAcornMoving;
extern Sprite * spr_nutmeg;

const UINT8 anim_acorn_moving[] = {8, 0, 0, 0, 1, 2, 2, 2, 1};
const UINT8 anim_acorn_static[] = {1, 0};

void Start_SpriteAcorn() {
	if (levelorientation == horizontal) {
		THIS->lim_x = 350;
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	if (isAcornMoving == true) SetSpriteAnim(THIS, anim_acorn_moving, 10);
	else if (isAcornMoving == false) SetSpriteAnim(THIS, anim_acorn_static, 1);
}

void Update_SpriteAcorn() {
	if (CheckCollision(THIS, spr_nutmeg)) {
		PlayFx(CHANNEL_1, 10, 0x00, 0x81, 0x83, 0xA3, 0x87);
		acorncounter++;
		SpriteManagerRemoveSprite (THIS);
	}
}

void Destroy_SpriteAcorn() {
}