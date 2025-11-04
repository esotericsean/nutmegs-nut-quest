#ifdef USE_CBT_FX

#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>

// Water Enter / Exit: CH4 splash
BANKREF(CBTFX_SFX_WaterSplash)
const unsigned char CBTFX_SFX_WaterSplash[] = {
	0x21, // CH4 + prio 1
	0x02, // 2 frames
	0x86, 0x88, 0x0C, 0x35, // len|pan, pan, NR42(vol), NR43(noise)
	0x84, 0x88, 0x08, 0x25
};
const UINT8 CBTFX_SFX_WaterSplash_Len = (UINT8)sizeof(CBTFX_SFX_WaterSplash);

// Water Stroke: CH2 clearer blip
BANKREF(CBTFX_SFX_WaterStroke)
const unsigned char CBTFX_SFX_WaterStroke[] = {
    0x81, // CH2 + prio 1
    0x02, // 2 frames
    0x86, 0x22, 0x9F, 0xF0, 0xE0, 0x84,
    0x84, 0x22, 0x9F, 0xE0, 0xE2, 0x84
};
const UINT8 CBTFX_SFX_WaterStroke_Len = (UINT8)sizeof(CBTFX_SFX_WaterStroke);

#endif
