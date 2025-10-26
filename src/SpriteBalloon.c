#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
#include "Sfx.h"
#include "../src/GlobalVars.h"

extern Sprite * spr_nutmeg;


static const UINT8 anim_balloon_empty[]  = {1, 0};
static const UINT8 anim_balloon_static[] = {1, 1};
static const UINT8 anim_balloon_jumped[] = {1, 2};
static const UINT8 anim_balloon_popped[] = {9, 2, 2, 3, 4, 0, 0, 0, 0, 0};

static UINT8 balloonjump;
static bool balloonpop;
static UINT8 ballooncounter;
static UINT8 balloonspring;
static UINT8 balloonpopcount;

void Start_SpriteBalloon(void) 
{
	if (level.orientation == horizontal) {
		THIS->lim_x = 160; //350
		THIS->lim_y = 144;
	}
	else if (level.orientation == vertical) {
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

void Update_SpriteBalloon(void) 
{
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

        if (balloonpopcount == 0) { Sfx_BalloonPop(); }
        if (balloonpopcount < 25) balloonpopcount++;

        if (balloonpopcount >= 20) {
            SetSpriteAnim(THIS, anim_balloon_empty, 1);
            SpriteManagerRemoveSprite (THIS);
        }
    }

    if (CheckCollision(THIS, spr_nutmeg)) {
        if (balloonjump < 2) { Sfx_Stomp(); }
		nutmeg.jumpPeak = 0;
		nutmeg.movestate = inair;

		if (balloonjump == 0) { nutmeg.speedY = -(nutmeg.enemyBounceY>>1); balloonjump = 1; }
		else if (balloonjump == 1) { nutmeg.speedY = -nutmeg.enemyBounceY; balloonjump = 2; }
	}
}

void Destroy_SpriteBalloon(void) 
{
}