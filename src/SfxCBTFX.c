#ifdef USE_CBT_FX

#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>
#include "BankManager.h"
#include "third_party/cbtfx/cbtfx.h"

// Small HOME RAM buffer to stage CBT-FX SFX blobs copied from banked ROM
static unsigned char s_cbtfx_buf[64];

void Sfx_Cbtfx_PlayFromBanked(const unsigned char *sfx_ptr, UINT8 sfx_len, UINT8 bank) NONBANKED {
    UINT8 copy_len = sfx_len;
    if (copy_len > (UINT8)sizeof(s_cbtfx_buf)) copy_len = (UINT8)sizeof(s_cbtfx_buf);

    PUSH_BANK(bank);
    for (UINT8 i = 0; i != copy_len; ++i) {
        s_cbtfx_buf[i] = sfx_ptr[i];
    }
    POP_BANK();

    // Play staged SFX from RAM so updates don't depend on current ROM bank
    CBTFX_init(s_cbtfx_buf);
}

#endif

#ifdef USE_CBT_FX
// Driver link disabled for now
#endif


