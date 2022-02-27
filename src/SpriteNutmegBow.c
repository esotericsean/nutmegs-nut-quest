#include "Banks/SetBank6.h"
#include "SpriteManager.h"

const UINT8 anim_nutmegbow_idle[] = {4, 1, 2, 3, 4};
const UINT8 anim_nutmegbow_static[] = {1, 1};

// Nutmeg's head moves in a pattern of up, down, down, up

// When idle 	 speed is 	5
// When walking	 speed is 	15
// When running	 speed is 	50

// When jumping, falling, landing, or hurt, Nutmeg's head is static

// 0 = idle (5)
// 1 = walking (15)
// 2 = running (50)
// 3 = static (0)
UINT8 bowanim;

void Start_SpriteNutmegBow() {
	THIS->coll_x = 0;
	THIS->coll_y = 0;
	THIS->coll_w = 0;
	THIS->coll_h = 0;

	THIS->lim_x = 9999;
	THIS->lim_y = 999;

	SetSpriteAnim(THIS, anim_nutmegbow_static, 5);
	bowanim = 0;
}

void Update_SpriteNutmegBow() {
	switch (bowanim) {
	case 0:
		SetSpriteAnim(THIS, anim_nutmegbow_idle, 5);
		break;
	case 1:
		SetSpriteAnim(THIS, anim_nutmegbow_idle, 15);
		break;
	case 2:
		SetSpriteAnim(THIS, anim_nutmegbow_idle, 15);
		break;
	case 3:
		SetSpriteAnim(THIS, anim_nutmegbow_static, 1);
		break;
	}
}

void Destroy_SpriteNutmegBow() {
}