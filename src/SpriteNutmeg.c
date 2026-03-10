#include "Banks/SetAutoBank.h"
#ifdef USE_CBT_FX
#include "Sound.h"
#undef PlayFx
#define PlayFx(...) do {} while(0)
#endif
#ifdef USE_CBT_FX
#include "third_party/cbtfx/cbtfx.h"
#endif
#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Sound.h"
#include "Music.h"
#include "Palette.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Sfx.h"
#include "SfxChain.h"
#include "../src/GlobalVars.h"
#include "SpriteNutmeg.h"

DECLARE_MUSIC (quickdeath);

bool isPaused;

// These speed structs are used by enemies fns, 
// so they need to live in ram (or in bank 0)

// all the speed parameters for nutmeg while she is in a normal level
static const NutmegSpeedT groundSpeed = {
	.frictionX = 35,
    .airFrictionX = 12,
	.runIncX = 52,        // slightly stronger run acceleration
	.runMaxX = 168,       // slightly higher run top speed
	.walkIncX = 52,
	.walkMaxX = 168,
    .enemyBounceY = 500,
    .cutsceneMaxX = 100,
	.initJumpY = 150,
	.jumpY = 18,          // a touch less sustained rise
	.jumpYMax = 310,      // cap for normal held jump height (reverted)
	.fallInitY = 100,
	.fallIncY = 19,       // slightly firmer gravity
	.fallMaxY = 280,      // slightly higher terminal velocity
	.fallGlideMaxY = 70   // much slower fall while gliding for long float
};

// all the speed parameters for nutmeg while she is in a normal level
static const NutmegSpeedT iceGroundSpeed = {
	.frictionX = 00,
    .airFrictionX = 3,
	.runIncX = 3,
	.runMaxX = 200,
	.walkIncX = 3,
	.walkMaxX = 200,
    .enemyBounceY = 500,
    .cutsceneMaxX = 100,
	.initJumpY = 150,
	.jumpY = 20,
	.jumpYMax = 330,
	.fallInitY = 100,
	.fallIncY = 20,
	.fallMaxY = 300,
	.fallGlideMaxY = 130
};

// all the speed parameters for nutmeg while she is underwater
static const NutmegSpeedT waterSpeed = {
    .frictionX = 18,      // slightly more horizontal drag
    .airFrictionX = 18,   // more drag while in water
    .runIncX = 35,        // slower acceleration
    .runMaxX = 130,       // lower top speed
    .walkIncX = 35,
    .walkMaxX = 130,
    .cutsceneMaxX = 100,
    .enemyBounceY = 250,
    .initJumpY = 85,      // smaller initial swim "jump"
    .jumpY = 12,          // gentler sustained rise
    .jumpYMax = 160,      // lower ceiling for held rise
	.fallInitY = 100,
    .fallIncY = 4,        // slightly less gravity per frame
    .fallMaxY = 120,      // slower terminal fall
    .fallGlideMaxY = 90   // gliding is a bit slower still
};


static const UINT8 anim_nutmeg_idle_right[] = {4, 1, 2, 3, 4};
static const UINT8 anim_nutmeg_idle_left[]  = {4, 1, 2, 3, 4};

static const UINT8 anim_nutmeg_walk_right[] = {4, 5, 6, 7, 8};
static const UINT8 anim_nutmeg_walk_left[]  = {4, 5, 6, 7, 8};

static const UINT8 anim_nutmeg_jump_right[] = {1, 9};
static const UINT8 anim_nutmeg_jump_left[]  = {1, 9};

static const UINT8 anim_nutmeg_fall_right[] = {1, 10};
static const UINT8 anim_nutmeg_fall_left[]  = {1, 10};

static const UINT8 anim_nutmeg_land_right[] = {1, 11};
static const UINT8 anim_nutmeg_land_left[]  = {1, 11};
   
// Hurt/Death animation with extended final frame to hold pose while timers elapse
static const UINT8 anim_nutmeg_hurt_right[] = {20, 12, 12, 12, 12, 13,
  14,14,14,14,14,14,14,14,14,14,14,14,14,14};
static const UINT8 anim_nutmeg_hurt_left[]  = {20, 12, 12, 12, 12, 13,
  14,14,14,14,14,14,14,14,14,14,14,14,14,14};

static const UINT8 anim_nutmeg_glide[] = {1, 15};

static const UINT8 anim_nutmeg_swim[] = {2, 16, 17}; // legacy two-frame loop (unused after switch to directional swim)
static const UINT8 anim_nutmeg_swim_up[] = {1, 16};
static const UINT8 anim_nutmeg_swim_down[] = {1, 17};
// Single-frame death pose to avoid looping/restarting animations during death
static const UINT8 anim_nutmeg_death[] = {1, 14};

// Underwater blue palette for Nutmeg (matches swim frames intent)
static const UWORD pal_nutmeg_blue[] = { RGB(31, 31, 31), RGB(19, 22, 30), RGB(12, 13, 28), RGB(8,  8, 27) };
// Normal palette for Nutmeg
static const UWORD pal_nutmeg_normal[] = { RGB(31, 31, 31), RGB(31, 27, 23), RGB(31, 17, 6), RGB(0,  0,  0) };
// Flash palette (bright white) to indicate hurt
static const UWORD pal_nutmeg_flash[] = { RGB(31, 31, 31), RGB(31, 31, 31), RGB(31, 31, 31), RGB(0,  0,  0) };

static const UINT8 anim_nutmeg_lostbow[] = {2, 11, 0};

extern Sprite *spr_nutmegbow;

// Declare a pointer to a sprite
Sprite * spr_nutmeg;
Sprite * spr_camera;

NutmegT nutmeg;

bool GameOver = false;
//cutscene mode!
switcher cutscenemode;
bool cutscenewalkleft;
bool cutscenewalkright;
bool levelGoldenAcornFound = false;


//storing collisions around player after movement
UINT8 collisionX;
UINT8 collisionY;

//if nutmeg loses her bow, add some kickback
UINT8 kickbackcounter;

static UINT8 acorn_throw_cooldown = 0;

// After jumping, allow momentum to carry in air for a short time (reduced air braking)
static UINT8 ice_air_brake_counter = 0; // frames remaining of reduced air friction

// --- Dynamic swim detection on solid water tiles (e.g., tile id 25) ---
// Solid water fill tile ID (VRAM index) used below animated surface
// BGB shows tile numbers in hex; '19' hex = 0x19 = 25 decimal
#define DEFAULT_SOLID_WATER_TILE_ID 0x19
// Animated surface tiles (from Water.c)
#define SURFACE_WATER_TILE_1 0x1A
#define SURFACE_WATER_TILE_2 0x1B
#define SURFACE_WATER_TILE_3 0x1C
static UINT8 swim_enter_counter = 0; // hysteresis for entering water
static UINT8 swim_exit_counter = 0;  // hysteresis for exiting water
static UINT8 swim_buoy_counter = 0;  // temporary extra buoyancy frames after entering
static UINT8 swim_exit_boost_window = 0; // frames to allow jump boost on exit
// Hard fallback counter for death transitions
static UINT16 deathHardCounter = 0;
static UINT8 deathSongLock = 0; // ensure quickdeath triggers once even if state re-enters
static UINT8 playedQuickdeath = 0; // per-life guard to avoid music re-trigger loops
static UINT16 deathStartSysTime = 0; // vblank anchor for death duration
static UINT8 pitDeathLock = 0; // prevent repeated pit-death triggers within the same life
static UINT8 lastCutsceneMode = 0; // track transition out of level intro
// --- Wall movement tunables ---
static const INT16 wallSlideMaxFallY = 80;      // clamp downward speed while sliding
static const INT16 wallJumpUpVel = 320;         // stronger vertical push on wall jump (positive; applied as -value)
static const INT16 wallJumpHorizVel = 200;      // base horizontal push away from wall
static const INT16 wallJumpHorizVelStrong = 240;// stronger push if pressing away direction
static const UINT8 kWallCoyoteFrames = 4;       // grace frames after leaving wall
static const UINT8 kWallRegrabCooldown = 10;    // frames before we can slide again after a wall jump
static const UINT8 kWallJumpGlideLock = 6;      // frames to block glide after a wall jump
// Debounce Start button across state transitions to avoid starting paused
static UINT8 pause_input_lock_frames = 0;
static void nutmeg_begin_death(void) {
    if (nutmeg.isDying) return;
    nutmeg.pendingDeath = false;
    nutmeg.pendingDeathTimer = 0;
    nutmeg.isDying = true;
    // initialize counters; let FSM state 1 handle music start and timing
    nutmeg.deathFrames = 0;
    nutmeg.deathtimer = 0;
    deathHardCounter = 0;
    nutmeg.deathSoundPlayed = false;
    deathSongLock = 0;
    // allow falling out bottom while dying; set beyond 255 to prevent despawn
    spr_nutmeg->lim_y = 300;
    // stop glide/motion carry; ensure death anim plays immediately
    nutmeg.isGliding = false;
    nutmeg.speedX = 0;
    if (spr_nutmeg) {
        // Use the full hurt/death sequence; long tail holds last frame
        if (nutmeg.direction == left) SetSpriteAnim(spr_nutmeg, anim_nutmeg_hurt_left, 10);
        else SetSpriteAnim(spr_nutmeg, anim_nutmeg_hurt_right, 10);
    }
    // Enter FSM init; music will be played once there
    nutmeg.deathState = 1;
}

