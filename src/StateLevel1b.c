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
#include "StateLevel1b.h"
#include "StateLevel1c.h"

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

#define ARRAY_LEN(arr) ((UINT8)(sizeof(arr) / sizeof((arr)[0])))

typedef struct {
    UINT16 px;
    UINT16 py;
    UINT8 type;
} Level1bSpawn;

static const Level1bSpawn level1bSpawns[] = {
    {15u * 8u, 12u * 8u, SpriteAcorn},
    {23u * 8u, 12u * 8u, SpriteAcorn},
    {31u * 8u, 12u * 8u, SpriteAcorn},
    {39u * 8u, 12u * 8u, SpriteAcorn},
    {60u * 8u, 13u * 8u, EnemyBunny},
    {107u * 8u, 8u * 8u, EnemyButterfly},
    {110u * 8u, 13u * 8u, EnemyBunny},
    {117u * 8u, 11u * 8u, SpriteAcorn},
    {117u * 8u, 9u * 8u, SpriteAcorn},
    {117u * 8u, 7u * 8u, SpriteAcorn},
    {117u * 8u, 5u * 8u, SpriteAcorn},
    {117u * 8u, 3u * 8u, SpriteAcorn},
    {123u * 8u, 15u * 8u, EnemyFish},
    {154u * 8u, 10u * 8u, SpriteAcorn},
    {157u * 8u, 8u * 8u, SpriteAcorn},
    {159u * 8u, 9u * 8u, SpriteAcorn},
    {164u * 8u, 7u * 8u, SpriteAcorn},
    {167u * 8u, 5u * 8u, SpriteAcorn},
    {169u * 8u, 6u * 8u, SpriteAcorn},
    {181u * 8u, 7u * 8u, SpriteAcorn},
    {191u * 8u, 4u * 8u, SpriteAcorn},
    {201u * 8u, 6u * 8u, SpriteAcorn},
    {219u * 8u, 14u * 8u, EnemyBunny},
    {234u * 8u, 11u * 8u, EnemyButterfly}
};

typedef enum {
    SPAWN_STATUS_AVAILABLE = 0u,
    SPAWN_STATUS_ACTIVE = 1u,
    SPAWN_STATUS_COLLECTED = 2u
} SpawnStatus;

UINT8 level1b_entry_from = LEVEL1B_ENTRY_DEFAULT;
static SpawnStatus level1bSpawnStatus[ARRAY_LEN(level1bSpawns)];

void Level1b_MarkSpawnCollected(UINT8 slot) BANKED {
    if (slot < ARRAY_LEN(level1bSpawns)) {
        level1bSpawnStatus[slot] = SPAWN_STATUS_COLLECTED;
    }
}

void Level1b_ReleaseSpawn(UINT8 slot) BANKED {
    if (slot < ARRAY_LEN(level1bSpawns) && level1bSpawnStatus[slot] == SPAWN_STATUS_ACTIVE) {
        level1bSpawnStatus[slot] = SPAWN_STATUS_AVAILABLE;
    }
}

static void Level1b_ResetActiveSpawns(void) {
    for (UINT8 i = 0; i < ARRAY_LEN(level1bSpawns); ++i) {
        if (level1bSpawnStatus[i] == SPAWN_STATUS_ACTIVE) {
            level1bSpawnStatus[i] = SPAWN_STATUS_AVAILABLE;
        }
    }
}

static void Level1b_ResetAllSpawns(void) {
    for (UINT8 i = 0; i < ARRAY_LEN(level1bSpawns); ++i) {
        level1bSpawnStatus[i] = SPAWN_STATUS_AVAILABLE;
    }
}

static void Level1b_SpawnPending(void) {
    UINT16 threshold = (UINT16)(spr_nutmeg->x + 96u);
    for (UINT8 i = 0; i < ARRAY_LEN(level1bSpawns); ++i) {
        if (level1bSpawnStatus[i] != SPAWN_STATUS_AVAILABLE) {
            continue;
        }
        const Level1bSpawn* slot = &level1bSpawns[i];
        if (slot->px > threshold) {
            continue;
        }
        Sprite* spawned = SpriteManagerAdd(slot->type, slot->px, slot->py);
        spawned->lim_x = 9999;
        spawned->lim_y = 999;
        switch (slot->type) {
            case SpriteAcorn:
                spawned->custom_data[3] = i;
                break;
            case EnemyBunny:
                spawned->custom_data[2] = i;
                break;
            case EnemyButterfly:
                spawned->custom_data[0] = i;
                break;
            case EnemyFish:
                spawned->custom_data[0] = i;
                break;
            default:
                break;
        }
        level1bSpawnStatus[i] = SPAWN_STATUS_ACTIVE;
    }
}


static UINT8 win_warmup;

void Start_StateLevel1b(void)
{
    level = levelInfo;
    levelStartCounter = 0;
    cutscenemode = disabled; // no intro walk in sub-room
    levelEndCounter = 0;

    SPRITES_8x16;

    // Keep whatever music is already playing from 1-1

    if (level1b_entry_from == LEVEL1B_ENTRY_FROM_SECRET) {
        Level1b_ResetActiveSpawns();
        // Spawn returning from the secret room door (tiles 112-113, rows 2-4)
        scroll_target = nutmeg_Add((112u * 8u) + 8u, (4u * 8u) - 17u);
        spr_nutmeg->y -= 2;
    } else {
        Level1c_Reset();
        Level1b_ResetAllSpawns();
        // Spawn Nutmeg exiting the 1-1 door, slightly to the right and grounded
        scroll_target = nutmeg_Add(32, (15 * 8) - 17);
        spr_nutmeg->y -= 2;
    }
    level1b_entry_from = LEVEL1B_ENTRY_DEFAULT;
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
    Level1b_SpawnPending();

    // No intro cutscene logic in sub-room

    // Secret two-way door into Level 1-1c located around tiles 112-113
    if (!nutmeg.isDying && (cutscenemode == disabled)) {
        UINT16 px = spr_nutmeg->x;
        UINT16 py = spr_nutmeg->y;
        UINT8 tx = (UINT8)(px >> 3);
        UINT8 tyFeet = (UINT8)((py + 8) >> 3);
        if (tyFeet > 0) {
            UINT8 tyMid = (UINT8)(tyFeet - 1);
            UINT8 tBelowL = GetScrollTile(tx, tyFeet);
            UINT8 tBelowR = GetScrollTile((UINT8)(tx + 1), tyFeet);
            UINT8 tMidL = GetScrollTile(tx, tyMid);
            UINT8 tMidR = GetScrollTile((UINT8)(tx + 1), tyMid);
            const UINT8 DOOR_MIN = 115u;
            const UINT8 DOOR_MAX = 118u;
            bool onSecretDoor =
                (tx >= 112u && tx <= 113u) &&
                ((tBelowL >= DOOR_MIN && tBelowL <= DOOR_MAX) ||
                 (tBelowR >= DOOR_MIN && tBelowR <= DOOR_MAX) ||
                 (tMidL   >= DOOR_MIN && tMidL   <= DOOR_MAX) ||
                 (tMidR   >= DOOR_MIN && tMidR   <= DOOR_MAX));
            if (onSecretDoor && KEY_TICKED(J_UP)) {
                extern UINT8 stop_music_on_new_state;
                stop_music_on_new_state = 0;
                SetState(StateLevel1c);
                return;
            }
        }
    }

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


