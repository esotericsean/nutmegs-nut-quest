#ifndef JUICE_CONFIG_H
#define JUICE_CONFIG_H

// Central tuning for all "game feel" effects.
// Every value can be tweaked here without touching gameplay logic;
// setting a value to 0 disables that effect entirely.

// --- Jump forgiveness -------------------------------------------------------
// Frames after walking off a ledge during which a jump still fires (0 = off)
#define JUICE_COYOTE_FRAMES        6
// Frames a jump press is remembered before landing (0 = off)
#define JUICE_JUMP_BUFFER_FRAMES   6

// --- Landing feedback -------------------------------------------------------
// Minimum downward speed (same units as nutmeg.speedY) required for
// landing dust + thud (0 = every landing)
#define JUICE_LAND_FX_MIN_SPEEDY   250

// --- Screen shake -----------------------------------------------------------
// Durations in frames (0 = off). Amplitude is fixed at 1 px, alternating.
#define JUICE_SHAKE_DEATH_FRAMES   8
#define JUICE_SHAKE_BOSSHIT_FRAMES 4

// --- Hit-stop (freeze frames) -----------------------------------------------
// Global gameplay freeze in frames (0 = off). Music keeps playing.
#define JUICE_HITSTOP_STOMP_FRAMES 2
#define JUICE_HITSTOP_HURT_FRAMES  3

// --- SFX pitch variation ----------------------------------------------------
// Max +/- nudge applied to the 11-bit CH2 frequency for "varied" sounds
// (0 = off; keep it a power of two; 16 is roughly up to a semitone)
#define JUICE_PITCH_VAR_RANGE      16

// --- Pickup sparkle ---------------------------------------------------------
// Frames before the sparkle removes itself
#define JUICE_SPARKLE_LIFETIME     24
// Sparkle rises 1 px every N frames (0 = no rise)
#define JUICE_SPARKLE_RISE_EVERY   2

// --- Squash & stretch -------------------------------------------------------
// Frames to hold the stretch pose on jump / squash pose on landing (0 = off).
// The pose is sprite-only; the hitbox never changes.
// Squash currently uses the existing (previously unused) landing pose,
// frame 11. When dedicated squash/stretch art is drawn in GBTD, point the
// _IDX defines at the new frames and set the hold times as desired.
#define JUICE_STRETCH_FRAMES       0   // jump pose (frame 9) already shows while rising
#define JUICE_SQUASH_FRAMES        5
// Frame indices inside the Nutmeg sprite GBR for the poses
#define JUICE_STRETCH_FRAME_IDX    9
#define JUICE_SQUASH_FRAME_IDX     11

#endif
