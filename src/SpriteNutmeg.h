#ifndef SPRITE_NUTMEG_H__
#define SPRITE_NUTMEG_H__

#include "Banks/SetAutoBank.h"

void nutmeg_setupNewLife (void) BANKED;
void nutmeg_SetupGame(void) BANKED;
void nutmeg_hit(void) BANKED;
void nutmeg_Animate(void) BANKED;
bool nutmeg_isInsideXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) BANKED;
#endif