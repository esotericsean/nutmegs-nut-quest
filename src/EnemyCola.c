#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_cola[]  = {1, 1};
static const UINT8 anim_cola_flash[]  = {2, 0, 1};

void START() {
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_cola, 1);

	THIS->custom_data[0] = 0; //cola counter
	THIS->custom_data[1] = 0; //cola faster
	THIS->custom_data[2] = 0; //cola bounce
	THIS->custom_data[3] = 0; //cola blink counter
}

void UPDATE() {
	if (THIS->custom_data[0] == 0 || THIS->custom_data[0] == 2) {
		if (THIS->y < 86 && THIS->custom_data[2] == 0) {
			TranslateSprite (THIS, 0, 1 + THIS->custom_data[1]); //checks for collisions
		}
		else if (THIS->y >= 86) {
			THIS->custom_data[2] = 1;
		}

		if (THIS->custom_data[2] == 1) {
			TranslateSprite (THIS, 0, -THIS->custom_data[1]);
			if (THIS->custom_data[1] > 0) THIS->custom_data[1] = THIS->custom_data[1] - 1;

			if (THIS->custom_data[1] < 2) {
				THIS->custom_data[2] = 2;
			}
		}

		if (THIS->y < 86 && THIS->custom_data[2] == 2) {
			TranslateSprite (THIS, 0, 1 + THIS->custom_data[1]); //checks for collisions
		}
		else if (THIS->y >= 86 && THIS->custom_data[2] == 2) {
			THIS->custom_data[2] = 3;
		}
	}

	THIS->custom_data[0]++;
	if (THIS->custom_data[0] > 3) {
		THIS->custom_data[0] = 0;
		if (THIS->custom_data[2] == 0 || THIS->custom_data[2] == 2) THIS->custom_data[1]++;
	}

	THIS->custom_data[3]++;
	/*
	if (THIS->custom_data[3] == 100) {
		THIS->x = THIS->x + 100; // move the can offscreen and back several times to simulate blinking before destroying it
	}
	else if (THIS->custom_data[3] == 105) {
		THIS->x = THIS->x - 100;
	}
	else if (THIS->custom_data[3] == 110) {
		THIS->x = THIS->x + 100;
	}
	else if (THIS->custom_data[3] == 115) {
		THIS->x = THIS->x - 100;
	}
	else if (THIS->custom_data[3] == 120) {
		THIS->x = THIS->x + 100;
	}
	else if (THIS->custom_data[3] == 125) {
		THIS->x = THIS->x - 100;
	}
	*/
	if (THIS->custom_data[3] >= 100 && THIS->custom_data[3] <= 125) {
		SetSpriteAnim(THIS, anim_cola_flash, 25);
	}
	else if (THIS->custom_data[3] == 130) {
		SpriteManagerRemoveSprite(THIS);
	}

	//die if touch cola
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg_death == false) {
		nutmeg_hit();
	}
}

void DESTROY() {
}