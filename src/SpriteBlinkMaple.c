#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

const UINT8 anim_blinkmaple[] = {16,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 1};

void Start_SpriteBlinkMaple() {
    SetSpriteAnim(THIS, anim_blinkmaple, 4);
}

void Update_SpriteBlinkMaple() {
}

void Destroy_SpriteBlinkMaple() {
}