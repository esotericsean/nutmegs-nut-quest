#ifndef SFX_H_
#define SFX_H_

#include <gbdk/platform.h>
#include "Sound.h"

// Inline tiny wrappers to avoid bank switches for SFX
static inline void Sfx_Init(void) {}

// 2) Coin (acorn): bright, upward ping (CH1)
static inline void Sfx_Pickup(void) { PlayFx(CHANNEL_1, 10, 0x17, 0x9F, 0xF2, 0xCD, 0x20); }
// 4) Stomp: thuddy impact (CH4 low noise)
static inline void Sfx_Stomp(void)  { PlayFx(CHANNEL_4, 6, 0x1F, 0xA4, 0x00, 0xC0, 0xA3); }
static inline void Sfx_Hurt(void)   { PlayFx(CHANNEL_4, 10, 0x30, 0xF1, 0x62, 0x80); }
// Classic jump (CH1)
static inline void Sfx_Jump(void)   { PlayFx(CHANNEL_1, 10, 0x17, 0x9F, 0xF3, 0xC9, 0xC4); }
static inline void Sfx_UIClick(void){ PlayFx(CHANNEL_4, 6, 0x20, 0x91, 0x40, 0x80); }
// 1) Water splash (CH4): short bright spit; use same for enter/exit
static inline void Sfx_WaterEnter(void){ PlayFx(CHANNEL_4, 8, 0x1F, 0x96, 0x00, 0xC0, 0x25); }
static inline void Sfx_WaterExit(void) { PlayFx(CHANNEL_4, 8, 0x1F, 0x96, 0x00, 0xC0, 0x25); }
// 3) Stroke underwater (CH1): softer, downward sweep "bloink"
static inline void Sfx_WaterStroke(void){ PlayFx(CHANNEL_1, 12, 0x3F, 0x5F, 0xC3, 0xC4, 0x90); }
static inline void Sfx_BalloonPop(void){ PlayFx(CHANNEL_4, 8, 0x20, 0xE1, 0x40, 0x80); }
// Pause will use sequencer; keep a tiny click fallback here
static inline void Sfx_PauseOpen(void){ /* handled by sequencer from caller if desired */ PlayFx(CHANNEL_1, 3, 0x10, 0xC7, 0xE3, 0xA0, 0x86); }
static inline void Sfx_PauseClose(void){ PlayFx(CHANNEL_1, 3, 0x10, 0xC7, 0xE3, 0x9A, 0x86); }

#endif


