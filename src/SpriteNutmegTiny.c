#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
#include "Scroll.h"
#include "Keys.h"
#include "ZGBMain.h"

#include "../src/GlobalVars.h"

Sprite * spr_nutmegtiny;

const UINT8 anim_nutmegtiny_idle[] = {4, 0, 0, 0, 1};

void Start_SpriteNutmegTiny() {
	/*THIS->coll_x = 2;
	THIS->coll_y = 1;
	THIS->coll_w = 5;
	THIS->coll_h = 7;*/

	THIS->lim_x = 9999;
	THIS->lim_y = 999;

	SetSpriteAnim(THIS, anim_nutmegtiny_idle, 6);

	//start on level 1
	//W1LevelSelection = 1;
}

void Update_SpriteNutmegTiny() {
}

void Destroy_SpriteNutmegTiny() {
}