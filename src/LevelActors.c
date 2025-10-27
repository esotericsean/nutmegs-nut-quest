#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>
#include "LevelActors.h"

void Actors_Init(ActorsRuntime* s, const ActorDef* defs, UINT8 count) {
    s->defs = defs;
    s->count = count;
    s->index = 0;
}

void Actors_Update(ActorsRuntime* s, UINT16 playerX, UINT8 spawnAheadPx) {
    if (!s->defs) return;
    UINT16 threshold = playerX + spawnAheadPx;
    while (s->index < s->count) {
        const ActorDef* a = &s->defs[s->index];
        UINT16 ax = ((UINT16)a->tx) << 3; // tile->px
        if (ax > threshold) break; // not yet
        // Spawn once; never revisit
        Sprite* spr = SpriteManagerAdd(a->type, ax, ((UINT16)a->ty) << 3);
        spr->lim_x = 9999; spr->lim_y = 999;
        spr->custom_data[0] = a->cd0;
        spr->custom_data[1] = a->cd1;
        spr->custom_data[2] = a->cd2;
        spr->custom_data[3] = a->cd3;
        s->index++;
    }
}


