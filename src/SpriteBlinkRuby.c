#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

const UINT8 anim_blinkruby[] = {16,
									0, 0, 0, 0, 1, 0, 0, 0,1, 0,
                                    0, 0, 0, 0, 0, 0};

void Start_SpriteBlinkRuby() {
    SetSpriteAnim(THIS, anim_blinkruby, 4);
}

void Update_SpriteBlinkRuby() {
}

void Destroy_SpriteBlinkRuby() {
}