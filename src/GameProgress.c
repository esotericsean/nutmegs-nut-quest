#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>

#include "GlobalVars.h"

static bool progress_initialized = false;

bool levelCompleted[MAX_LEVEL_TRACKING];
bool levelGoldenCollected[MAX_LEVEL_TRACKING];
UINT8 level_playing = 0;
UINT8 highest_level_completed = 0;

void GameProgress_InitIfNeeded(void) BANKED {
    if(progress_initialized) {
        return;
    }
    for(UINT8 i = 0; i < MAX_LEVEL_TRACKING; ++i) {
        levelCompleted[i] = false;
        levelGoldenCollected[i] = false;
    }
    progress_initialized = true;
}

