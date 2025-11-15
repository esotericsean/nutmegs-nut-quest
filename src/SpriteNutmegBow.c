#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "../src/GlobalVars.h"

extern Sprite * spr_nutmeg;
Sprite *spr_nutmegbow = 0;

#define ARRAY_LEN(A) (sizeof(A) / sizeof((A)[0]))

static const UINT8 anim_nutmegbow_static[] = {1, 0};

typedef struct {
    const INT8* frame_x;
    const INT8* frame_y;
    UINT8 frame_count;
    UINT8 mirror;
    const INT8* bob_offsets;
    UINT8 bob_length;
    UINT8 bob_speed;
} BowPlacementConfig;

static const INT8 bow_idle_bob[] = {0};
static const INT8 bow_walk_bob[] = {0};
static const INT8 bow_glide_bob[] = {0};

static const INT8 bow_idle_x_r[] = { 0, 0, 0, 0 };
static const INT8 bow_idle_y_r[] = { -17, -16, -16, -17 };
static const INT8 bow_idle_x_l[] = { 0, 0, 0, 0 };
static const INT8 bow_idle_y_l[] = { -17, -16, -16, -17 };

static const INT8 bow_walk_x_r[] = { 5, 4, 4, 4 };
static const INT8 bow_walk_y_r[] = { -15, -14, -14, -15 };
static const INT8 bow_walk_x_l[] = { -5, -4, -4, -4 };
static const INT8 bow_walk_y_l[] = { -15, -14, -14, -15 };

static const INT8 bow_jump_x_r[] = { 0 };
static const INT8 bow_jump_y_r[] = { -19 };
static const INT8 bow_jump_x_l[] = { 0 };
static const INT8 bow_jump_y_l[] = { -19 };

static const INT8 bow_fall_x_r[] = { 0 };
static const INT8 bow_fall_y_r[] = { -18 };
static const INT8 bow_fall_x_l[] = { 0 };
static const INT8 bow_fall_y_l[] = { -18 };

static const INT8 bow_drop_x_r[] = { 0 };
static const INT8 bow_drop_y_r[] = { -16 };
static const INT8 bow_drop_x_l[] = { 0 };
static const INT8 bow_drop_y_l[] = { -16 };

static const INT8 bow_glide_x_r[] = { -3 };
static const INT8 bow_glide_y_r[] = { -18 };
static const INT8 bow_glide_x_l[] = { 3 };
static const INT8 bow_glide_y_l[] = { -18 };

static const INT8 bow_swim_x_r[] = { 4 };
static const INT8 bow_swim_y_r[] = { -14 };
static const INT8 bow_swim_x_l[] = { -4 };
static const INT8 bow_swim_y_l[] = { -14 };

static const BowPlacementConfig bow_placements[] = {
    // 0 = idle right
    { bow_idle_x_r, bow_idle_y_r, ARRAY_LEN(bow_idle_x_r), NO_MIRROR, bow_idle_bob, ARRAY_LEN(bow_idle_bob), 24 },
    // 1 = idle left
    { bow_idle_x_l, bow_idle_y_l, ARRAY_LEN(bow_idle_x_l), V_MIRROR, bow_idle_bob, ARRAY_LEN(bow_idle_bob), 24 },
    // 2 = walk right
    { bow_walk_x_r, bow_walk_y_r, ARRAY_LEN(bow_walk_x_r), NO_MIRROR, bow_walk_bob, ARRAY_LEN(bow_walk_bob), 12 },
    // 3 = walk left
    { bow_walk_x_l, bow_walk_y_l, ARRAY_LEN(bow_walk_x_l), V_MIRROR, bow_walk_bob, ARRAY_LEN(bow_walk_bob), 12 },
    // 4 = jump right
    { bow_jump_x_r, bow_jump_y_r, ARRAY_LEN(bow_jump_x_r), NO_MIRROR, NULL, 0, 0 },
    // 5 = jump left
    { bow_jump_x_l, bow_jump_y_l, ARRAY_LEN(bow_jump_x_l), V_MIRROR, NULL, 0, 0 },
    // 6 = fall right
    { bow_fall_x_r, bow_fall_y_r, ARRAY_LEN(bow_fall_x_r), NO_MIRROR, NULL, 0, 0 },
    // 7 = fall left
    { bow_fall_x_l, bow_fall_y_l, ARRAY_LEN(bow_fall_x_l), V_MIRROR, NULL, 0, 0 },
    // 8 = drop right (handled in lost branch)
    { bow_drop_x_r, bow_drop_y_r, ARRAY_LEN(bow_drop_x_r), NO_MIRROR, NULL, 0, 0 },
    // 9 = drop left
    { bow_drop_x_l, bow_drop_y_l, ARRAY_LEN(bow_drop_x_l), V_MIRROR, NULL, 0, 0 },
    // 10 = disabled/hidden
    { NULL, NULL, 0, NO_MIRROR, NULL, 0, 0 },
    // 11 = glide right
    { bow_glide_x_r, bow_glide_y_r, ARRAY_LEN(bow_glide_x_r), NO_MIRROR, bow_glide_bob, ARRAY_LEN(bow_glide_bob), 16 },
    // 12 = glide left
    { bow_glide_x_l, bow_glide_y_l, ARRAY_LEN(bow_glide_x_l), V_MIRROR, bow_glide_bob, ARRAY_LEN(bow_glide_bob), 16 },
};

