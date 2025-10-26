#ifndef SFXCHAIN_H_
#define SFXCHAIN_H_

#include <gbdk/platform.h>

// Trigger a short multi-note SFX chain handled in main loop
// which: 1=pauseUp, 2=pauseDown, 3=oneUp, 4=bow
// period: frames per note step (e.g., 2)
void SfxChain_Start(UINT8 which, UINT8 period);

#endif


