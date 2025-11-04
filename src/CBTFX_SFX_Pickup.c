#ifdef USE_CBT_FX

#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>

BANKREF(CBTFX_SFX_Pickup)

// Pickup: bright CH2 blip, 2 frames
const unsigned char CBTFX_SFX_Pickup[] = {
	0x81, // CH2 + prio 1
	0x02, // 2 frames
	// Frame 1
	0x86, // len 6 | pan present
	0x22, // pan CH2 both L/R
	0x9F, // NR21 duty/length
	0xF0, // shared -> NR22 = 0xF0
	0xD0, // NR23
	0x86, // NR24
	// Frame 2 (short repeat)
	0x84, // len 4 | pan present
	0x22,
	0x9F,
	0xF0,
	0xD0,
	0x86
};

const UINT8 CBTFX_SFX_Pickup_Len = (UINT8)sizeof(CBTFX_SFX_Pickup);

#endif
