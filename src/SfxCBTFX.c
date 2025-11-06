#ifdef USE_CBT_FX

#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>
#include <gb/gb.h>
#include <string.h>
#include "BankManager.h"
#include "third_party/cbtfx/cbtfx.h"
extern UINT8 CBTFX_priority;
extern UINT8 CBTFX_size;

// Double-buffered HOME RAM staging to avoid overwriting the active buffer
// Size chosen to fit longest hammeredfx exports comfortably
static unsigned char s_cbtfx_buf[2][192];
static UINT8 s_active_idx = 0; // index of buffer currently used by the driver
void Sfx_Cbtfx_PlayFromBanked(const unsigned char *sfx_ptr, UINT16 sfx_len, UINT8 bank) NONBANKED {
    CRITICAL {
        UINT8 next_idx = s_active_idx ^ 1u;
        const unsigned char *src;
        UINT8 channels;
        UINT8 frames;
        UINT16 copy_len = 2;
        UINT16 i;

        PUSH_BANK(bank);
        src = sfx_ptr;
        channels = src[0];
        frames = src[1];

        const unsigned char *ptr = src + 2;
        for (UINT8 f = 0; f < frames; ++f) {
            UINT8 frame_len = *ptr++;
            copy_len += 1;
            if (frame_len & 0x80u) { ptr++; copy_len++; }
            if (channels & 0x80u)  { ptr++; copy_len++; }
            ptr++; copy_len++; // shared volume
            if (channels & 0x80u) { ptr += 2; copy_len += 2; }
            if (channels & 0x20u) { ptr++; copy_len++; }
        }
        if (copy_len > sizeof(s_cbtfx_buf[0])) copy_len = sizeof(s_cbtfx_buf[0]);

        for (i = 0; i < copy_len; ++i) {
            s_cbtfx_buf[next_idx][i] = src[i];
        }
        POP_BANK();

        s_cbtfx_buf[next_idx][0] = (s_cbtfx_buf[next_idx][0] & 0xF0) | ((s_cbtfx_buf[next_idx][0] & 0x0F) ? (s_cbtfx_buf[next_idx][0] & 0x0F) : 0x01);
        CBTFX_priority = 0;
        s_active_idx = next_idx;
        CBTFX_init(s_cbtfx_buf[s_active_idx]);
    }
}

#endif

#ifdef USE_CBT_FX
// Driver link disabled for now
#endif