static UINT8 read_bg_tile_at_px(UINT16 px, UINT16 py) {
    // Map world pixels to BG map indices (ZGB keeps a 32x32 tilemap in VRAM)
    UINT8 tx = (UINT8)((px >> 3) & 31);
    UINT8 ty = (UINT8)((py >> 3) & 31);
    UINT8 id = 0xFF;
    VBK_REG = 0; // tile ids
    get_bkg_tiles(tx, ty, 1, 1, &id);
    return id;
}

static void DetectSwimmingSolidWater(void) {
    // In dedicated water levels, always be in swim mode
    if (level.isWaterLevel) {
        nutmeg.isSwimming = true;
        return;
    }
    // Allow per-level override: when set to NO_ICE_TILES (255), disable solid-water swim detection entirely
    if (level.waterSolidTileId == NO_ICE_TILES) {
        nutmeg.isSwimming = false;
        return;
    }
    // Sample deeper into the body and across width to detect solid water fill
    // Feet are near y + 12/14 for 8x16 sprites
    UINT16 yFeet = spr_nutmeg->y + 12;
    UINT16 yWaist = spr_nutmeg->y + 6;   // mid-body inside fill
    UINT16 yHead = (spr_nutmeg->y > 4) ? (spr_nutmeg->y - 4) : 0; // near surface

    UINT16 xMid = spr_nutmeg->x + 4;
    UINT16 xLeft = spr_nutmeg->x + 2;
    UINT16 xRight = spr_nutmeg->x + 10;

    UINT8 feetMid = read_bg_tile_at_px(xMid, yFeet);
    UINT8 feetL = read_bg_tile_at_px(xLeft, yFeet);
    UINT8 feetR = read_bg_tile_at_px(xRight, yFeet);
    UINT8 waistMid = read_bg_tile_at_px(xMid, yWaist);
    UINT8 headMid = read_bg_tile_at_px(xMid, yHead);

    UINT8 solidId = (level.waterSolidTileId != 0) ? level.waterSolidTileId : DEFAULT_SOLID_WATER_TILE_ID;
    UINT8 feetSolid = (feetMid == solidId) || (feetL == solidId) || (feetR == solidId);
    UINT8 waistSolid = (waistMid == solidId);
    UINT8 headSurface = (headMid == SURFACE_WATER_TILE_1) || (headMid == SURFACE_WATER_TILE_2) || (headMid == SURFACE_WATER_TILE_3);

    // Inside water when feet or waist are in solid water fill
    UINT8 inside = feetSolid || waistSolid;

    bool wasSwimming = nutmeg.isSwimming;

    if (inside) {
        if (swim_enter_counter < 3) swim_enter_counter++;
        swim_exit_counter = 0;
        if (swim_enter_counter >= 2) {
            nutmeg.isSwimming = true;
        }
    } else {
        // Only consider exiting when BOTH feet and waist are not solid water
        if (!feetSolid && !waistSolid) {
            if (swim_exit_counter < 4) swim_exit_counter++;
        }
        swim_enter_counter = 0;
        if (swim_exit_counter >= 4) {
            nutmeg.isSwimming = false;
        }
    }

    // On transition, add a small splash and set a buoyancy window
    if (!wasSwimming && nutmeg.isSwimming) {
        swim_buoy_counter = 12;
        if (nutmeg.speedY > 60) nutmeg.speedY = 60; // dampen downward speed on entry
        SpriteManagerAdd(SpritePuff, spr_nutmeg->x-2, spr_nutmeg->y-6);
        SpriteManagerAdd(SpritePuff, spr_nutmeg->x+10, spr_nutmeg->y-6);
        // splash sfx (enter)
        Sfx_WaterEnter();
        // switch to blue palette when entering swim
        SetPalette(SPRITES_PALETTE, SPRITE_GET_CGB_PALETTE(spr_nutmeg), 1, pal_nutmeg_blue, _current_bank);
        // allow falling out of deep water by removing bottom clamp while swimming
        spr_nutmeg->lim_y = 255;
    } else if (wasSwimming && !nutmeg.isSwimming) {
        // Restore strong exit boost when leaving water on-screen; avoid any boost near/past bottom (pit)
        INT16 screenY = (INT16)spr_nutmeg->y - (INT16)scroll_y;
        bool onScreen = (screenY <= 150);
        bool nearBottom = (screenY > 140);

        if (onScreen && ((INT16)nutmeg.speedY < 0)) {
            INT16 boost = groundSpeed.initJumpY + 275; // ~425 total pop out of water
            const INT16 waterExitMax = 450;
            if (boost > waterExitMax) boost = waterExitMax;
            nutmeg.speedY = -boost;
            swim_exit_boost_window = 6; // short grace to ensure boost if sampled next frame
            SpriteManagerAdd(SpritePuff, spr_nutmeg->x-2, spr_nutmeg->y-6);
            SpriteManagerAdd(SpritePuff, spr_nutmeg->x+10, spr_nutmeg->y-6);
            Sfx_WaterExit();
        } else {
            // No grace boost window when exiting at bottom or while falling
            swim_exit_boost_window = 0;
        }
        // restore normal palette regardless
        {
            static const UWORD pal_nutmeg_normal[] = { RGB(31, 31, 31), RGB(31, 27, 23), RGB(31, 17, 6), RGB(0, 0, 0) };
            SetPalette(SPRITES_PALETTE, SPRITE_GET_CGB_PALETTE(spr_nutmeg), 1, pal_nutmeg_normal, _current_bank);
        }
        // restore normal bottom clamp only if not near bottom; keep unclamped to allow pit fall
        if (!nearBottom) spr_nutmeg->lim_y = 144; else spr_nutmeg->lim_y = 255;
    }
}

// moved to NutmegT in GlobalVars

//reset nutmeg's state back to default
void ResetState(void) {
    nutmeg.speedY = 0;
    nutmeg.speedX = 0;
    
    nutmeg.offsetX = 0;
    nutmeg.offsetY = 0;

    collisionX = 0;
    collisionY = 0;
    nutmeg.jumpPeak = 0;
    nutmeg.movestate = grounded;

    nutmeg.direction = right;

    cutscenewalkleft = false;
    cutscenewalkright = false;

    // Only reset death-related state when not currently in a death sequence.
    // This prevents re-inits (e.g., from engine sprite lifecycle) from retriggering quickdeath.
    if ((nutmeg.isDying == false) && (playedQuickdeath == 0)) {
        nutmeg.deathtimer = 0;
        nutmeg.isDying = false;
        nutmeg.deathSoundPlayed = false;
        nutmeg.deathFrames = 0;
        nutmeg.deathState = 0;
        deathSongLock = 0;
        playedQuickdeath = 0;
        deathStartSysTime = 0;
    }
    // Disable wind by default; levels enable explicitly (e.g., 1-5)
    windEnabled = false;
    nutmeg.hurtFlashCounter = 0;
    nutmeg.isInvincible = false;

    GameOver = false;
    isPaused = false;

    kickbackcounter = 0;

    // Ensure bow-drop state doesn't carry across levels
    nutmeg.lostbow = false;
    nutmeg.bow_counter = 0;

    nutmeg.speeds = &groundSpeed;
    nutmeg.enemyBounceY = nutmeg.speeds->enemyBounceY;
    // Ensure new levels start in a clean state
    nutmeg.isGliding = false;
    nutmeg.isSwimming = false;

    // wall movement
    nutmeg.isWallSliding = false;
    nutmeg.wallSide = right;
    nutmeg.lastWallSide = right;
    nutmeg.wallCoyoteFrames = 0;
    nutmeg.wallRegrabCooldown = 0;
    nutmeg.wallJumpGlideLock = 0;
    nutmeg.pickupPauseFrames = 0;
    isPaused = false;
    pause_input_lock_frames = 8; // small grace to ignore stale START during transitions
}

