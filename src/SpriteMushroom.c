#include "Banks/SetAutoBank.h"
#ifdef USE_CBT_FX
#include "Sound.h"
#undef PlayFx
#define PlayFx(...) do {} while(0)
#endif
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sound.h"
/* do not disable PlayFx while diagnosing */
#include "../src/GlobalVars.h"

extern Sprite * spr_nutmeg;

static const UINT8 anim_mushroom_moving[] = {4, 0, 0, 1, 1};

void Start_SpriteMushroom(void) 
{
	THIS->lim_x = 500;
	THIS->lim_y = 144;

	SetSpriteAnim(THIS, anim_mushroom_moving, 10);
}

void Update_SpriteMushroom(void) 
{
	//mushroom bounce
    if (CheckCollision(THIS, spr_nutmeg)) {
#ifdef USE_CBT_FX
        Sfx_MushroomBounce();
#endif
		
		INT16 acclY = nutmeg.enemyBounceY;
		acclY += (nutmeg.enemyBounceY >> 2);
		nutmeg.speedY = -acclY;
		nutmeg.jumpPeak = 0;
		nutmeg.movestate = inair;
	}
}

void Destroy_SpriteMushroom(void) {
}