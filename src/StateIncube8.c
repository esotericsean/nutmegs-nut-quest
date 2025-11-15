#include "Banks/SetAutoBank.h"
#include "SGB.h"
//#include <gb/cgb.h>
#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "Sound.h"
#include "Keys.h"
#include "GlobalVars.h"

IMPORT_MAP (gb_border);
IMPORT_MAP (incube8map);

UINT16 incube8counter;

const UINT8 collision_tiles_incube8[] = {0};

BANKREF(pal_games)
const UWORD pal_games[] =       { 0, RGB(30, 16, 16), RGB(28,  3,  4), 0 };
BANKREF(pal_gamespale)
const UWORD pal_gamespale[] =   { 0, RGB(30, 24, 24), RGB(29, 17, 19), 0 };
BANKREF(pal_gamespalest)
const UWORD pal_gamespalest[] = { 0, RGB(30, 28, 28), RGB(30, 25, 26), 0 };

DECLARE_MUSIC (incube8);

#define INCUBE8_AUTO_ADV_FRAMES   150u
#define INCUBE8_FADE_TO_PALE      10u
#define INCUBE8_FADE_TO_FULL      20u

#define INCUBE8_BASE_X            97u
#define INCUBE8_BASE_Y            (84u + 8u)
#define INCUBE8_LETTER_COUNT      5u

typedef enum Incube8PaletteStage {
    PALETTE_STAGE_NONE = 0xFF,
    PALETTE_STAGE_PALEST = 0,
    PALETTE_STAGE_PALE,
    PALETTE_STAGE_FULL
} Incube8PaletteStage;

static Sprite* letters[INCUBE8_LETTER_COUNT];
static Incube8PaletteStage palette_stage = PALETTE_STAGE_NONE;

static void apply_games_palette(Incube8PaletteStage stage) {
    if (palette_stage == stage) {
        return;
    }
    const UWORD* pal_ptr = pal_gamespalest;
    switch(stage) {
        case PALETTE_STAGE_FULL:
            pal_ptr = pal_games;
            break;
        case PALETTE_STAGE_PALE:
            pal_ptr = pal_gamespale;
            break;
        case PALETTE_STAGE_PALEST:
        default:
            pal_ptr = pal_gamespalest;
            break;
    }
    SetPalette(SPRITES_PALETTE, 0, 1, pal_ptr, _current_bank);
    palette_stage = stage;
}

static void go_to_logo(void) {
    incube8counter = 0;
    SetState(StateLogo);
}

void Start_StateIncube8(void) 
{
    SPRITES_8x8;

    PlayMusic(incube8, 1);
    // SfxSeq_Init(); // temporarily disabled to isolate white screen

    for (UINT8 i = 0; i < INCUBE8_LETTER_COUNT; ++i) {
        letters[i] = 0;
    }

    letters[0] = SpriteManagerAdd(SpriteIncube8G, INCUBE8_BASE_X, INCUBE8_BASE_Y);
    letters[1] = SpriteManagerAdd(SpriteIncube8A, INCUBE8_BASE_X + 11u, INCUBE8_BASE_Y);
    letters[2] = SpriteManagerAdd(SpriteIncube8M, INCUBE8_BASE_X + 22u, INCUBE8_BASE_Y);
    letters[3] = SpriteManagerAdd(SpriteIncube8E, INCUBE8_BASE_X + 33u, INCUBE8_BASE_Y);
    letters[4] = SpriteManagerAdd(SpriteIncube8S, INCUBE8_BASE_X + 43u, INCUBE8_BASE_Y);
#ifdef CGB
    for (UINT8 i = 0; i < INCUBE8_LETTER_COUNT; ++i) {
        if (letters[i]) {
            SPRITE_SET_CGB_PALETTE(letters[i], 0);
        }
    }
#endif

    LOAD_SGB_BORDER(gb_border);

    InitScrollTiles(0, &incube8tiles);
    InitScroll(BANK(incube8map), &incube8map, collision_tiles_incube8, 0);

    SHOW_SPRITES;
	SHOW_BKG;
	isPaused = false;
    incube8counter = 0;
    palette_stage = PALETTE_STAGE_PALEST;
    apply_games_palette(PALETTE_STAGE_PALEST);
}

void Update_StateIncube8(void) 
{
    if (incube8counter == INCUBE8_FADE_TO_PALE) {
        apply_games_palette(PALETTE_STAGE_PALE);
    } else if (incube8counter == INCUBE8_FADE_TO_FULL) {
        apply_games_palette(PALETTE_STAGE_FULL);
    }

    if (KEY_TICKED(J_A) || KEY_TICKED(J_START)) {
        go_to_logo();
        return;
    }

    if (incube8counter >= INCUBE8_AUTO_ADV_FRAMES) {
        go_to_logo();
        return;
    }

    incube8counter++;
}