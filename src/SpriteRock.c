#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "../src/GlobalVars.h"

const UINT8 anim_rock_idle[] = {1, 0};

void Start_SpriteRock() {
	if (levelorientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_rock_idle, 1);
}

void Update_SpriteRock() {
}

void Destroy_SpriteRock() {
}