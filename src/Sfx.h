#ifndef SFX_H_
#define SFX_H_

#include <gbdk/platform.h>
#include "Sound.h"
#ifdef USE_CBT_FX
// Disable legacy PlayFx calls project-wide when CBT-FX is enabled
#undef PlayFx
#define PlayFx(...) do {} while(0)
#endif

// SFX API (implemented in Sfx.c)
static inline void Sfx_Init(void) {}
void Sfx_Pickup(void);
void Sfx_Stomp(void);
void Sfx_Hurt(void);
void Sfx_Jump(void);
void Sfx_UIClick(void);
void Sfx_WaterEnter(void);
void Sfx_WaterExit(void);
void Sfx_WaterStroke(void);
void Sfx_BalloonPop(void);
void Sfx_PauseOpen(void);
void Sfx_PauseClose(void);
#endif


