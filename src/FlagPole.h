#ifndef FLAGPOLE_H_
#define FLAGPOLE_H_

#include "Banks/SetAutoBank.h"

void FlagPole_Init(void) BANKED;
void FlagPole_Animate (void) BANKED;
void FlagPole_Activate(int x, int y) BANKED;

#endif // FLAGPOLE_H