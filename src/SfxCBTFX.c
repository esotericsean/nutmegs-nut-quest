#ifdef USE_CBT_FX

#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>
#include <gb/gb.h>
#include "BankManager.h"
#include "third_party/cbtfx/cbtfx.h"
extern UINT8 CBTFX_priority;
extern UINT8 CBTFX_size;

// Double-buffered HOME RAM staging to avoid overwriting the active buffer
// Size chosen to fit longest hammeredfx exports comfortably
static unsigned char s_cbtfx_buf[2][192];
static UINT8 s_active_idx = 0; // index of buffer currently used by the driver

// game feel: when nonzero, the next SFX played gets its pitch nudged by a
// random delta within +/- this many 11-bit frequency units (CH2), and the
// noise divider stepped by one (CH4). Reset after each play.
UINT8 cbtfx_pitch_var = 0;

// Walk the staged copy and apply the pitch delta in place.
// Frame layout (see cbtfx.c): len[+pan] [NR21] vol [NR23 NR24] [NR43]
// BANKED so it stays out of bank 0; the banked-call thunk handles switching.
void cbtfx_apply_pitch_var(unsigned char *buf) BANKED {
    UINT8 range = cbtfx_pitch_var;
    INT16 delta = (INT16)(DIV_REG & (UINT8)((range << 1) - 1)) - (INT16)range;
    UINT8 ch = buf[0];
    UINT8 frames = buf[1];
    unsigned char *p = buf + 2;
    for (UINT8 f = 0; f < frames; ++f) {
        UINT8 flen = *p++;
        if (flen & 0x80u) p++;       // pan byte
        if (ch & 0x80u) p++;         // NR21 (duty/length)
        p++;                          // shared volume
        if (ch & 0x80u) {            // NR23/NR24: 11-bit tone frequency
            INT16 freq = (INT16)(p[0] | ((UINT16)(p[1] & 0x07u) << 8)) + delta;
            if (freq < 0) freq = 0;
            if (freq > 2047) freq = 2047;
            p[0] = (UINT8)freq;
            p[1] = (p[1] & 0xF8u) | (UINT8)((UINT16)freq >> 8);
            p += 2;
        }
        if (ch & 0x20u) {            // NR43: step the noise divider by one
            UINT8 div = *p & 0x07u;
            if (delta >= 0) { if (div < 7u) div++; }
            else { if (div > 0u) div--; }
            *p = (*p & 0xF8u) | div;
            p++;
        }
    }
}

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
        if (cbtfx_pitch_var) {
            cbtfx_apply_pitch_var(s_cbtfx_buf[next_idx]);
            cbtfx_pitch_var = 0;
        }
        CBTFX_priority = 0;
        s_active_idx = next_idx;
        CBTFX_init(s_cbtfx_buf[s_active_idx]);
    }
}

#endif

#ifdef USE_CBT_FX
// Driver link disabled for now
#endif


