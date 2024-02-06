#ifndef HUD_H_
#define HUD_H_

#include "Banks/SetAutoBank.h"
#include "GlobalVars.h"

void Hud_Init(bool isBoss) BANKED;
void Hud_Update (void) BANKED;

#endif // HUD_H