static void grant_bow_powerup(void) {
    if (nutmeg.hasbow) {
        return;
    }
    nutmeg.hasbow = true;
    nutmeg.lostbow = false;
    nutmeg.bow_counter = 0;
    nutmeg.health = full;
    nutmeg.pickupPauseFrames = 24;
    nutmeg.isInvincible = true;
    nutmeg.hurtFlashCounter = 24;
    if (spr_nutmegbow) {
        spr_nutmegbow->custom_data[0] = 0;
        spr_nutmegbow->x = spr_nutmeg->x;
        spr_nutmegbow->y = spr_nutmeg->y;
    } else {
        spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, spr_nutmeg->x, spr_nutmeg->y);
    }
#ifdef USE_CBT_FX
    Sfx_BowPickup();
#else
    SfxChain_Start(4, 2);
#endif
    if (gameStats.totalPowerups < 0xFFFFu) {
        gameStats.totalPowerups++;
    }
}

static void try_throw_acorn(void) {
    if (acorn_throw_cooldown > 0) {
        return;
    }
    if (nutmeg.acorns == 0) {
        return;
    }
    if (nutmeg.isDying || nutmeg.pickupPauseFrames > 0) {
        return;
    }
    INT16 shotX = spr_nutmeg->x + ((nutmeg.direction == right) ? 12 : -12);
    INT16 shotY = spr_nutmeg->y - 8;
    Sprite* shot = SpriteManagerAdd(SpriteAcorn, shotX, shotY);
    if (!shot) {
        return;
    }
    nutmeg.acorns--;
    acorn_throw_cooldown = 12;
    INT8 init_vx = (nutmeg.direction == right) ? 6 : -6;
    INT8 init_vy = -8;
    shot->lim_x = 9999;
    shot->lim_y = 9999;
    shot->custom_data[4] = 1; // projectile mode
    shot->custom_data[0] = (UINT8)init_vx;
    shot->custom_data[1] = (UINT8)init_vy;
    shot->custom_data[2] = 0;
    shot->mirror = (nutmeg.direction == right) ? NO_MIRROR : H_MIRROR;
#ifdef USE_CBT_FX
    Sfx_UIClick();
#else
    PlayFx(CHANNEL_4, 4, 0x20, 0x91, 0x40, 0x80);
#endif
}


void Start_SpriteNutmeg(void) {
    spr_nutmeg = THIS;

    ResetState();

    THIS->lim_x = 500;
	THIS->lim_y = 144;
    SetSpriteAnim(spr_nutmeg, anim_nutmeg_idle_left, 5);

    // At spawn, only water levels start in swim; pools will be picked up by detector
    if (level.isWaterLevel)
    {
         nutmeg.speeds = &waterSpeed;
         nutmeg.isSwimming = true;
         // Set initial swim frame based on vertical speed
         if (nutmeg.speedY <= 0) SetSpriteAnim(spr_nutmeg, anim_nutmeg_swim_up, 1);
         else SetSpriteAnim(spr_nutmeg, anim_nutmeg_swim_down, 1);
         // apply underwater palette to Nutmeg's sprite
         SetPalette(SPRITES_PALETTE, SPRITE_GET_CGB_PALETTE(spr_nutmeg), 1, pal_nutmeg_blue, _current_bank);
    }
    else
    {
         nutmeg.speeds = &groundSpeed;
         nutmeg.isSwimming = false;
    }
    nutmeg.enemyBounceY = nutmeg.speeds->enemyBounceY;

    // Ensure fresh entry state for each level
    nutmeg.isGliding = false;
    pitDeathLock = 0; // allow pit detection again in new level
    // If coming from a death, do not auto-grant the bow; keep existing hasbow state
    if (nutmeg.isDying) {
        nutmeg.lostbow = false;
        nutmeg.bow_counter = 0;
    }
}

// Create nutmeg sprite at x,y (and her bow if required)
Sprite *nutmeg_Add (uint16_t x, uint16_t y) BANKED
{
	// Add bow first, then Nutmeg so Nutmeg is layered above bow by ZGB order
	if (nutmeg.hasbow == true) {
		spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, x, y);
	}
	spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, x, y);
    return spr_nutmeg;
}

static INT8 MoveX (void)
{
    INT8 r = 0;
    while (nutmeg.offsetX <= -100)
    {
        nutmeg.offsetX += 100;
        r --;
    }
    while (nutmeg.offsetX >= 100)
    {
        nutmeg.offsetX -= 100;
        r ++;
    }
    return r;
}

static INT8 MoveY (void)
{
    INT8 r = 0;
    while (nutmeg.offsetY <= -100)
    {
        nutmeg.offsetY += 100;
        r --;
    }
    while (nutmeg.offsetY >= 100)
    {
        nutmeg.offsetY -= 100;
        r ++;
    }
    return r;
}

static void update_pending_death_motion(Sprite* sprite) {
    UINT8 elapsed = 30u - nutmeg.pendingDeathTimer;
    INT8 dir = (nutmeg.direction == left) ? 1 : -1;
    INT8 dx = 0;

    if (elapsed < 10u) {
        dx = (INT8)(dir * 2);
    } else if (elapsed < 25u) {
        dx = dir;
    }

    if (dx != 0) {
        TranslateSprite(sprite, dx, 0);
    }
    nutmeg.offsetX = 0;
    nutmeg.offsetY = 0;
    nutmeg.speedX = 0;
    nutmeg.speedY = 0;
    nutmeg.movestate = grounded;
}


void nutmegBow_update(void ) BANKED ;

static void move_whileDead(void)
{
    cutscenemode = enabled;

    if (nutmeg.direction == left) {
        SetSpriteAnim(THIS, anim_nutmeg_hurt_left, 10);
        
        if (nutmeg.deathtimer < 10) 
        {
            nutmeg.speedX = nutmeg.speeds->cutsceneMaxX;
        }
        else 
        {
            nutmeg.speedX = 0;
        }
    }
    else if (nutmeg.direction == right) {
        SetSpriteAnim(THIS, anim_nutmeg_hurt_right, 10);

        if (nutmeg.deathtimer < 10) 
        {
            nutmeg.speedX = nutmeg.speeds->cutsceneMaxX;
        }
        else 
        {
            nutmeg.speedX = 0;
        }
    }

    // Apply gravity and move while dying
    nutmeg.offsetX += nutmeg.speedX;
    nutmeg.speedY += nutmeg.speeds->fallIncY;
    nutmeg.offsetY += nutmeg.speedY;

    INT8 delta = MoveX();
    collisionX = TranslateSprite(THIS, delta, 0);
    delta = MoveY();
    collisionY = TranslateSprite(THIS, 0, delta);
    if ((nutmeg.speedY < 0) && (collisionY != 0)) {
        // Hitting the ceiling: snap velocity to zero so we ease into the fall
        nutmeg.speedY = 0;
        nutmeg.offsetY = 0;
        nutmeg.jumpPeak = 1;
        // Bring Nutmeg back up against the ceiling to avoid a visible bounce
        TranslateSprite(THIS, 0, -1);
    }

    // Small lift after stepping through doors so Nutmeg doesn't sink into tiles
    if ((collisionY != 0) && (nutmeg.speedY >= 0) && (delta == 0)) {
        TranslateSprite(THIS, 0, -2);
    }

    if (collisionY == 0) {
        nutmeg.movestate = inair;
    } else {
        nutmeg.movestate = grounded;
        nutmeg.speedY = nutmeg.speeds->fallInitY;
        nutmeg.offsetY = 0;
    }
}

