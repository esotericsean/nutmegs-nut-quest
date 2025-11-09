#ifndef SPRITE_NUTMEG_H__
#define SPRITE_NUTMEG_H__

#include <gbdk/platform.h>
#include "SpriteManager.h"
#include "Banks/SetAutoBank.h"
#include "GlobalVars.h"

void nutmeg_setupNextLife (void) BANKED;
void nutmeg_SetupGame(void) BANKED;
void nutmeg_hit(void) BANKED;
void nutmeg_Animate(void) BANKED;
bool nutmeg_isInsideXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) BANKED;
void nutmeg_allow_next_quickdeath(void) BANKED;
void nutmeg_SetIdlePose(void) BANKED;

Sprite *nutmeg_Add (uint16_t x, uint16_t y) BANKED;


#endif