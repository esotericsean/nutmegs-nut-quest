#ifndef CBTFX_H_INCLUDE
#define CBTFX_H_INCLUDE

#include <gbdk/platform.h>
#include "BankManager.h"

void CBTFX_update(void) NONBANKED;
void CBTFX_init(const unsigned char * SFX) BANKED;

// 0 = Panning won't be reset after an SFX, 1 = Panning will be set to 0XFF after an SFX plays.
#define MONO_MUSIC 1

#endif
