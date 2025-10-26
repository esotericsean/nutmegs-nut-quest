#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "../src/GlobalVars.h"

void Start_SpriteCamera(void) 
{
    // Make the camera target fully transparent:
    // 1) Assign to an unused palette (7) in case any color indices are non-zero
#ifdef CGB
    SPRITE_SET_CGB_PALETTE(THIS, 7);
#endif
    // 2) Overwrite the camera sprite tiles in VRAM with zeros so all pixels use color index 0 (transparent)
    {
        static const unsigned char zeros32[32] = { 0 };
        // Camera is 8x16 => 2 tiles
        set_sprite_data(THIS->first_tile, 2, zeros32);
    }
}

void Update_SpriteCamera(void) 
{
}

void Destroy_SpriteCamera(void) 
{
}