static void update_inCutscene(void)
{
    if (cutscenewalkright == true) 
    {
        nutmeg.direction = right;
        THIS->mirror = NO_MIRROR;

        nutmeg.speedX += nutmeg.speeds->walkIncX;
        if (nutmeg.speedX > nutmeg.speeds->cutsceneMaxX && nutmeg.movestate == grounded)
            nutmeg.speedX = nutmeg.speeds->cutsceneMaxX;

    }

    if (cutscenewalkleft == true) {
        nutmeg.direction = left;
        THIS->mirror = V_MIRROR;

        nutmeg.speedX -= nutmeg.speeds->walkIncX;
        if (nutmeg.speedX < -nutmeg.speeds->cutsceneMaxX && nutmeg.movestate == grounded)
            nutmeg.speedX = -nutmeg.speeds->cutsceneMaxX;
    }
  
    if (nutmeg.movestate == inair) {

        if (collisionY != 0) {
            nutmeg.jumpPeak = 1;
        }

        if (nutmeg.speedY < nutmeg.speeds->fallMaxY) {
            nutmeg.speedY += nutmeg.speeds->fallIncY;
            nutmeg.jumpPeak = 1;
        }

        if (nutmeg.speedX < -nutmeg.speeds->cutsceneMaxX) 
        {  
            nutmeg.speedX = -nutmeg.speeds->cutsceneMaxX;
        }

        if (nutmeg.speedX > nutmeg.speeds->cutsceneMaxX) 
        {
            nutmeg.speedX = nutmeg.speeds->cutsceneMaxX;
        }
    }

    // apply speed to position
    nutmeg.offsetX += nutmeg.speedX;
    nutmeg.offsetY += nutmeg.speedY;

    INT8 delta = MoveX();
    collisionX = TranslateSprite(THIS, delta, 0);
    
    delta = MoveY();
    collisionY = TranslateSprite(THIS, 0, delta);

    if (level.isWaterLevel || nutmeg.isSwimming)
    {
        nutmeg.speeds = &waterSpeed;
    }
    else
    {
        nutmeg.speeds = &groundSpeed;
        nutmeg.isOnIce = false;
        if ((collisionY >= level.iceTileMin) && (collisionY <= level.iceTileMax))
        {
            nutmeg.speeds = &iceGroundSpeed;
            nutmeg.isOnIce = true;
        }   
    } 
    nutmeg.enemyBounceY = nutmeg.speeds->enemyBounceY;

    if (collisionX != 0) {
        nutmeg.speedX = 0;
        nutmeg.offsetX = 0;
    }
    else if (cutscenewalkleft == false && cutscenewalkright == false) {
        if (nutmeg.speedX > 0) {
            if (nutmeg.speedX > nutmeg.speeds->frictionX) 
            {
                nutmeg.speedX -= nutmeg.speeds->frictionX;
            }
            else nutmeg.speedX = 0;
        }
        else if (nutmeg.speedX < 0) {
            if (nutmeg.speedX < -nutmeg.speeds->frictionX) 
            {
                nutmeg.speedX += nutmeg.speeds->frictionX;
            }
            else nutmeg.speedX = 0;
        }
    }

    if (collisionY == 0) {
        nutmeg.movestate = inair;
    }
    else {
        nutmeg.movestate = grounded;
        
        // We need to move down in order to hit the ground each turn
        // Only pin to ground in non-water levels; allow sinking out of deep water pits
        if (!(level.isWaterLevel || nutmeg.isSwimming)) {
            nutmeg.speedY = 100;
        }
        nutmeg.offsetY = 0;
    }

    if (nutmeg.isDying == false)
    {
        if (nutmeg.movestate == grounded) {
            if (level.isWaterLevel || nutmeg.isSwimming) {
                // choose swim frame by vertical velocity and skip other anims
                if (!KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_A) && !KEY_PRESSED(J_B)) {
                SetSpriteAnim(THIS, anim_nutmeg_swim, 5);
                } else if (nutmeg.speedY <= 0) SetSpriteAnim(THIS, anim_nutmeg_swim_up, 1);
                else SetSpriteAnim(THIS, anim_nutmeg_swim_down, 1);
            } else {
                if (nutmeg.speedX < nutmeg.speeds->cutsceneMaxX && nutmeg.speedX > -nutmeg.speeds->cutsceneMaxX) {
                    if (nutmeg.direction == right) {
                        SetSpriteAnim(THIS, anim_nutmeg_idle_right, 5);
                        nutmeg.bowanim = 0;
                    }
                    else {
                        SetSpriteAnim(THIS, anim_nutmeg_idle_left, 5);
                        nutmeg.bowanim = 1;
                    }
                }
                else {
                    if (nutmeg.direction == right) {
                        SetSpriteAnim(THIS, anim_nutmeg_walk_right, 15);
                        nutmeg.bowanim = 2;
                    }
                    else {
                        SetSpriteAnim(THIS, anim_nutmeg_walk_left, 15);
                        nutmeg.bowanim = 3;
                    }
                }
            }
        }
        else if (nutmeg.movestate == inair) {
            if (level.isWaterLevel || nutmeg.isSwimming) {
                if (nutmeg.speedY <= 0) SetSpriteAnim(THIS, anim_nutmeg_swim_up, 1);
                else SetSpriteAnim(THIS, anim_nutmeg_swim_down, 1);
            } else {
                if (nutmeg.speedY > 60) {
                    if (nutmeg.direction == right) {
                        SetSpriteAnim(THIS, anim_nutmeg_fall_right, 1);
                        nutmeg.bowanim = 6;
                    }
                    else  {
                        SetSpriteAnim(THIS, anim_nutmeg_fall_left, 1);
                        nutmeg.bowanim = 7;
                    }
                }
                else if (nutmeg.speedY < -60) {
                    if (nutmeg.direction == right) {
                        SetSpriteAnim(THIS, anim_nutmeg_jump_right, 1);
                        nutmeg.bowanim = 4;
                    }
                    else {
                        SetSpriteAnim(THIS, anim_nutmeg_jump_left, 1);
                        nutmeg.bowanim = 5;
                    }
                }
            }
        }
    }
}

static void try_quit_to_overworld(void)
{
    if ((level.isOverworld == false) && (nutmeg.isDying == false))
    {
        StopMusic;
        isPaused = false;
        rWY = 144-8;
        level_current = level_playing;
        level_next = level_playing;
        levelGoldenAcornFound = false;
        SetState(StateOverworld);
    }
}

