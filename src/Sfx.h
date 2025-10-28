#ifndef SFX_H_
#define SFX_H_

#include <gbdk/platform.h>
#include "Sound.h"

// Optional CBT-FX integration: define USE_CBT_FX to route SFX through CBT-FX
#ifndef USE_CBT_FX
#define USE_CBT_FX 1
#endif

#if defined(USE_CBT_FX)
#include "third_party/cbtfx/include/cbtfx.h"
#include "third_party/cbtfx/include/sfx/SFX_00.h" // coin-like
#include "third_party/cbtfx/include/sfx/SFX_01.h" // jump
// Keep only a minimal set at first to avoid bank0 pressure; reuse SFX_00/01
#endif

// Inline tiny wrappers to avoid bank switches for SFX
static inline void Sfx_Init(void) {
#ifdef USE_CBT_FX
    // No global init required; ensure music driver is present
#endif
}

// 2) Coin (acorn): bright, upward ping (CH1)
static inline void Sfx_Pickup(void) {
#ifdef USE_CBT_FX
    CBTFX_init(SFX_00);
#else
    PlayFx(CHANNEL_1, 10, 0x17, 0x9F, 0xF2, 0xCD, 0x20);
#endif
}
// 4) Stomp: thuddy impact (CH4 low noise)
static inline void Sfx_Stomp(void)  {
#ifdef USE_CBT_FX
    CBTFX_init(SFX_00);
#else
    PlayFx(CHANNEL_4, 6, 0x1F, 0xA4, 0x00, 0xC0, 0xA3);
#endif
}
static inline void Sfx_Hurt(void)   {
#ifdef USE_CBT_FX
    CBTFX_init(SFX_00);
#else
    PlayFx(CHANNEL_4, 10, 0x30, 0xF1, 0x62, 0x80);
#endif
}
// Classic jump (CH1)
static inline void Sfx_Jump(void)   {
#ifdef USE_CBT_FX
    // Temporarily use legacy jump to avoid CBT-FX muting music tracks
    PlayFx(CHANNEL_1, 10, 0x17, 0x9F, 0xF3, 0xC9, 0xC4);
#else
    PlayFx(CHANNEL_1, 10, 0x17, 0x9F, 0xF3, 0xC9, 0xC4);
#endif
}
static inline void Sfx_UIClick(void){
#ifdef USE_CBT_FX
    CBTFX_init(SFX_01);
#else
    PlayFx(CHANNEL_4, 6, 0x20, 0x91, 0x40, 0x80);
#endif
}
// 1) Water splash (CH4): short bright spit; use same for enter/exit
static inline void Sfx_WaterEnter(void){
#ifdef USE_CBT_FX
    CBTFX_init(SFX_01);
#else
    PlayFx(CHANNEL_4, 8, 0x1F, 0x96, 0x00, 0xC0, 0x25);
#endif
}
static inline void Sfx_WaterExit(void) {
#ifdef USE_CBT_FX
    CBTFX_init(SFX_01);
#else
    PlayFx(CHANNEL_4, 8, 0x1F, 0x96, 0x00, 0xC0, 0x25);
#endif
}
// 3) Stroke underwater (CH1): softer, downward sweep "bloink"
static inline void Sfx_WaterStroke(void){
#ifdef USE_CBT_FX
    CBTFX_init(SFX_01);
#else
    PlayFx(CHANNEL_1, 12, 0x3F, 0x5F, 0xC3, 0xC4, 0x90);
#endif
}
static inline void Sfx_BalloonPop(void){
#ifdef USE_CBT_FX
    CBTFX_init(SFX_01);
#else
    PlayFx(CHANNEL_4, 8, 0x20, 0xE1, 0x40, 0x80);
#endif
}
// Pause will use sequencer; keep a tiny click fallback here
static inline void Sfx_PauseOpen(void){
#ifdef USE_CBT_FX
    CBTFX_init(SFX_01);
#else
    PlayFx(CHANNEL_1, 3, 0x10, 0xC7, 0xE3, 0xA0, 0x86);
#endif
}
static inline void Sfx_PauseClose(void){
#ifdef USE_CBT_FX
    CBTFX_init(SFX_01);
#else
    PlayFx(CHANNEL_1, 3, 0x10, 0xC7, 0xE3, 0x9A, 0x86);
#endif
}

#endif


