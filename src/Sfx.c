#include <gbdk/platform.h>
#include "Sound.h"
#include "Sfx.h"

#ifdef USE_CBT_FX
#include "third_party/cbtfx/cbtfx.h"
extern const unsigned char CBTFX_SFX_Jump[];
extern const UINT8 CBTFX_SFX_Jump_Len;
#include "BankManager.h"
BANKREF_EXTERN(CBTFX_SFX_Jump)
// Staging player
void Sfx_Cbtfx_PlayFromBanked(const unsigned char *sfx_ptr, UINT8 sfx_len, UINT8 bank);

// Additional SFX
extern const unsigned char CBTFX_SFX_Pickup[];
extern const UINT8 CBTFX_SFX_Pickup_Len;
BANKREF_EXTERN(CBTFX_SFX_Pickup)
extern const unsigned char CBTFX_SFX_Stomp[];
extern const UINT8 CBTFX_SFX_Stomp_Len;
BANKREF_EXTERN(CBTFX_SFX_Stomp)
extern const unsigned char CBTFX_SFX_WaterSplash[];
extern const UINT8 CBTFX_SFX_WaterSplash_Len;
BANKREF_EXTERN(CBTFX_SFX_WaterSplash)
extern const unsigned char CBTFX_SFX_WaterStroke[];
extern const UINT8 CBTFX_SFX_WaterStroke_Len;
BANKREF_EXTERN(CBTFX_SFX_WaterStroke)
#endif

static void sfx_play_cbtfx_default(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(CBTFX_SFX_Jump, CBTFX_SFX_Jump_Len, BANK(CBTFX_SFX_Jump));
#endif
}

void Sfx_Jump(void) {
#ifdef USE_CBT_FX
	sfx_play_cbtfx_default();
#else
	PlayFx(CHANNEL_1, 10, 0x17, 0x9F, 0xF3, 0xC9, 0xC4);
#endif
}

void Sfx_Pickup(void) {
#ifdef USE_CBT_FX
	Sfx_Cbtfx_PlayFromBanked(CBTFX_SFX_Pickup, CBTFX_SFX_Pickup_Len, BANK(CBTFX_SFX_Pickup));
#else
	PlayFx(CHANNEL_1, 10, 0x17, 0x9F, 0xF2, 0xCD, 0x20);
#endif
}

void Sfx_Stomp(void) {
#ifdef USE_CBT_FX
	Sfx_Cbtfx_PlayFromBanked(CBTFX_SFX_Stomp, CBTFX_SFX_Stomp_Len, BANK(CBTFX_SFX_Stomp));
#else
	PlayFx(CHANNEL_4, 6, 0x1F, 0xA4, 0x00, 0xC0, 0xA3);
#endif
}

void Sfx_Hurt(void) {
#ifdef USE_CBT_FX
	sfx_play_cbtfx_default();
#else
	PlayFx(CHANNEL_4, 10, 0x30, 0xF1, 0x62, 0x80);
#endif
}

void Sfx_UIClick(void) {
#ifdef USE_CBT_FX
	sfx_play_cbtfx_default();
#else
	PlayFx(CHANNEL_4, 6, 0x20, 0x91, 0x40, 0x80);
#endif
}

void Sfx_WaterEnter(void) {
#ifdef USE_CBT_FX
	Sfx_Cbtfx_PlayFromBanked(CBTFX_SFX_WaterSplash, CBTFX_SFX_WaterSplash_Len, BANK(CBTFX_SFX_WaterSplash));
#else
	PlayFx(CHANNEL_4, 8, 0x1F, 0x96, 0x00, 0xC0, 0x25);
#endif
}

void Sfx_WaterExit(void) {
#ifdef USE_CBT_FX
	Sfx_Cbtfx_PlayFromBanked(CBTFX_SFX_WaterSplash, CBTFX_SFX_WaterSplash_Len, BANK(CBTFX_SFX_WaterSplash));
#else
	PlayFx(CHANNEL_4, 8, 0x1F, 0x96, 0x00, 0xC0, 0x25);
#endif
}

void Sfx_WaterStroke(void) {
#ifdef USE_CBT_FX
	Sfx_Cbtfx_PlayFromBanked(CBTFX_SFX_WaterStroke, CBTFX_SFX_WaterStroke_Len, BANK(CBTFX_SFX_WaterStroke));
#else
	PlayFx(CHANNEL_1, 12, 0x3F, 0x5F, 0xC3, 0xC4, 0x90);
#endif
}

void Sfx_BalloonPop(void) {
#ifdef USE_CBT_FX
	sfx_play_cbtfx_default();
#else
	PlayFx(CHANNEL_4, 8, 0x20, 0xE1, 0x40, 0x80);
#endif
}

void Sfx_PauseOpen(void) {
#ifdef USE_CBT_FX
	sfx_play_cbtfx_default();
#else
	PlayFx(CHANNEL_1, 3, 0x10, 0xC7, 0xE3, 0xA0, 0x86);
#endif
}

void Sfx_PauseClose(void) {
#ifdef USE_CBT_FX
	sfx_play_cbtfx_default();
#else
	PlayFx(CHANNEL_1, 3, 0x10, 0xC7, 0xE3, 0x9A, 0x86);
#endif
}