void update_aliveInControl (void)
{ 
    // Freeze controls/motion during pickup pause
    if (nutmeg.pickupPauseFrames > 0) {
        nutmeg.pickupPauseFrames--;
        // zero out velocities and offsets; leave gravity neutral so she hangs in-air
        nutmeg.speedX = 0;
        nutmeg.speedY = 0;
        return;
    }

    if (nutmeg.pendingDeath) {
        update_pending_death_motion(THIS);
        return;
    }

    if (pause_input_lock_frames > 0) { pause_input_lock_frames--; }
    // Start + Select held together: quick return to overworld on replayed levels
    bool can_quick_exit = (level_playing > 0)
                       && (level_playing < MAX_LEVEL_TRACKING)
                       && levelCompleted[level_playing]
                       && !levelbeat;
    if (can_quick_exit && KEY_PRESSED(J_START) && KEY_PRESSED(J_SELECT))
    {
        try_quit_to_overworld();
        return;
    }
        if ((pause_input_lock_frames == 0) && KEY_TICKED(J_START)) 
	{
        if (level_current == 0)
        {
            // don't pause in the tree house
        }
        else
        {
		isPaused = true;
#ifdef USE_CBT_FX
		Sfx_PauseOpen();
#endif
		    rWY = 144-24;
            return;
        }
	}

    // Pit death detection based on screen-space Y to work across all level types (autoscroll, tall maps, etc)
    {
        // Use 32-bit math to avoid overflow/wrap issues when Y grows large
        INT32 screenY = (INT32)THIS->y - (INT32)scroll_y;
        // If we hit the bottom edge, trigger death once and lock it to avoid re-inits looping music
        if (screenY >= 150) {
            if (pitDeathLock == 0) {
                pitDeathLock = 1;
                nutmeg_begin_death();
            }
        }
    }

    /* * * * * * * * * * * * * * * * * * * */
    /* left and right directional movement */
    /* * * * * * * * * * * * * * * * * * * */
    // Step-up smoothing: if blocked horizontally by a 1-tile ledge and there's space above, climb it
    // Only on ground, not swimming, and while holding into the ledge
    if (KEY_PRESSED(J_RIGHT)) {
        //sets it to the direction you pressed
        nutmeg.direction = right;
        //makes sure the sprites are facing the right way
        THIS->mirror = NO_MIRROR;

        // Attempt small step-up before applying accel
        if (nutmeg.movestate == grounded && !(level.isWaterLevel || nutmeg.isSwimming)) {
            if (collisionX != 0) {
                // try to nudge up by 8px (1 tile) if space is free above head
                UINT8 headTile = read_bg_tile_at_px(THIS->x + 8, THIS->y - 8);
                UINT8 chestTile = read_bg_tile_at_px(THIS->x + 8, THIS->y);
                if (headTile == 0 && chestTile == 0) {
                    TranslateSprite(THIS, 0, -8);
                    collisionY = 0;
                }
            }
        }

        // reintroduce run: slight speedup over walk
        if (KEY_PRESSED(J_B) && !level.isWaterLevel) {
            nutmeg.speedX += nutmeg.speeds->runIncX;
            if (nutmeg.speedX > nutmeg.speeds->runMaxX)
                nutmeg.speedX = nutmeg.speeds->runMaxX;
        } else {
            nutmeg.speedX += nutmeg.speeds->walkIncX;
            if (nutmeg.speedX > nutmeg.speeds->walkMaxX)
                nutmeg.speedX = nutmeg.speeds->walkMaxX;
        }
    }

    if (KEY_PRESSED(J_LEFT)) {
        nutmeg.direction = left;
        //SPRITE_SET_VMIRROR(THIS);
        THIS->mirror = V_MIRROR;

        // Attempt small step-up to the left
        if (nutmeg.movestate == grounded && !(level.isWaterLevel || nutmeg.isSwimming)) {
            if (collisionX != 0) {
                UINT8 headTile = read_bg_tile_at_px(THIS->x - 1, THIS->y - 8);
                UINT8 chestTile = read_bg_tile_at_px(THIS->x - 1, THIS->y);
                if (headTile == 0 && chestTile == 0) {
                    TranslateSprite(THIS, 0, -8);
                    collisionY = 0;
                }
            }
        }

        if (KEY_PRESSED(J_B) && !level.isWaterLevel) {
            nutmeg.speedX -= nutmeg.speeds->runIncX;
            if (nutmeg.speedX < -nutmeg.speeds->runMaxX)
                nutmeg.speedX = -nutmeg.speeds->runMaxX;
        } else {
            nutmeg.speedX -= nutmeg.speeds->walkIncX;
            if (nutmeg.speedX < -nutmeg.speeds->walkMaxX)
                nutmeg.speedX = -nutmeg.speeds->walkMaxX;
        }
    }
    
    /* * * * * * * * * * * * * * * * * * * */
    /*                jump                 */
    /* * * * * * * * * * * * * * * * * * * */
    // If we are on ground and A is pressed, jump
    // Jump sound is played on every successful jump
    // Jump is controlled by reaching high enought acceleration
    // or hitting a wall with head
    // In both cases, we set peak to true and start falling
    // Note that we can't start running when jumping,
    // but we can keep the running speed if we start the jump from run
    if (nutmeg.movestate == grounded) {
        if (KEY_TICKED(J_A)) {
            nutmeg.speedY = -nutmeg.speeds->initJumpY;
            nutmeg.jumpPeak = 0;
            nutmeg.movestate = inair;
            // Always carry momentum a bit longer in air after any jump (feels better)
            ice_air_brake_counter = 12; // ~12 frames of reduced air braking
            
            // SFX: Use underwater stroke sound in water levels, else regular jump
            if (level.isWaterLevel || nutmeg.isSwimming) {
                Sfx_WaterStroke();
            } else {
                Sfx_Jump();
            }

            //display a puff when jumping
            if (nutmeg.direction == right) {
                SpriteManagerAdd(SpritePuff, THIS->x-2, THIS->y-2);
            }
            else {
                Sprite *r = SpriteManagerAdd(SpritePuff, THIS->x+10, THIS->y-2);
                r->mirror = V_MIRROR;
                r->custom_data[1] = 1;
            }
        }
    }
    else if (nutmeg.movestate == inair) {
        if (collisionY != 0) {
            nutmeg.jumpPeak = 1;
        }

        if (nutmeg.jumpPeak == 0 && KEY_PRESSED(J_A) && nutmeg.speedY > -nutmeg.speeds->jumpYMax) {
            nutmeg.speedY -= nutmeg.speeds->jumpY;
        }
        else if (nutmeg.speedY < nutmeg.speeds->fallMaxY) {
            // Add initial buoyancy after entering swim mode
            if (nutmeg.isSwimming && swim_buoy_counter > 0) {
                nutmeg.speedY += (nutmeg.speeds->fallIncY / 3);
                swim_buoy_counter--;
            } else {
                nutmeg.speedY += nutmeg.speeds->fallIncY;
            }
            nutmeg.jumpPeak = 1;
        }
        
        // if nutmeg is swimming, allow a "stroke"; also allow a small exit boost
        if ((nutmeg.isSwimming == true) && (nutmeg.jumpPeak == 1) 
            && (nutmeg.speedY > 20) && (KEY_TICKED(J_A))) {
            nutmeg.speedY = -nutmeg.speeds->initJumpY;
            nutmeg.jumpPeak = 0;
            nutmeg.movestate = inair;
            
            // Underwater stroke SFX
            Sfx_WaterStroke();

            //display a puff when jumping
            if (nutmeg.direction == right) {
                SpriteManagerAdd(SpritePuff, THIS->x-2, THIS->y-2);
            }
            else {
                Sprite *r = SpriteManagerAdd(SpritePuff, THIS->x+10, THIS->y-2);
                r->mirror = V_MIRROR;
                r->custom_data[1] = 1;
            }
        } else if (!nutmeg.isSwimming && swim_exit_boost_window > 0) {
            // Grace exit boost: apply if still on-screen and moving upward (true surface exit)
            INT16 screenY = (INT16)spr_nutmeg->y - (INT16)scroll_y;
            if (screenY <= 150 && (INT16)nutmeg.speedY < 0) {
                nutmeg.speedY = - (nutmeg.speeds->initJumpY + 275);
                if (nutmeg.speedY < -450) nutmeg.speedY = -450;
            }
            swim_exit_boost_window = 0;
        }
        // Wall jump: while sliding or within coyote frames, J_A triggers a jump away from the last wall side
        else if (!(level.isWaterLevel || nutmeg.isSwimming) && KEY_TICKED(J_A) && (nutmeg.isWallSliding || nutmeg.wallCoyoteFrames > 0)) {
            // set velocities; allow held-away input to increase horizontal push
            nutmeg.speedY = -wallJumpUpVel;
            if (nutmeg.lastWallSide == left) {
                // jumping to the right
                bool pressingAway = KEY_PRESSED(J_RIGHT);
                nutmeg.speedX = pressingAway ? wallJumpHorizVelStrong : wallJumpHorizVel;
                nutmeg.direction = right;
                THIS->mirror = NO_MIRROR;
            } else {
                // jumping to the left
                bool pressingAway = KEY_PRESSED(J_LEFT);
                nutmeg.speedX = pressingAway ? -wallJumpHorizVelStrong : -wallJumpHorizVel;
                nutmeg.direction = left;
                THIS->mirror = V_MIRROR;
            }
            nutmeg.isWallSliding = false;
            nutmeg.wallCoyoteFrames = 0;
            nutmeg.wallRegrabCooldown = kWallRegrabCooldown;
            nutmeg.wallJumpGlideLock = kWallJumpGlideLock;
            // allow held A to extend jump height like a normal jump
            nutmeg.jumpPeak = 0;
            // FX
#ifdef USE_CBT_FX
            Sfx_Jump();
#else
            PlayFx(CHANNEL_1, 5, 0x17, 0x9f, 0xf3, 0xc9, 0xc4);
#endif
            // dust at feet
            if (nutmeg.direction == right) {
                SpriteManagerAdd(SpritePuff, THIS->x-2, THIS->y-2);
            } else {
                Sprite *r = SpriteManagerAdd(SpritePuff, THIS->x+10, THIS->y-2);
                r->mirror = V_MIRROR;
                r->custom_data[1] = 1;
            }
        }

        // Handle wall sliding: auto when airborne and pressed against a wall
        // Disabled in water and during death/invincibility knockback effects do not change this logic
        if (!(level.isWaterLevel || nutmeg.isSwimming)) {
            // Detect wall adjacency even without horizontal input by probing +/-1 pixel
            bool contactLeft = false;
            bool contactRight = false;
            UINT8 hit;
            // probe left
            hit = TranslateSprite(THIS, -1, 0);
            if (hit != 0) {
                contactLeft = true;
            } else {
                // revert probe
                TranslateSprite(THIS, 1, 0);
            }
            // probe right
            hit = TranslateSprite(THIS, 1, 0);
            if (hit != 0) {
                contactRight = true;
            } else {
                TranslateSprite(THIS, -1, 0);
            }

            bool touchingAny = contactLeft || contactRight || (collisionX != 0);

            if (touchingAny && nutmeg.wallRegrabCooldown == 0) {
                nutmeg.isWallSliding = true;
                if (contactLeft) nutmeg.wallSide = left; else if (contactRight) nutmeg.wallSide = right; else {
                    // fallback based on previous horizontal move
                    if (nutmeg.speedX >= 0) nutmeg.wallSide = right; else nutmeg.wallSide = left;
                }
                nutmeg.lastWallSide = nutmeg.wallSide;
                nutmeg.wallCoyoteFrames = kWallCoyoteFrames;
            } else {
                if (!touchingAny) {
                    if (nutmeg.wallCoyoteFrames > 0) nutmeg.wallCoyoteFrames--; else nutmeg.isWallSliding = false;
                }
            }
            // Clamp fall speed while sliding
            if (nutmeg.isWallSliding && nutmeg.speedY > wallSlideMaxFallY) {
                nutmeg.speedY = wallSlideMaxFallY;
            }
        } else {
            nutmeg.isWallSliding = false;
            nutmeg.wallCoyoteFrames = 0;
        }

        // Disallow glide while actively wall sliding or during brief post-wall-jump lock
        nutmeg.isGliding = false;
        // Glide while holding A (jump) during a fall
        if (nutmeg.hasbow && KEY_PRESSED(J_A) && nutmeg.speedY > 0 && !nutmeg.isWallSliding && nutmeg.wallJumpGlideLock == 0)
        {
            nutmeg.isGliding = true;
            // this will slow nutmeg down to 1 pixel drop per second
            if (nutmeg.speedY > nutmeg.speeds->fallGlideMaxY){
                nutmeg.speedY = nutmeg.speeds->fallGlideMaxY;
            }
        }
        if (nutmeg.wallJumpGlideLock > 0) nutmeg.wallJumpGlideLock--;

    }

    // Wind handling (from windy levels such as 1-5), applied as acceleration so normal physics still work
    if (windEnabled) {
        if (nutmeg.movestate == inair) {
            if (KEY_PRESSED(J_RIGHT)) {
                nutmeg.speedX += -12;  // still allows forward gain but stronger wind
            } else if (KEY_PRESSED(J_LEFT)) {
                nutmeg.speedX += -60;  // stronger push left
            } else {
                nutmeg.speedX += -28;  // default air push left stronger
            }
        } else { // grounded
            if (KEY_PRESSED(J_RIGHT)) {
                nutmeg.speedX += -8; // still possible to move forward
            } else if (KEY_PRESSED(J_LEFT)) {
                nutmeg.speedX += -14;
            } else {
                // stronger idle drift; use fractional via offset
                nutmeg.offsetX += -12; // ~0.12 px/frame
            }
        }
    }

    /* * * * * * * * * * * * * * * * * * * */
    /*                move                 */
    /* * * * * * * * * * * * * * * * * * * */
    // Move player and check for collisions

        // apply speed to position
    nutmeg.offsetX += nutmeg.speedX;
    nutmeg.offsetY += nutmeg.speedY;

    INT8 delta = MoveX();
    INT8 deltaX_for_wall = delta;
    // Do two movements to get colliders from both directions
    collisionX = TranslateSprite(THIS, delta, 0);
    // 1-tile step-up smoothing: if blocked horizontally and on ground (not swimming), try to climb 1 tile and retry X
    if (collisionX != 0 && nutmeg.movestate == grounded && !(level.isWaterLevel || nutmeg.isSwimming)) {
        UINT8 upCollide = TranslateSprite(THIS, 0, -8);
        if (upCollide == 0) {
            // retry horizontal move after stepping up
            collisionX = TranslateSprite(THIS, delta, 0);
            if (collisionX != 0) {
                // failed to move horizontally; drop back down to original height
                TranslateSprite(THIS, 0, 8);
            } else {
                // success; we are now on top of the 1-tile ledge
                nutmeg.movestate = grounded;
            }
        }
    }
    delta = MoveY();
    collisionY = TranslateSprite(THIS, 0, delta);

    // Dynamic swim detection based on solid water tiles (works in any level)
    DetectSwimmingSolidWater();

    if (level.isWaterLevel || nutmeg.isSwimming)
    {
        nutmeg.speeds = &waterSpeed;
    }
    else
    {
        nutmeg.speeds = &groundSpeed;
        nutmeg.isOnIce = false;
        if ((collisionY >= level.iceTileMin) && (collisionY <= level.iceTileMax))
        {
            nutmeg.speeds = &iceGroundSpeed;
            nutmeg.isOnIce = true;
        }   
    } 
   

    /* * * * * * * * * * * * * * * * * * * */
    /*             X physics               */
    /* * * * * * * * * * * * * * * * * * * */
    // X physics
    // Stop movement if we hit something
    // Otherwise drag
    if (collisionX != 0) {
        nutmeg.speedX = 0;
        // If airborne and not swimming, update wall contact for slide detection
        if (nutmeg.movestate == inair && !(level.isWaterLevel || nutmeg.isSwimming)) {
            if (deltaX_for_wall > 0) { nutmeg.lastWallSide = right; }
            else if (deltaX_for_wall < 0) { nutmeg.lastWallSide = left; }
            if (nutmeg.wallRegrabCooldown == 0) {
                nutmeg.isWallSliding = true;
                nutmeg.wallSide = nutmeg.lastWallSide;
                nutmeg.wallCoyoteFrames = kWallCoyoteFrames;
            }
        }
        if ((level.isSpikeLevel == true) && (collisionX == 2))
        {
            // Get hit!
            nutmeg_hit();
            if (nutmeg.isDying == false)
            {
                // bounce upwards on hit
                nutmeg.speedY = - nutmeg.speeds->fallMaxY;
            }
        }
    }
    else if (!KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT)) 
    {
        if (nutmeg.movestate == grounded)
        {
            if (nutmeg.speedX > 0) {
                INT16 fr = nutmeg.speeds->frictionX;
                if (nutmeg.isInvincible && nutmeg.hurtFlashCounter > 0) fr = fr / 2; // smoother stop after knockback
                if (nutmeg.speedX > fr)
                {
                    nutmeg.speedX -= fr;
                }
                else 
                {
                    nutmeg.speedX = 0;
                }
            }
            else if (nutmeg.speedX < 0) {
                INT16 fr = nutmeg.speeds->frictionX;
                if (nutmeg.isInvincible && nutmeg.hurtFlashCounter > 0) fr = fr / 2;
                if (nutmeg.speedX < -fr) 
                {
                    nutmeg.speedX += fr;
                }
                else 
                {
                    nutmeg.speedX = 0;
                }
            }
        }
        else
        {
            // In air braking; if recently jumped, reduce braking to carry momentum
            INT16 airFric = nutmeg.speeds->airFrictionX;
            if (ice_air_brake_counter > 0) {
                airFric = airFric / 3; // gentler braking window after jump
                if (airFric == 0) airFric = 1;
            }
            // While gliding, stop more quickly when releasing input (tighter landing control)
            if (nutmeg.isGliding) {
                INT16 glideFric = airFric * 2; // stronger braking when gliding
                if (glideFric == 0) glideFric = 1;
                airFric = glideFric;
            }

            if (nutmeg.speedX > 0) {
                if (nutmeg.speedX > airFric)
                {
                    nutmeg.speedX -= airFric;
                }
                else 
                {
                    nutmeg.speedX = 0;
                }
            }
            else if (nutmeg.speedX < 0) {
                if (nutmeg.speedX < -airFric) 
                {
                    nutmeg.speedX += airFric;
                }
                else 
                {
                    nutmeg.speedX = 0;
                }
            }

            if (ice_air_brake_counter > 0) ice_air_brake_counter--;
        }
    }

    /* * * * * * * * * * * * * * * * * * * */
    /*             Y physics               */
    /* * * * * * * * * * * * * * * * * * * */
    // Y physics
    // Drop down if we don't have ground under
    // Play audio on land
    // Start from step sound 6 on land to have start playing stepping audio when we walk quickly
    if (nutmeg.speedY > 0) {
        if (collisionY == 0) {
            nutmeg.movestate = inair;
        }
        else {
            if (nutmeg.movestate == inair) {
                //PlayFx(CHANNEL_4, 4, 0x32, 0x71, 0x73, 0x80);
                nutmeg.movestate = grounded;
                // On landing, clear wall slide state
                nutmeg.isWallSliding = false;
                nutmeg.wallCoyoteFrames = 0;
            }

            nutmeg.speedY =  nutmeg.speeds->fallInitY;
        }
    }
    else {
        nutmeg.movestate = inair;
    }

    // check for up/down spike collisions
    if ((level.isSpikeLevel == true) && (collisionY == 2))
    {
        // Get hit!
        nutmeg_hit();
        if (nutmeg.isDying == false)
        {
            // bounce upwards on hit
            nutmeg.speedY = - nutmeg.speeds->fallMaxY;
        }
    }

	/* * * * * * * * * * * * * * * * * * * */
	/*    clamp to visible screen bounds     */
	/* * * * * * * * * * * * * * * * * * * */
	{
		INT16 screenX = (INT16)THIS->x - (INT16)scroll_x;
		INT16 screenY = (INT16)THIS->y - (INT16)scroll_y;
		const INT16 leftBound = 4;
		const INT16 rightBound = 156; // 160px wide screen
		const INT16 topBound = 8;

		if (screenX < leftBound) {
			THIS->x = (UINT16)((INT16)scroll_x + leftBound);
			nutmeg.offsetX = 0;
			if (nutmeg.speedX < 0) nutmeg.speedX = 0;
			// don't allow wall slide on screen edges
			nutmeg.isWallSliding = false;
			nutmeg.wallCoyoteFrames = 0;
		}
		if (screenX > rightBound) {
			THIS->x = (UINT16)((INT16)scroll_x + rightBound);
			nutmeg.offsetX = 0;
			if (nutmeg.speedX > 0) nutmeg.speedX = 0;
			nutmeg.isWallSliding = false;
			nutmeg.wallCoyoteFrames = 0;
		}
        if (screenY < topBound) {
            THIS->y = (UINT16)((INT16)scroll_y + topBound);
            nutmeg.offsetY = 0;
            nutmeg.speedY = 0;
            nutmeg.jumpPeak = 1;
            nutmeg.movestate = inair;
            nutmeg.isWallSliding = false;
            nutmeg.wallCoyoteFrames = 0;
            collisionY = 1; // treat as ceiling contact for consistent fall behavior
        }
	}


    /* * * * * * * * * * * * * * * * * * * */
    /*      kickback from losing bow       */
    /* * * * * * * * * * * * * * * * * * * */
    if (nutmeg.lostbow == true) {
        if (kickbackcounter < 10) {
            // show hurt frames first
            static const UINT8 anim_hurt_single[] = {1, 11};
            SetSpriteAnim(THIS, anim_hurt_single, 1);
            // keep knockback moving during hurt frames
            if (nutmeg.direction == left) TranslateSprite(THIS, 2, 0); else TranslateSprite(THIS, -2, 0);
            kickbackcounter++;
        }
        else if (kickbackcounter < 25) {
            SetSpriteAnim(THIS, anim_nutmeg_lostbow, 30);

            if (nutmeg.direction == left) {
                TranslateSprite (THIS, 1, 0);
            }
            else if (nutmeg.direction == right) {
                TranslateSprite (THIS, -1, 0);
            }

            kickbackcounter++;
        }
    }

    // Per-frame cooldowns for wall mechanics
    if (nutmeg.wallRegrabCooldown > 0) {
        nutmeg.wallRegrabCooldown--;
    }
}



