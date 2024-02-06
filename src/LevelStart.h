#ifndef LEVEL_START_H_
#define LEVEL_START_H_

#include "Banks/SetAutoBank.h"
#include "GlobalVars.h"

void LevelStart_Init(UINT8 posx, UINT8 posy) BANKED;
void LevelStart_Update (void) BANKED;

#endif // LEVEL_START_H