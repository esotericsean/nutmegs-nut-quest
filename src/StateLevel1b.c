#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Palette.h"

#include "GlobalVars.h"
#include "FlagPole.h"
#include "Water.h"
#include "Hud.h"
#include "LevelStart.h"
#include "SpriteNutmeg.h"
#include "LevelActors.h"

// Map resource
IMPORT_MAP (level1bmap);

static const UINT8 collision_tiles_level1b[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
static const UINT8 collision_tiles_down_level1b[] = {29,30,31,32,0};

DECLARE_MUSIC (quickstart);
DECLARE_MUSIC (mushrooms);

extern Sprite * spr_nutmeg;

static const LevelT levelInfo = {
    .isWaterLevel = false,
    .isSpikeLevel = false,
    .iceTileMin = NO_ICE_TILES,
    .iceTileMax = NO_ICE_TILES,
    .orientation = horizontal,
    .hasTimer = true,
    .timer = 300,
    .timerclock = 0,
};

// No actors yet; pass NULL to Actors_Init
static ActorsRuntime gActors;

static UINT8 win_warmup;

void Start_StateLevel1b(void)
{
    level = levelInfo;
    levelStartCounter = 0;
    cutscenemode = disabled; // no intro walk in sub-room
    levelEndCounter = 0;

    SPRITES_8x16;

    // Keep whatever music is already playing from 1-1

    // Spawn Nutmeg exiting the door, slightly to the right and grounded
    scroll_target = nutmeg_Add(32, (15 * 8) - 17);
    spr_nutmeg->y -= 2;
    nutmeg.offsetY = 0;
    nutmeg.speedY = 0;

    InitScrollTiles(0, &level1tiles);
    // Load the intended 1-1b map
    InitScroll(BANK(level1bmap), &level1bmap, collision_tiles_level1b, collision_tiles_down_level1b);
    Hud_Init();
    FlagPole_Init();
    // No LevelStart banner in sub-room
    VBK_REG = 0; // ensure subsequent VRAM writes go to tile data bank 0

    // No actor spawner in 1-1b during stabilization

    SHOW_SPRITES;
    SHOW_BKG;
    // Start with window off for first frames to avoid covering BG
    LCDC_REG &= (UINT8)~LCDCF_WINON;
    WY_REG = 144; // place window off-screen
    win_warmup = 2; // re-enable after a couple vblanks
}

void Update_StateLevel1b(void)
{
    Hud_Update();
    if (win_warmup) {
        win_warmup--;
        if (!win_warmup) {
            WY_REG = (INT8)(144 - 8);
            LCDC_REG |= LCDCF_WINON;
        }
    }
    Water_Animate();
    FlagPole_Animate();

    // Spawn any actors whose X is within view + some ahead buffer
    // Actors_Update(&gActors, spr_nutmeg->x, 96);

    // No intro cutscene logic in sub-room

    if (levelbeat == true) {
        cutscenemode = enabled;
        cutscenewalkright = true;
        cutscenewalkleft = false;
        if (levelEndCounter >= 100) {
            SetState(StateOverworld);
        }
        if (levelEndCounter < 250) levelEndCounter++;
    }

    // Trigger flagpole when Nutmeg overlaps the pole column after intro walk
    if (!nutmeg.isDying && (levelbeat == false) && (cutscenemode == disabled)) {
        UINT16 px = spr_nutmeg->x;
        UINT16 py = spr_nutmeg->y;
        UINT8 tx = (UINT8)(px >> 3);
        UINT8 ty = (UINT8)(py >> 3);
        if (ty == 0) ty = 1; // guard underflow for sampling above

        const UINT8 POLE1 = 0x21; // pole body
        const UINT8 POLE2 = 0x22; // pole cap

        UINT8 t  = GetScrollTile(tx,     ty);
        UINT8 tr = GetScrollTile((UINT8)(tx + 1), ty);
        if (t == POLE1 || t == POLE2 || tr == POLE1 || tr == POLE2) {
            UINT8 poleX = (t == POLE1 || t == POLE2) ? tx : (UINT8)(tx + 1);
            UINT8 poleY = ty;
            while ((UINT8)(poleY + 1) < 32) {
                UINT8 below = GetScrollTile(poleX, (UINT8)(poleY + 1));
                if (below == POLE1 || below == POLE2) poleY++;
                else break;
            }
            FlagPole_Activate(poleX, poleY);
            levelbeat = true;
            levelEndCounter = 0;
            cutscenemode = enabled;
            cutscenewalkright = true;
        }
    }
}


