#include "Banks/SetAutoBank.h"

#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Palette.h"

#include "GlobalVars.h"
#include "Hud.h"
#include "SpriteNutmeg.h"
#include "Sfx.h"
#include "StateLevel1b.h"
#include "StateLevel1c.h"

// Map resource
IMPORT_MAP (level1cmap);

static const UINT8 collision_tiles_level1c[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
static const UINT8 collision_tiles_down_level1c[] = {29,30,31,32,0};

extern Sprite * spr_nutmeg;
extern UINT8 level1b_entry_from;

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
    UINT8 flags;
} Level1cSpawn;

enum {
    SPAWN_FLAG_GOLDEN = 1u << 0
};

typedef enum {
    SPAWN_STATUS_AVAILABLE = 0u,
    SPAWN_STATUS_ACTIVE = 1u,
    SPAWN_STATUS_COLLECTED = 2u
} SpawnStatus;

static const Level1cSpawn level1cSpawns[] = {
    {5u * 8u, 4u * 8u, SpriteAcorn, 0u},
    {11u * 8u, 8u * 8u, SpriteAcorn, 0u},
    {15u * 8u, 2u * 8u, SpriteAcorn, SPAWN_FLAG_GOLDEN}
};

static SpawnStatus level1cSpawnStatus[ARRAY_LEN(level1cSpawns)];

void Level1c_MarkSpawnCollected(UINT8 slot) BANKED {
    if (slot < ARRAY_LEN(level1cSpawns)) {
        level1cSpawnStatus[slot] = SPAWN_STATUS_COLLECTED;
    }
}

void Level1c_Reset(void) BANKED {
    for (UINT8 i = 0; i < ARRAY_LEN(level1cSpawns); ++i) {
        level1cSpawnStatus[i] = SPAWN_STATUS_AVAILABLE;
    }
}

static void Level1c_ResetActiveSpawns(void) {
    for (UINT8 i = 0; i < ARRAY_LEN(level1cSpawns); ++i) {
        if (level1cSpawnStatus[i] == SPAWN_STATUS_ACTIVE) {
            level1cSpawnStatus[i] = SPAWN_STATUS_AVAILABLE;
        }
    }
}

static void Level1c_SpawnPending(void) {
    UINT16 threshold = (UINT16)(spr_nutmeg->x + 96u);
    for (UINT8 i = 0; i < ARRAY_LEN(level1cSpawns); ++i) {
        if (level1cSpawnStatus[i] != SPAWN_STATUS_AVAILABLE) {
            continue;
        }
        const Level1cSpawn* slot = &level1cSpawns[i];
        if (slot->px > threshold) {
            continue;
        }
        Sprite* spawned = SpriteManagerAdd(slot->type, slot->px, slot->py);
        spawned->lim_x = 9999;
        spawned->lim_y = 999;
        UINT8 meta = (UINT8)(ACORN_META_ASSIGNED | ACORN_META_LEVEL1C | (i & ACORN_META_INDEX_MASK));
        if (slot->flags & SPAWN_FLAG_GOLDEN) {
            meta |= ACORN_META_GOLDEN;
#ifdef CGB
            SPRITE_SET_CGB_PALETTE(spawned, 0);
#endif
        }
        spawned->custom_data[3] = meta;
        level1cSpawnStatus[i] = SPAWN_STATUS_ACTIVE;
    }
}

static UINT8 win_warmup;

void Start_StateLevel1c(void)
{
    level = levelInfo;
    levelStartCounter = 0;
    cutscenemode = disabled;
    levelEndCounter = 0;

    SPRITES_8x16;

    Level1c_ResetActiveSpawns();

    // Entry from Level 1-1b two-way door (tiles 3-4, rows 11-13)
    scroll_target = nutmeg_Add((3u * 8u) + 8u, (13u * 8u) - 17u);
    spr_nutmeg->y -= 2;
    nutmeg.offsetY = 0;
    nutmeg.speedY = 0;

    InitScrollTiles(0, &level1tiles);
    InitScroll(BANK(level1cmap), &level1cmap, collision_tiles_level1c, collision_tiles_down_level1c);
    Hud_Init();

    SHOW_SPRITES;
    SHOW_BKG;
    LCDC_REG &= (UINT8)~LCDCF_WINON;
    WY_REG = 144;
    win_warmup = 2;
}

void Update_StateLevel1c(void)
{
    Hud_Update();
    if (win_warmup) {
        win_warmup--;
        if (!win_warmup) {
            WY_REG = (INT8)(144 - 8);
            LCDC_REG |= LCDCF_WINON;
        }
    }

    Level1c_SpawnPending();

    // Handle returning to Level 1-1b
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
            bool onDoor =
                ((tBelowL >= DOOR_MIN && tBelowL <= DOOR_MAX) ||
                 (tBelowR >= DOOR_MIN && tBelowR <= DOOR_MAX) ||
                 (tMidL   >= DOOR_MIN && tMidL   <= DOOR_MAX) ||
                 (tMidR   >= DOOR_MIN && tMidR   <= DOOR_MAX));
            if (onDoor && KEY_TICKED(J_UP)) {
                extern UINT8 stop_music_on_new_state;
                stop_music_on_new_state = 0;
                Sfx_DoorEnter();
                level1b_entry_from = LEVEL1B_ENTRY_FROM_SECRET;
                SetState(StateLevel1b);
                return;
            }
        }
    }
}