void Update_SpriteNutmeg(void) 
{
    if (KEY_TICKED(J_SELECT)) {
        grant_bow_powerup();
    }

    if (KEY_TICKED(J_B)) {
        try_throw_acorn();
    }

    if (acorn_throw_cooldown > 0) {
        acorn_throw_cooldown--;
    }

    if (nutmeg.acorns > 99u) {
        nutmeg.acorns = 99u;
    }

    // if we run out of time
	if ((level.hasTimer == true) && (level.timer == 0) && (nutmeg.isDying == false))
    {
        // keep hitting until dead
        nutmeg_hit();
	}


    if (nutmeg.isDying == true)
    {
        // Ensure bow sprite is removed while dying so it doesn't float
        if (spr_nutmegbow) {
            SpriteManagerRemoveSprite(spr_nutmegbow);
            spr_nutmegbow = 0;
        }
        // Start quickdeath once on entering death branch (robust against state hiccups)
        if (deathSongLock == 0) {
            StopMusic;
            __critical { PlayMusic(quickdeath, false); }
            deathSongLock = 1;
            playedQuickdeath = 1;
            if (deathStartSysTime == 0) deathStartSysTime = sys_time;
        }
        // global safety counter to guarantee exit regardless of state
        if (deathHardCounter < 60000) deathHardCounter++;
        // Music trigger handled only at death begin to avoid loops
        // If death was already initialized but state was reset, skip re-init
        if (nutmeg.deathState == 0 && deathHardCounter > 0) {
            nutmeg.deathState = 2;
        }
        // FSM for clean death handling
        if (nutmeg.deathState == 0) {
            nutmeg.deathState = 1;
            nutmeg.deathFrames = 0;
            nutmeg.deathtimer = 0;
            nutmeg.deathSoundPlayed = false;
            deathHardCounter = 0;
            // stop glide/motion carry; ensure death anim plays (already set in begin_death)
            nutmeg.isGliding = false;
            nutmeg.speedX = 0;
            // prevent sprite despawn at bottom while dying
            spr_nutmeg->lim_y = 255;
        }

        if (nutmeg.deathState == 1) {
            // init: visuals already set in begin_death; music already started above
            nutmeg.deathState = 2;
            return;
        }

        if (nutmeg.deathState == 2) {
            // apply gravity and actual movement while dying so Nutmeg falls
            if (nutmeg.speedY < nutmeg.speeds->fallMaxY) {
                nutmeg.speedY += nutmeg.speeds->fallIncY;
            }
            nutmeg.offsetY += nutmeg.speedY;
            INT8 dy = MoveY();
            TranslateSprite(THIS, 0, dy);

            // If far below the screen for long enough, force transition (safety)
            INT16 screenY = (INT16)THIS->y - (INT16)scroll_y;
            if ((screenY > 240) && (nutmeg.deathtimer > 90)) {
                nutmeg.deathState = 3;
            }

            // timer
            if (nutmeg.deathtimer < 250) nutmeg.deathtimer++;
            if (nutmeg.deathFrames < 60000) nutmeg.deathFrames++;
            if (deathHardCounter < 60000) deathHardCounter++;

            // safety transition: allow quickdeath to finish using both frame and vblank timers
            // Exit if either frame-based timers pass threshold, or if >= ~180 vblanks elapsed since start
            if (nutmeg.deathtimer > 180 || nutmeg.deathFrames > 240 || deathHardCounter > 360
                || ((UINT16)(sys_time - deathStartSysTime) > 180)) {
                nutmeg.deathState = 3;
            }
            return;
        }

        if (nutmeg.deathState == 3) {
            levelbeat = false;
            // Losing a life also loses the bow
            nutmeg.hasbow = false;
            nutmeg.lostbow = true;
            bool had_spare_life = (nutmeg.lives > 0);
            if (had_spare_life) {
                nutmeg.lives--;
            }
            StopMusic;
            // restore normal bottom clamp
            spr_nutmeg->lim_y = 144;
            pitDeathLock = 0; // allow future pit deaths next life
            gameStats.totalDeaths++;
            if (!had_spare_life) {
                GameOver = true;
                SetState(StateGameOver);
            } else {
                SetState(StateOverworld);
            }
            return;
        }

        return;
    }

    // palette flash while invincible (very rapid)
    if (nutmeg.isInvincible) {
        if ((nutmeg.hurtFlashCounter & 0x01) == 0) {
            SetPalette(SPRITES_PALETTE, SPRITE_GET_CGB_PALETTE(spr_nutmeg), 1, pal_nutmeg_flash, _current_bank);
        } else {
            // choose appropriate base palette (blue if swimming)
            const UWORD* base = (nutmeg.isSwimming || level.isWaterLevel) ? pal_nutmeg_blue : pal_nutmeg_normal;
            SetPalette(SPRITES_PALETTE, SPRITE_GET_CGB_PALETTE(spr_nutmeg), 1, base, _current_bank);
        }
        if (nutmeg.hurtFlashCounter > 0) nutmeg.hurtFlashCounter--; else {
            nutmeg.isInvincible = false;
            const UWORD* base = (nutmeg.isSwimming || level.isWaterLevel) ? pal_nutmeg_blue : pal_nutmeg_normal;
            SetPalette(SPRITES_PALETTE, SPRITE_GET_CGB_PALETTE(spr_nutmeg), 1, base, _current_bank);
        }
    }

    if (nutmeg.pendingDeath) {
        if (nutmeg.pendingDeathTimer > 0) {
            nutmeg.pendingDeathTimer--;
            update_pending_death_motion(THIS);
            return;
        } else {
            nutmeg.pendingDeath = false;
            nutmeg.isInvincible = false;
            nutmeg_begin_death();
            return;
        }
    }

    /* * * * * * * * * * * * * * * * * * * */
    /*           normal mode               */
    /* * * * * * * * * * * * * * * * * * * */
    if (cutscenemode == disabled)
    {
        // If we just exited the level-start cutscene, clear any residual motion and drop state
        if (lastCutsceneMode == enabled) {
            nutmeg.speedX = 0;
            nutmeg.offsetX = 0;
            ice_air_brake_counter = 0;
            kickbackcounter = 0;
        }
        update_aliveInControl ();
    }
    else
    {
        update_inCutscene();
    }

    // Record current cutscene mode for next frame
    lastCutsceneMode = cutscenemode;

    // Always update bow sprite once per frame while in levels (handles drop animation)
    if (spr_nutmegbow != 0)
    {
        nutmegBow_update();
    }
}

