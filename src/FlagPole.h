#ifndef FLAGPOLE_H_
#define FLAGPOLE_H_

#include "Banks/SetAutoBank.h"

void FlagPole_Init(void) BANKED;
void FlagPole_Animate (void) BANKED;
// x = tile x of bottom of flagpole
// y = tile y of bottom of flagpole
void FlagPole_Activate(int tilex, int tiley) BANKED;


#endif // FLAGPOLE_H