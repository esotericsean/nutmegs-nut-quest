#include "Banks/SetAutoBank.h"
#ifdef USE_CBT_FX
#include "Sound.h"
#undef PlayFx
#define PlayFx(...) do {} while(0)
#endif
#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "../src/GlobalVars.h"

static const UINT8 anim_lightningspot[] = {11, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0};
static const UINT8 anim_lightningspot_empty[] = {1, 0};

static UINT8 lightningspotcounter;

void Start_EnemyLightningSpot (void) 
{
	if (level.orientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (level.orientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_lightningspot, 60);

	lightningspotcounter = 0;
}

void Update_EnemyLightningSpot (void) 
{
	if (lightningspotcounter == 0) {
        // visual warning only; audio plays on actual strike
	}

	lightningspotcounter++;

	if (lightningspotcounter >= 30) {
		lightningspotcounter = 31;
		SetSpriteAnim(THIS, anim_lightningspot_empty, 1);
		SpriteManagerRemoveSprite (THIS);
	}
}

void Destroy_EnemyLightningSpot (void) 
{
}