void Destroy_SpriteNutmeg(void) {
    spr_nutmeg = 0;
}

// Called from overworld start to allow next quickdeath in a new life
void nutmeg_allow_next_quickdeath(void) BANKED {
    playedQuickdeath = 0;
    deathSongLock = 0;
    deathStartSysTime = 0;
}

void nutmeg_SetIdlePose(void) BANKED {
    if (!spr_nutmeg) return;
    if (nutmeg.direction == right) {
        SetSpriteAnim(spr_nutmeg, anim_nutmeg_idle_right, 8);
    } else {
        SetSpriteAnim(spr_nutmeg, anim_nutmeg_idle_left, 8);
    }
}

void nutmeg_SetupGame(void) BANKED
{
    //health system
       
    // Starting lives
    nutmeg.lives = 3; 
    nutmeg.acorns = 0;
    nutmeg.goldenAcorns = 0;
  
    nutmeg.isOnIce = false;

    level_playing = 0;
    highest_level_completed = 0;
    for (UINT8 i = 0; i < MAX_LEVEL_TRACKING; ++i) {
        levelCompleted[i] = false;
        levelGoldenCollected[i] = false;
    }

    level_current = 0;
	level_next = 0;
	level_max = 0;
    
    // advance to the first level
    levelbeat = true;

    W1LevelSelection = 0;

    // Start new game without a bow; collect it as a powerup in Level 1
    nutmeg.hasbow = false;
    nutmeg.lostbow = false;
    // reset global stats for a new game
    gameStats.totalAcorns = 0;
    gameStats.totalEnemyKills = 0;
    gameStats.totalDamageTaken = 0;
    gameStats.totalDeaths = 0;
    gameStats.totalLevelsCompleted = 0;
    gameStats.totalPowerups = 0;
    gameStats.totalGoldenAcorns = 0;
    levelGoldenAcornFound = false;
    nutmeg_setupNextLife();
}

