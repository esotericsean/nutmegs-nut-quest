#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"

extern Sprite * nutmeg_sprite;
Sprite * spr_spatula;

const UINT8 anim_spatula_spin[]  = {14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

UINT8 spatula_counter;

void START() {
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_spatula_spin, 10);

	spatula_counter = 0;
}

void UPDATE() {
	THIS->x = THIS->x - 1;

	//die if touch spatula
	if (CheckCollision(THIS, nutmeg_sprite) && nutmeg_death == false) {
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

void DESTROY() {
	spatula_counter = 0;
}