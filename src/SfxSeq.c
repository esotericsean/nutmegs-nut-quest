#pragma bank 0
#include "Banks/SetAutoBank.h"
#ifdef USE_CBT_FX
#include "Sound.h"
#undef PlayFx
#define PlayFx(...) do {} while(0)
#endif
#include <gbdk/platform.h>
#include "Sound.h"
/* do not disable PlayFx while diagnosing */

// Extremely small step sequencer; uses CH1 only to avoid clashes
// Steps advance every 3 frames by default

typedef struct {
    const UINT8 *steps;   // pointer to param blocks (5 bytes each)
    UINT8 num_steps;
    UINT8 idx;
    UINT8 timer;
    UINT8 period;         // frames per step
    UINT8 active;
} SfxSeqT;

static SfxSeqT seq;

void SfxSeq_Init(void) {
    seq.active = 0;
    seq.period = 3;
}

void SfxSeq_Update(void) {
    if (!seq.active) return;
    if (seq.timer > 0) { seq.timer--; return; }
    if (seq.idx >= seq.num_steps) { seq.active = 0; return; }
    const UINT8 *p = seq.steps + (seq.idx * 5);
    PlayFx(CHANNEL_1, p[0], p[1], p[2], p[3], p[4]);
    seq.idx++;
    seq.timer = seq.period;
}

// Note helpers: envelope/sweep tuned for simple beeps
// Each step: len, sweep, duty, env, freq
static const UINT8 triad_up[] = {
    4, 0x10, 0xC7, 0xE3, 0xA0, // C
    4, 0x10, 0xC7, 0xE3, 0xA8, // E
    6, 0x10, 0xC7, 0xE3, 0xB0  // G
};
static const UINT8 triad_down[] = {
    4, 0x10, 0xC7, 0xE3, 0xB0, // G
    4, 0x10, 0xC7, 0xE3, 0xA8, // E
    6, 0x10, 0xC7, 0xE3, 0xA0  // C
};
static const UINT8 oneup_seq[] = {
    4, 0x10, 0xC7, 0xE3, 0x9C, // lower C
    4, 0x10, 0xC7, 0xE3, 0xA6, // E
    4, 0x10, 0xC7, 0xE3, 0xB0, // G
    8, 0x10, 0xC7, 0xE3, 0xBC  // C'
};
static const UINT8 bow_seq[] = {
    4, 0x10, 0xC7, 0xE3, 0xA2,
    4, 0x10, 0xC7, 0xE3, 0xAC,
    6, 0x10, 0xC7, 0xE3, 0xB6
};

static void start_seq(const UINT8 *steps, UINT8 count, UINT8 period) {
    seq.steps = steps;
    seq.num_steps = count;
    seq.idx = 0;
    seq.timer = 0;
    seq.period = period;
    seq.active = 1;
}

void SfxSeq_PlayTriadUp(void)     { start_seq(triad_up,    3, 2); }
void SfxSeq_PlayTriadDown(void)   { start_seq(triad_down,  3, 2); }
void SfxSeq_PlayOneUp(void)       { start_seq(oneup_seq,   4, 2); }
void SfxSeq_PlayBow(void)         { start_seq(bow_seq,     3, 2); }


