#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "GlobalVars.h"

// Short twinkle burst shown when an acorn is collected.
// Timing lives in JuiceConfig.h (pulled in via GlobalVars.h).

static const UINT8 anim_sparkle[] = {4, 0, 1, 2, 3};

#define SPARKLE_AGE 0

void Start_SpriteSparkle(void) {
	THIS->mirror = NO_MIRROR;
	// spread the 4 frames across the whole lifetime
	// (ZGB advances a frame each time anim_speed accumulates past 100)
	SetSpriteAnim(THIS, anim_sparkle, (UINT8)(400 / JUICE_SPARKLE_LIFETIME) + 1);
	THIS->custom_data[SPARKLE_AGE] = 0;
}

void Update_SpriteSparkle(void) {
	if (THIS->custom_data[SPARKLE_AGE] >= JUICE_SPARKLE_LIFETIME) {
		SpriteManagerRemoveSprite(THIS);
		return;
	}
	THIS->custom_data[SPARKLE_AGE]++;

#if JUICE_SPARKLE_RISE_EVERY > 0
	if ((THIS->custom_data[SPARKLE_AGE] % JUICE_SPARKLE_RISE_EVERY) == 0) {
		THIS->y--;
	}
#endif
}

void Destroy_SpriteSparkle(void) {
}
