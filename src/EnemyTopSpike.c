#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "../src/GlobalVars.h"

extern Sprite * nutmeg_sprite;

const UINT8 anim_topspike_idle[] = {1, 0};

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
		if (health == full) {
			lostbow = true;
			bow_counter = 0;
			if (nutmeg_direction == right) { bowanim = 8; }
			else if (nutmeg_direction == left) { bowanim = 9; }
		}
		else if (health == low) {
			nutmeg_death = true;
			nutmegdeathtimer = 0;
			
			if (nutmeglives <= 0) { GameOver = true; }
			else { nutmeglives--; }
		}
	}
}

void Destroy_EnemyTopSpike() {
}