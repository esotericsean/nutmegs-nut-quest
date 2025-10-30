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
    0x21, // CH4 used + priority 1
    0x01, // 1 frame
    0x06, // frame length (no pan)
    0x0F, // volume nibble (15), envelope 0
    0x33  // NR43 noise (coarse, short)
};

// Export length for use from headers without sizeof on incomplete type
const UINT8 CBTFX_SFX_Jump_Len = (UINT8)sizeof(CBTFX_SFX_Jump);

#endif


