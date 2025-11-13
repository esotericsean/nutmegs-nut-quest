#ifndef STATELEVEL1B_H
#define STATELEVEL1B_H

#include <gbdk/platform.h>

#define LEVEL1B_ENTRY_DEFAULT      0u
#define LEVEL1B_ENTRY_FROM_SECRET  1u

#define ACORN_META_ASSIGNED        0x80u
#define ACORN_META_LEVEL1C         0x40u
#define ACORN_META_GOLDEN          0x20u
#define ACORN_META_INDEX_MASK      0x1Fu

extern UINT8 level1b_entry_from;

void Level1b_MarkSpawnCollected(UINT8 slot) BANKED;
void Level1b_ReleaseSpawn(UINT8 slot) BANKED;

#endif

