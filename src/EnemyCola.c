#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "GlobalVars.h"

Sprite * spr_cola;

const UINT8 anim_cola[]  = {1, 0};

UINT8 cola_counter;
UINT8 cola_faster;
UINT8 cola_bounce;
UINT8 cola_blink_counter;

void START() {
	THIS->lim_x = 350;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_cola, 1);

	cola_counter = 0;
	cola_faster = 0;
	cola_bounce = 0;

	cola_blink_counter = 0;
}

void UPDATE() {
	if (cola_counter == 0 || cola_counter == 2) {
		if (THIS->y < 86 && cola_bounce == 0) {
			TranslateSprite (THIS, 0, 1 + cola_faster); //checks for collisions
		}
		else if (THIS->y >= 86) {
			cola_bounce = 1;
		}

		if (cola_bounce == 1) {
			TranslateSprite (THIS, 0, -cola_faster);
			if (cola_faster > 0) cola_faster = cola_faster - 1;

			if (cola_faster < 2) {
				cola_bounce = 2;
			}
		}

		if (THIS->y < 86 && cola_bounce == 2) {
			TranslateSprite (THIS, 0, 1 + cola_faster); //checks for collisions
		}
		else if (THIS->y >= 86 && cola_bounce == 2) {
			cola_bounce = 3;
		}
	}

	cola_counter++;
	if (cola_counter > 3) {
		cola_counter = 0;
		if (cola_bounce == 0 || cola_bounce == 2) cola_faster++;
	}

	cola_blink_counter++;
	if (cola_blink_counter == 100) {
		THIS->x = THIS->x + 100; // move the can offscreen and back several times to simulate blinking before destroying it
	}
	else if (cola_blink_counter == 105) {
		THIS->x = THIS->x - 100;
	}
	else if (cola_blink_counter == 110) {
		THIS->x = THIS->x + 100;
	}
	else if (cola_blink_counter == 115) {
		THIS->x = THIS->x - 100;
	}
	else if (cola_blink_counter == 120) {
		THIS->x = THIS->x + 100;
	}
	else if (cola_blink_counter == 125) {
		THIS->x = THIS->x - 100;
	}
	else if (cola_blink_counter == 130) {
		SpriteManagerRemoveSprite(THIS);
	}
}

void DESTROY() {
}