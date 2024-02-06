#include "Banks/SetAutoBank.h"

#include "..\res\src\cutscene3tiles.h"
#include "..\res\src\cutscene3map.h"

#include "..\res\src\incube8G.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Palette.h"
#include "Sound.h"
#include "Keys.h"

#include "../src/GlobalVars.h"
#include "../src/Font.h"

IMPORT_MAP (cutscene3map);

static UINT16 cutscene3counter;

static UINT8 collision_tiles_cutscene3[] = {0};

void Start_StateCutscene3() {
    SPRITES_8x16;

    //PlayMusic (oaktree, 1);

    InitScrollTiles(0, &cutscene3tiles);
    InitScroll(BANK(cutscene3map), &cutscene3map, collision_tiles_cutscene3, 0);

    SHOW_SPRITES;
	SHOW_BKG;
    cutscene3counter = 0;
}

void Update_StateCutscene3() {

    if (KEY_PRESSED(J_A) || KEY_PRESSED(J_START)) {
        SetState(StateCutsceneGordon);
    }
}