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
// BANKED: Sfx.c lives in an auto-assigned bank to keep bank 0 free
static inline void Sfx_Init(void) {}
void Sfx_Pickup(void) BANKED;
void Sfx_OneUp(void) BANKED;
void Sfx_BowPickup(void) BANKED;
void Sfx_Stomp(void) BANKED;
void Sfx_MegaStomp(void) BANKED;
void Sfx_Hurt(void) BANKED;
void Sfx_Jump(void) BANKED;
void Sfx_Land(void) BANKED;
void Sfx_UIClick(void) BANKED;
void Sfx_WaterEnter(void) BANKED;
void Sfx_WaterExit(void) BANKED;
void Sfx_WaterStroke(void) BANKED;
void Sfx_BalloonPop(void) BANKED;
void Sfx_MushroomBounce(void) BANKED;
void Sfx_GemBounce(void) BANKED;
void Sfx_Lightning(void) BANKED;
void Sfx_DoorEnter(void) BANKED;
void Sfx_PauseOpen(void) BANKED;
void Sfx_PauseClose(void) BANKED;
#endif


