#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_hand_idle[]  = {1, 0};
static const UINT8 anim_hand_open[]  = {28, 0,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
static const UINT8 anim_hand_karate[] = {1, 3};
static const UINT8 anim_hand_close[] = {28, 3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const UINT8 anim_hand_hurt[]  = {1, 4};

Sprite * spr_hand;

	// hand position chart //
	
	// 0 = idle, facing left, right side of screen
	// 1 = start to open, facing left, right side
	// 2 = hand open karate chop, facing left, right side
	// 3 = start to close, facing left, right side
	// 4 = hurt, facing left, right side

	// 5 = idle, facing right, left side
	// 6 = start to open, facing right, left side
	// 7 = hand open karate chop, facing right, left side
	// 8 = start to close, facing right, left side
	// 9 = hurt, facing right, left side

void START (void)
{
	if (levelorientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_hand_idle, 1);
	THIS->mirror = NO_MIRROR;
}

void UPDATE(void) 
{
	//Jump on/hurt hand
	if (handpos == 4 || handpos == 9) handhurt = 1;
	else if (handpos == 0 || handpos == 5) handhurt = 0;

	//Hand Animations - Right Side Facing Left
	if (handpos == 0 && handhurt == 0) {
		THIS->mirror = NO_MIRROR;
		SetSpriteAnim(THIS, anim_hand_idle, 1); //idle
	}
	else if (handpos == 1 && handhurt == 0) {
		THIS->mirror = NO_MIRROR;
		SetSpriteAnim(THIS, anim_hand_open, 15); //start to open
	}
	else if (handpos == 2 && handhurt == 0) {
		THIS->mirror = NO_MIRROR;
		SetSpriteAnim(THIS, anim_hand_karate, 1); //karate chop
	}
	else if (handpos == 3 && handhurt == 0) {
		THIS->mirror = NO_MIRROR;
		SetSpriteAnim(THIS, anim_hand_close, 15); //start to close
	}
	else if (handpos == 4) {
		THIS->mirror = NO_MIRROR;
		SetSpriteAnim(THIS, anim_hand_hurt, 1); //hurt
	}
	//Hand Animations - Left Side Facing Right
	else if (handpos == 5 && handhurt == 0) {
		THIS->mirror = V_MIRROR;
		SetSpriteAnim(THIS, anim_hand_idle, 1); //idle
	}
	else if (handpos == 6 && handhurt == 0) {
		THIS->mirror = V_MIRROR;
		SetSpriteAnim(THIS, anim_hand_open, 15); //start to open
	}
	else if (handpos == 7 && handhurt == 0) {
		THIS->mirror = V_MIRROR;
		SetSpriteAnim(THIS, anim_hand_karate, 1); //karate chop
	}
	else if (handpos == 8 && handhurt == 0) {
		THIS->mirror = V_MIRROR;
		SetSpriteAnim(THIS, anim_hand_close, 15); //start to close
	}
	else if (handpos == 9) {
		THIS->mirror = V_MIRROR;
		SetSpriteAnim(THIS, anim_hand_hurt, 1); //hurt
	}

	//hurt hand if jump on it
	if (CheckCollision(THIS, spr_nutmeg) && nutmeg_death == false) {
		if ( movestate == inair && accelY > 0 )
		{
			PlayFx(CHANNEL_1, 10, 0x4f, 0xC7, 0xF3, 0x73, 0x86);
			accelY = -400;
			jumpPeak = 0;
			movestate = inair;

			if (abletohurthand == true) {
				handhealth = handhealth + 1;
				abletohurthand = false;
			}
			
			if (handphase == 0 || handphase == 2) handpos = 4; //hand on the right side, facing left
			else if (handphase == 1 || handphase == 3) handpos = 9; //hand on left side, facing right
		}
		else
		{
			//die if touch hand
			nutmeg_hit();
		}
	}
}

void DESTROY(void) 
{
}