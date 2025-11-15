#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>
#include "SpriteManager.h"
#include "GlobalVars.h"

void Start_SpriteSmallGoldenAcorn(void) {
    THIS->lim_x = 500;
    THIS->lim_y = 500;
    THIS->custom_data[0] = 0;
}

void Update_SpriteSmallGoldenAcorn(void) {
    if (THIS->custom_data[0] == 1) {
        THIS->x = (12u * 8u) - 1;
        THIS->y = (0u * 8u);
    } else {
        THIS->x = 65527;
        THIS->y = 240;
    }
}

void Destroy_SpriteSmallGoldenAcorn(void) {
}


