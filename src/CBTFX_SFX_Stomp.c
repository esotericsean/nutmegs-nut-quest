#ifdef USE_CBT_FX

#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>

BANKREF(CBTFX_SFX_Stomp)

// Stomp: CH4 thud, 3 frames
const unsigned char CBTFX_SFX_Stomp[] = {
	0x21, // CH4 + prio 1
	0x03, // 3 frames
	// Frame 1
	0x88, // len 8 | pan present
	0x88, // pan CH4 both L/R
	0x0E, // shared -> NR42 = 0xE0 (loud)
	0x52, // NR43 (lower pitch)
	// Frame 2
	0x86,
	0x88,
	0x0C, // NR42 = 0xC0
	0x62,
	// Frame 3
	0x84,
	0x88,
	0x08, // NR42 = 0x80
	0x72
};

const UINT8 CBTFX_SFX_Stomp_Len = (UINT8)sizeof(CBTFX_SFX_Stomp);

#endif
