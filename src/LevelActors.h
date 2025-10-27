#ifndef LEVELACTORS_H_
#define LEVELACTORS_H_

#include <gbdk/platform.h>
#include "SpriteManager.h"

// Define one spawnable actor at a given map tile coordinate (tx, ty)
// The array MUST be sorted by tx ascending (left to right) for O(1) forward spawning.
typedef struct {
    UINT8 tx;        // tile X (map coordinate)
    UINT8 ty;        // tile Y (map coordinate)
    UINT8 type;      // sprite type enum used by SpriteManagerAdd
    UINT8 cd0, cd1, cd2, cd3; // optional custom_data bytes
} ActorDef;

// Runtime state that walks forward through the list and spawns actors once.
typedef struct {
    const ActorDef* defs;
    UINT8 count;
    UINT8 index;      // next actor to consider (0..count)
} ActorsRuntime;

// Initialize forward-only spawner.
void Actors_Init(ActorsRuntime* s, const ActorDef* defs, UINT8 count);

// Spawn any actors whose X threshold is within view.
// playerX is Nutmeg's current pixel X; actors spawn when (tx<<3) <= playerX + spawnAheadPx.
void Actors_Update(ActorsRuntime* s, UINT16 playerX, UINT8 spawnAheadPx);

#endif


