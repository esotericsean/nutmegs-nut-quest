#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"

extern Sprite * nutmeg_sprite;

UINT16 rockithcounter = 0;
UINT8 rockithdirection = 0; // 0 is left, 1 is right

// 0 is blank
// 1 is rock form
// 2 is eye open
// 3 is stand up (walk frame 1)
// 4 is walk frame 2
// 5 is flatten
// 6, 7, 8 is death poof
const UINT8 anim_rockith_idle[]  	 = {1, 1};
const UINT8 anim_rockith_eyeball[]   = {1, 2};
const UINT8 anim_rockith_stand[] 	 = {8, 2, 2, 2, 2, 3, 3, 3, 3};
const UINT8 anim_rockith_walk[]  	 = {2, 3, 4};
const UINT8 anim_rockith_death[] 	 = {13, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0};
const UINT8 anim_rockith_death_alt[] = {16, 5, 5, 5, 5, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0};

bool rockdamage;

void Start_EnemyRockith() {
	/*THIS->coll_x = 0;
	THIS->coll_y = 3;
	THIS->coll_w = 8;
	THIS->coll_h = 5;*/

	if (levelorientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_rockith_idle, 1);
	//SPRITE_UNSET_VMIRROR(THIS);
	THIS->mirror = NO_MIRROR;

	rockithcounter = 0;
	rockdamage = false;
}

void Update_EnemyRockith() {
	//rock mode
	if (rockithcounter == 0) {
		SetSpriteAnim(THIS, anim_rockith_idle, 1);
		rockdamage = false;
	}
	//eyeball mode (watch out! can't hurt you yet)
	else if (rockithcounter >= 150 && rockithcounter < 180) {
		SetSpriteAnim(THIS, anim_rockith_eyeball, 1);
		rockdamage = false;
	}
	//stand mode (ahh! still can't hurt you, but getting close!)
	else if (rockithcounter >= 180 && rockithcounter < 200) {
		SetSpriteAnim(THIS, anim_rockith_stand, 5);
		rockdamage = false;
	}
	//walk mode (hurt mode activated!)
	else if (rockithcounter > 200 && rockithcounter < 250) {
		SetSpriteAnim(THIS, anim_rockith_walk, 5);
		rockdamage = true;
		if (rockithdirection == 0) TranslateSprite (THIS, -1, 0);
		else if (rockithdirection == 1) TranslateSprite (THIS, 1, 0);
	}
	//back to rock mode
	else if (rockithcounter >= 250) {
		SetSpriteAnim(THIS, anim_rockith_idle, 1);
		TranslateSprite (THIS, 0, 0);
		rockdamage = false;
	}

	rockithcounter++;

	if (rockithcounter > 350) {
		if (rockithdirection == 0) {
			rockithdirection = 1;
			//SPRITE_SET_VMIRROR(THIS);
			THIS->mirror = V_MIRROR;
		}
		else if (rockithdirection == 1) {
			rockithdirection = 0;
			//SPRITE_UNSET_VMIRROR(THIS);
			THIS->mirror = NO_MIRROR;
		}

		rockithcounter = 0;
	}

	//kill rockith if jump on it
	if (CheckCollision(THIS, nutmeg_sprite) && movestate == inair && accelY > 0 && nutmeg_death == false) {
		PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
		isjumping = true;
		accelY = -600;
		jumpPeak = 0;
		movestate = inair;
		
		if (nutmeg_direction == right) {
			SpriteManagerAdd(SpriteStarLeft, THIS->x, THIS->y+1);
			SpriteManagerAdd(SpriteStarRight, THIS->x, THIS->y+1);
		}
		else if (nutmeg_direction == left) {
			SpriteManagerAdd(SpriteStarLeft, THIS->x-6, THIS->y+1);
			SpriteManagerAdd(SpriteStarRight, THIS->x-6, THIS->y+1);
		}

		SpriteManagerRemoveSprite (THIS);
	}
	//die if touch rockith
	else if (CheckCollision(THIS, nutmeg_sprite) && rockdamage == true && movestate == grounded && nutmeg_death == false) {
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

void Destroy_EnemyRockith() {
}