static UINT8 bow_prev_anim = 0xFF;
static UINT8 bow_bob_index = 0;
static UINT8 bow_bob_timer = 0;

// 0 = idle (5)
// 1 = walking (15)
// 2 = jump/fall (1)
// 3 = static (1)


/* * * * * * * * * * * * */
/*        bowanim        */
/* * * * * * * * * * * * */

// 0 = idle_right (NO_MIRROR)
// 1 = idle_left (V_MIRROR)
// 2 = walk_right (NO_MIRROR)
// 3 = walk_left (V_MIRROR)
// 4 = jump_right (NO_MIRROR)
// 5 = jump_left (V_MIRROR)
// 6 = fall_right (NO_MIRROR)
// 7 = fall_left (V_MIRROR)

// 8 = drop_right (NO_MIRROR) // lost health
// 9 = drop_left (V_MIRROR)   // use anim_nutmegbow_static

// 10 = disabled

// 11 = glide right
// 12 = glide left

void Start_SpriteNutmegBow(void) 
{
	// Large limits so we can park the preload fully off-screen
	THIS->lim_x = 5000;
	THIS->lim_y = 5000;

	SetSpriteAnim(THIS, anim_nutmegbow_static, 16);
	nutmeg.bowanim = 0;

	nutmeg.bow_counter = 0;
	spr_nutmegbow = THIS;
    bow_prev_anim = 0xFF;
    bow_bob_index = 0;
    bow_bob_timer = 0;
}

// the falling speed of the box at each bow_counter frame
static const INT8 Y_OFFSET_AT_COUNTER [] = {
	0,
	-5,
	-4,
	-3,
	-2,
	-1,
	-1,
	0,
	0,
	1,
	1,
	2,
	2,
	3,
	3,
	4,
	4,
	5,
	5,
	6,
	6,
	7,
	7,
	8,
	8,
	9,
	9,
	10,
	10,
	11,
	11,
	12,
	12,
	13,
	13,
	14,
	14,
	0,
};