// setup variables for the next life
void nutmeg_setupNextLife (void) BANKED
{
    // On life setup, do NOT auto-grant the bow; it must be earned or preserved
    // Health reflects bow state: without a bow, the next hit should kill
    if (nutmeg.hasbow) {
        nutmeg.health = full;
    } else {
        nutmeg.health = low;
    }
    nutmeg.pendingDeath = false;
    nutmeg.pendingDeathTimer = 0;
    // keep current bow state (lose on death handled at death exit)
}

// call this when nutmeg has been hit
void nutmeg_hit(void) BANKED
{
    // Ignore hits during invincibility window
    if (nutmeg.isInvincible) {
        return;
    }

    if (nutmeg.hasbow == true)
    {
        #ifdef USE_CBT_FX
        Sfx_Hurt();
        #endif
        nutmeg.hasbow = false;
        nutmeg.lostbow = true;
        nutmeg.bow_counter = 0;
        if (nutmeg.direction == right) { nutmeg.bowanim = 8; }
        else if (nutmeg.direction == left) { nutmeg.bowanim = 9; }

        // health gets set low after bow loss I guess (this provides some invincibility)
        // play hurt animation briefly
        if (spr_nutmeg) {
            // Use sprite index 11 for hurt (single frame), alternate mirror by facing
            static const UINT8 anim_hurt_single[] = {1, 11};
            SetSpriteAnim(spr_nutmeg, anim_hurt_single, 1);
        }
        // knockback (horizontal only)
        if (nutmeg.direction == left) {
            // facing left means hit came from right -> push right
            nutmeg.speedX = 100;
        } else {
            // facing right means hit came from left -> push left
            nutmeg.speedX = -100;
        }
        // clear friction briefly so knockback is visible
        ice_air_brake_counter = 6;

        // initialize bow drop position so it starts falling from current head offset
        if (spr_nutmegbow) {
            spr_nutmegbow->y = spr_nutmeg->y - 24;
            if (nutmeg.direction == right) {
                spr_nutmegbow->x = spr_nutmeg->x - 8;
                spr_nutmegbow->mirror = NO_MIRROR;
            } else {
                spr_nutmegbow->x = spr_nutmeg->x + 8;
                spr_nutmegbow->mirror = V_MIRROR;
            }
            // allow the bow to fall fully offscreen during drop
            spr_nutmegbow->lim_y = 300;
        }
        // sfx
        PlayFx(CHANNEL_4, 20, 0x3a, 0xf2, 0x62, 0x80);
        // brief invincibility/flash
        nutmeg.isInvincible = true;
        nutmeg.hurtFlashCounter = 45; // extend invincibility for clearer feedback
        kickbackcounter = 0;
        gameStats.totalDamageTaken++;
    }
    else if (nutmeg.health == low) {
        if (nutmeg.pendingDeath || nutmeg.isDying) {
            return;
        }
#ifdef USE_CBT_FX
        Sfx_Hurt();
#endif
        if (spr_nutmeg) {
            static const UINT8 anim_hurt_single[] = {1, 11};
            SetSpriteAnim(spr_nutmeg, anim_hurt_single, 1);
        }
        if (nutmeg.direction == left) {
            nutmeg.speedX = 100;
        } else {
            nutmeg.speedX = -100;
        }
        ice_air_brake_counter = 6;

        nutmeg.isInvincible = true;
        nutmeg.hurtFlashCounter = 45;
        kickbackcounter = 0;
        gameStats.totalDamageTaken++;

        nutmeg.pendingDeath = true;
        nutmeg.pendingDeathTimer = 30;
        nutmeg.speedY = 0;
    }
}

bool nutmeg_isInsideXY(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) BANKED
{
    if ((spr_nutmeg->x > x1)
      && (spr_nutmeg->x < x2)
      && (spr_nutmeg->y > y1)
      && (spr_nutmeg->y < y2))
    {
        return true;
    }
    return false;
}

// WARNING - Not called with THIS pointing to spr_nutmeg
void nutmeg_Animate(void) BANKED
{
    if (nutmeg.isDying == true) {
        return;
    }
   
     /* * * * * * * * * * * * * * * * * * * */
    /*             animation               */
    /* * * * * * * * * * * * * * * * * * * */
    // play correct animation based on current state & input
    // Idle if our movement is zero, or we are sliding and not pressing left or right
    if (nutmeg.movestate == grounded) {
        if (level.isWaterLevel || nutmeg.isSwimming) {
            // if no input and touching ground, gently alternate frames
            if (!KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_A) && !KEY_PRESSED(J_B)) {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_swim, 5);
            } else if (nutmeg.speedY <= 0) SetSpriteAnim(spr_nutmeg, anim_nutmeg_swim_up, 1);
            else SetSpriteAnim(spr_nutmeg, anim_nutmeg_swim_down, 1);
        } else {
            if (((nutmeg.isOnIce == true) && !KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT))
               || (nutmeg.isOnIce == false && nutmeg.speedX < 100 && nutmeg.speedX > -100)) 
            {
                if (nutmeg.direction == right) {
                    SetSpriteAnim(spr_nutmeg, anim_nutmeg_idle_right, 5);
                    nutmeg.bowanim = 0;
                }
                if (nutmeg.direction == left) {
                    SetSpriteAnim(spr_nutmeg, anim_nutmeg_idle_left, 5);
                    nutmeg.bowanim = 1;
                }
            }
            else {
                if (nutmeg.direction == right) {
                    SetSpriteAnim(spr_nutmeg, anim_nutmeg_walk_right, 15);
                    nutmeg.bowanim = 2;
                }
                if (nutmeg.direction == left) {
                    SetSpriteAnim(spr_nutmeg, anim_nutmeg_walk_left, 15);
                    nutmeg.bowanim = 3;
                }
            }
        }
    }
    else if (nutmeg.movestate == inair) {
            if (level.isWaterLevel || nutmeg.isSwimming) {
                if (nutmeg.speedY <= 0) SetSpriteAnim(spr_nutmeg, anim_nutmeg_swim_up, 1);
                else SetSpriteAnim(spr_nutmeg, anim_nutmeg_swim_down, 1);
            }
        if (!(level.isWaterLevel || nutmeg.isSwimming) && nutmeg.isGliding)
        {
            if (nutmeg.direction == right)
            {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_glide, 1);
                nutmeg.bowanim = 11;
            }
            else
            {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_glide, 1);
                nutmeg.bowanim = 12;
            }
        }
        else if (!(level.isWaterLevel || nutmeg.isSwimming) && nutmeg.speedY > 60) {
            if (nutmeg.direction == right) {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_fall_right, 1);
                nutmeg.bowanim = 6;
            }
            if (nutmeg.direction == left) {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_fall_left, 1);
                nutmeg.bowanim = 7;
            }
        }
        else if (!(level.isWaterLevel || nutmeg.isSwimming) && nutmeg.speedY < -60) {
            if (nutmeg.direction == right) {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_jump_right, 1);
                nutmeg.bowanim = 4;
            }
            if (nutmeg.direction == left) {
                SetSpriteAnim(spr_nutmeg, anim_nutmeg_jump_left, 1);
                nutmeg.bowanim = 5;
            }
        }
    }

    // update the bow after we are done updating, so the x & y positions can track us correctly
    if (spr_nutmegbow != 0)
    {
        nutmegBow_update();
    }
}