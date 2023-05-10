#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Palette.h"
#include "Sound.h"
#include "Keys.h"

#include "../src/GlobalVars.h"
//#include "../src/Font.h"

IMPORT_MAP (cutscene2map);

const UINT8 collision_tiles_cutscene2[] = {0};

void Start_StateCutscene2() {
    SPRITES_8x16;

    InitScrollTiles(0, &cutscene2tiles);
    InitScroll(BANK(cutscene2map), &cutscene2map, collision_tiles_cutscene2, 0);

    SHOW_SPRITES;
	SHOW_BKG;
    
    SpriteManagerAdd (SpriteShockline1, 30, 10);
    SpriteManagerAdd (SpriteShockline2, 30, 30);
    SpriteManagerAdd (SpriteShockline3, 30, 50);
}

void Update_StateCutscene2() {
    if (KEY_PRESSED(J_A) || KEY_PRESSED(J_START)) { SetState(StateCutscene3); }
}