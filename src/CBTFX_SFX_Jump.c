#ifdef USE_CBT_FX

#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>

BANKREF(CBTFX_SFX_Jump)

// Simple CH4 noise burst as a jump placeholder to clearly distinguish from legacy
// Format summary for CH4-only:
// [0]: channels/flags (0x20=CH4) + priority (low nibble)
// [1]: number of frames
// Per frame:
//  len, [pan?], VOL_NIBBLE, NR43
const unsigned char CBTFX_SFX_Jump[] = {
    0x80, // CH2 used + priority 0 (lowest)
    0x03, // 3 frames
    // Frame 1
    0x8A, // len 10 | pan present
    0x22, // pan: CH2 both L/R
    0x9F, // NR21 duty/length (50% duty, short length)
    0xF0, // shared -> NR22 = 0xF0 (max vol)
    0xC9, // NR23
    0xC4, // NR24 (hi freq + trigger)
    // Frame 2 (repeat to prolong)
    0x8A,
    0x22,
    0x9F,
    0xF0,
    0xC9,
    0xC4,
    // Frame 3
    0x8A,
    0x22,
    0x9F,
    0xF0,
    0xC9,
    0xC4
};

// Export length for use from headers without sizeof on incomplete type
const UINT16 CBTFX_SFX_Jump_Len = (UINT16)sizeof(CBTFX_SFX_Jump);

#endif