// returns false if the bow sprite has been destroyed
// can't use THIS, because it is called fromthe spr_nutmeg update fn
void nutmegBow_update(void) BANKED 
{
    // If hidden preload, do nothing (keeps bow off-screen until enabled by pickup)
    if (spr_nutmegbow && spr_nutmegbow->custom_data[0] == 2) {
        // keep off-screen
        spr_nutmegbow->x = 65527;
        spr_nutmegbow->y = 240;
        return;
    }
    if (nutmeg.lostbow == false) {
        UINT8 bow_state = nutmeg.bowanim;
        if (bow_state >= ARRAY_LEN(bow_placements)) {
            bow_state = 0;
        }

        // In water (including pools), force a stable bow placement and static anim
        if (level.isWaterLevel || nutmeg.isSwimming) {
            const INT8* swim_x = (nutmeg.direction == right) ? bow_swim_x_r : bow_swim_x_l;
            const INT8* swim_y = (nutmeg.direction == right) ? bow_swim_y_r : bow_swim_y_l;
            spr_nutmegbow->x = (INT16)spr_nutmeg->x + swim_x[0];
            spr_nutmegbow->y = (INT16)spr_nutmeg->y + swim_y[0];
            spr_nutmegbow->mirror = (nutmeg.direction == right) ? NO_MIRROR : V_MIRROR;
            SetSpriteAnim(spr_nutmegbow, anim_nutmegbow_static, 1);
            return;
        }

        const BowPlacementConfig* cfg = &bow_placements[bow_state];
        if ((bow_state == 10) || (cfg->frame_count == 0)) {
            spr_nutmegbow->x = 65527;
            spr_nutmegbow->y = 240;
            spr_nutmegbow->mirror = NO_MIRROR;
            return;
        }

        if (bow_state != bow_prev_anim) {
            SetSpriteAnim(spr_nutmegbow, anim_nutmegbow_static, 16);
            bow_prev_anim = bow_state;
            bow_bob_index = 0;
            bow_bob_timer = 0;
        }

        UINT8 frame_idx = spr_nutmeg->anim_frame;
        if (frame_idx >= cfg->frame_count) {
            frame_idx = cfg->frame_count ? (cfg->frame_count - 1) : 0;
        }

        INT16 target_x = (INT16)spr_nutmeg->x + cfg->frame_x[frame_idx];
        INT16 target_y = (INT16)spr_nutmeg->y + cfg->frame_y[frame_idx];
        spr_nutmegbow->x = target_x;
        spr_nutmegbow->y = target_y;
        spr_nutmegbow->mirror = cfg->mirror;
    }
    else if (nutmeg.lostbow == true) {
		SetSpriteAnim(spr_nutmegbow, anim_nutmegbow_static, 1);
	
		if (nutmeg.bowanim == 8) { spr_nutmegbow->mirror = NO_MIRROR; }
		else { spr_nutmegbow->mirror = V_MIRROR; }

        // Ensure bow can fall offscreen during drop
        spr_nutmegbow->lim_y = 300;
        // Ensure starting height is anchored once at drop start
        if (nutmeg.bow_counter == 0) {
            UINT8 cfg_index = (nutmeg.bowanim == 9) ? 9 : 8;
            if (cfg_index >= ARRAY_LEN(bow_placements)) {
                cfg_index = 8;
            }
            const BowPlacementConfig* drop_cfg = &bow_placements[cfg_index];
            UINT8 frame_idx = spr_nutmeg->anim_frame;
            if (frame_idx >= drop_cfg->frame_count) {
                frame_idx = drop_cfg->frame_count ? (drop_cfg->frame_count - 1) : 0;
            }
            spr_nutmegbow->y = (INT16)spr_nutmeg->y + drop_cfg->frame_y[frame_idx];
            spr_nutmegbow->x = (INT16)spr_nutmeg->x + drop_cfg->frame_x[frame_idx];
            // freeze following Nutmeg; begin autonomous drop
            spr_nutmegbow->custom_data[0] = 0;
        }
        // Apply falling offset each frame without collision blocking
        spr_nutmegbow->y += (INT8)Y_OFFSET_AT_COUNTER[nutmeg.bow_counter];

		nutmeg.bow_counter++;

        // Despawn once sufficiently below the screen or after full drop frames
        if ((spr_nutmegbow->y > 200) || (nutmeg.bow_counter >= 37)) {
			nutmeg.health = low;
			nutmeg.bowanim = 10;
			SpriteManagerRemoveSprite(spr_nutmegbow);
		}
	}
}

void Update_SpriteNutmegBow(void) 
{
	// If used as HUD overlay on overworld nut head, freeze one frame and don't follow Nutmeg
	if (THIS->custom_data[0] == 1) {
		SetSpriteAnim(THIS, anim_nutmegbow_static, 1);
		return;
	}
	// Hidden mode for in-level preloaded bow to control draw order; keep off-screen and do not draw or follow
	if (THIS->custom_data[0] == 2) {
		THIS->x = 65527; // far off left
		THIS->y = 0;
		return;
	}
	// updates are done from the spr_nutmeg in levels
}


void Destroy_SpriteNutmegBow(void) 
{
	spr_nutmegbow = 0;
}