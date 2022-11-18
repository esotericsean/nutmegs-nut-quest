#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "../src/GlobalVars.h"

const UINT8 anim_lightningspot[] = {11, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0};
const UINT8 anim_lightningspot_empty[] = {1, 0};

UINT8 lightningspotcounter;

void Start_EnemyLightningSpot() {
	if (levelorientation == horizontal) {
		THIS->lim_x = 500;
		THIS->lim_y = 144;
	}
	else if (levelorientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	SetSpriteAnim(THIS, anim_lightningspot, 60);

	lightningspotcounter = 0;
}

void Update_EnemyLightningSpot() {
	if (lightningspotcounter == 0) {
		//PlayFx(CHANNEL_4, 60, 0x3f, 0x81, 0x28, 0xC0);
	}

	lightningspotcounter++;

	if (lightningspotcounter >= 30) {
		lightningspotcounter = 31;
		SetSpriteAnim(THIS, anim_lightningspot_empty, 1);
		SpriteManagerRemoveSprite (THIS);
	}
}

void Destroy_EnemyLightningSpot() {
}