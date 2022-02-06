#include "Banks/SetBank5.h"
#include "SpriteManager.h"

const UINT8 anim_blinkcinnamon[] = {20,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 1, 0, 0, 0, 0, 0, 1};

void Start_SpriteBlinkCinnamon() {
    SetSpriteAnim(THIS, anim_blinkcinnamon, 9);
}

void Update_SpriteBlinkCinnamon() {
}

void Destroy_SpriteBlinkCinnamon() {
}