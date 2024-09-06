#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

static const UINT8 anim_blinkcinnamon[] = {20,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 1, 0, 0, 0, 0, 0, 1};

void Start_SpriteBlinkCinnamon(void) 
{
    SetSpriteAnim(THIS, anim_blinkcinnamon, 9);
}

void Update_SpriteBlinkCinnamon(void) 
{
}

void Destroy_SpriteBlinkCinnamon(void)
{
}