#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

static const UINT8 anim_blinkruby[] = {16,
									0, 0, 0, 0, 1, 0, 0, 0,1, 0,
                                    0, 0, 0, 0, 0, 0};

void Start_SpriteBlinkRuby(void) 
{
    SetSpriteAnim(THIS, anim_blinkruby, 4);
}

void Update_SpriteBlinkRuby(void) 
{
}

void Destroy_SpriteBlinkRuby(void) 
{
}