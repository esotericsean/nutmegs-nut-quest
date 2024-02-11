#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"

extern Sprite * spr_nutmeg;

UINT8 balloonjump;
bool balloonpop;

const UINT8 anim_balloon_empty[]  = {1, 0};
const UINT8 anim_balloon_static[] = {1, 1};
const UINT8 anim_balloon_jumped[] = {1, 2};
const UINT8 anim_balloon_popped[] = {9, 2, 2, 3, 4, 0, 0, 0, 0, 0};

UINT8 ballooncounter;
UINT8 balloonspring;
UINT8 balloonpopcount;

void Start_SpriteBalloon() {
	if (levelorientation == horizontal) {
		THIS->lim_x = 160; //350
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_balloon_static, 1);

	ballooncounter = 0;
	balloonjump = 0;
	balloonpop = false;
	balloonspring = 0;
	balloonpopcount = 0;
}

void Update_SpriteBalloon() {
	// if balloon hasn't been popped, move it up and right
	if (balloonpop == false) {
		ballooncounter++;

		if (ballooncounter > 14) ballooncounter = 0;
		
		switch (ballooncounter) {
			case  7: TranslateSprite (THIS, 0, -1); break;
			case 14: TranslateSprite (THIS, 1, -1); break;
			default: TranslateSprite (THIS, 0,  0); break;
		}
	}

	// haven't jumped on it yet
	if (balloonjump == 0) {
		SetSpriteAnim(THIS, anim_balloon_static, 1);
	}

	// jumped once
	else if (balloonjump == 1) {
		if (balloonspring == 0) SetSpriteAnim(THIS, anim_balloon_jumped, 1);
		else if (balloonspring >= 20) SetSpriteAnim(THIS, anim_balloon_static, 1);

		if (balloonspring < 21) balloonspring++;
	}

	// jumped twice
	else if (balloonjump == 2) {
		SetSpriteAnim(THIS, anim_balloon_popped, 20);

		if (balloonpopcount < 25) balloonpopcount++;

		if (balloonpopcount >= 20) {
			SetSpriteAnim(THIS, anim_balloon_empty, 1);
			SpriteManagerRemoveSprite (THIS);
		}
	}

	if (CheckCollision(THIS, spr_nutmeg)) {
		PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
		jumpPeak = 0;
		movestate = inair;

		if (balloonjump == 0) { accelY = -300; balloonjump = 1; }
		else if (balloonjump == 1) { accelY = -600; balloonjump = 2; }
	}
}

void Destroy_SpriteBalloon() {
}