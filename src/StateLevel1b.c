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
#include "Sfx.h"
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
            case SpriteAcorn: {
                UINT8 meta = (UINT8)(ACORN_META_ASSIGNED | (i & ACORN_META_INDEX_MASK));
                spawned->custom_data[3] = meta;
                break;
            }
            case EnemyBunny:
                spawned->custom_data[2] = i;
                break;
            case EnemyButterfly:
                spawned->custom_data[0] = i;
                break;
            case EnemyBeetle:
                spawned->custom_data[2] = i;
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
static UINT8 flagpole_tile_x = 0xFF;
static UINT8 flagpole_tile_y = 0;

#define FLAGPOLE_TILE_BODY (0x21)
#define FLAGPOLE_TILE_CAP  (0x22)

static void Level1b_InitFlagpoleSite(void) {
    UINT8 tiles_w = 0;
    UINT8 tiles_h = 0;
    UINT16 fx = 0;
    UINT16 fy = 0;
    UINT8 search_w = 40;
    UINT8 start_x;
    UINT8 found;

    GetMapSize(BANK(level1bmap), &level1bmap, &tiles_w, &tiles_h);
    if (tiles_w == 0 || tiles_h == 0) {
        flagpole_tile_x = 0xFF;
        return;
    }

    start_x = (tiles_w > search_w) ? (UINT8)(tiles_w - search_w) : 0;
    found = ScrollFindTile(BANK(level1bmap), &level1bmap, FLAGPOLE_TILE_BODY,
        start_x, 0, search_w, tiles_h, &fx, &fy);
    if (!found) {
        found = ScrollFindTile(BANK(level1bmap), &level1bmap, FLAGPOLE_TILE_CAP,
            start_x, 0, search_w, tiles_h, &fx, &fy);
    }
    if (!found) {
        flagpole_tile_x = 0xFF;
        return;
    }

    flagpole_tile_x = (UINT8)fx;
    flagpole_tile_y = (UINT8)fy;
    while ((UINT8)(flagpole_tile_y + 1) < tiles_h) {
        UINT8 below = GetScrollTile(flagpole_tile_x, (UINT8)(flagpole_tile_y + 1));
        if (below == FLAGPOLE_TILE_BODY || below == FLAGPOLE_TILE_CAP) {
            flagpole_tile_y++;
        } else {
            break;
        }
    }
}

static void Level1b_TryActivateFlagpole(void) {
    UINT16 px;
    UINT16 pole_px;

    if (flagpole_tile_x == 0xFF) {
        return;
    }

    px = spr_nutmeg->x;
    pole_px = ((UINT16)flagpole_tile_x) << 3;
    // Activate when Nutmeg reaches the pole column, including when jumping over it.
    if (px + 12 < pole_px || px > pole_px + 16) {
        return;
    }

    FlagPole_Activate(flagpole_tile_x, flagpole_tile_y);
    levelbeat = true;
    levelEndCounter = 0;
    cutscenemode = enabled;
    cutscenewalkright = true;
}

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
    Level1b_InitFlagpoleSite();
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
                Sfx_DoorEnter();
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

    if (!nutmeg.isDying && (levelbeat == false) && (cutscenemode == disabled)) {
        Level1b_TryActivateFlagpole();
    }
}


