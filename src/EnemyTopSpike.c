#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * nutmeg_sprite;

static const UINT8 anim_topspike_idle[] = {1, 0};

void Start_EnemyTopSpike() {
	if (levelorientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_topspike_idle, 1);
	THIS->mirror = NO_MIRROR;
}

void Update_EnemyTopSpike() {
	//die if touch topspike
	if (CheckCollision(THIS, nutmeg_sprite) && accelY < 0 && nutmeg_death == false) {
		nutmeg_hit();
	}
}

void Destroy_EnemyTopSpike() {
}