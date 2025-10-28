// Place SFX data in a banked unit to keep bank0 small
#pragma bank 2
// Minimal set to avoid bank0 overflow during first integration
#include "third_party/cbtfx/include/cbtfx.c" // driver provides CBTFX_init/update
#include "third_party/cbtfx/include/sfx/SFX_00.c" // general pickup/coin
#include "third_party/cbtfx/include/sfx/SFX_01.c" // jump/alt


