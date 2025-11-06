#include <gbdk/platform.h>
#include "Sound.h"
#include "Sfx.h"

#ifdef USE_CBT_FX
#include "third_party/cbtfx/cbtfx.h"
extern const unsigned char CBTFX_SFX_Jump[];
extern const UINT16 CBTFX_SFX_Jump_Len;
#include "BankManager.h"
BANKREF_EXTERN(CBTFX_SFX_Jump)
// Staging player
void Sfx_Cbtfx_PlayFromBanked(const unsigned char *sfx_ptr, UINT16 sfx_len, UINT8 bank);

// Additional SFX from hammeredfx export (banked arrays)
extern const unsigned char SFX_00[]; extern const UINT16 SFX_00_Len; BANKREF_EXTERN(SFX_00)
extern const unsigned char SFX_02[]; extern const UINT16 SFX_02_Len; BANKREF_EXTERN(SFX_02)
extern const unsigned char SFX_03[]; extern const UINT16 SFX_03_Len; BANKREF_EXTERN(SFX_03)
extern const unsigned char SFX_05[]; extern const UINT16 SFX_05_Len; BANKREF_EXTERN(SFX_05)
extern const unsigned char SFX_06[]; extern const UINT16 SFX_06_Len; BANKREF_EXTERN(SFX_06)
extern const unsigned char SFX_08[]; extern const UINT16 SFX_08_Len; BANKREF_EXTERN(SFX_08)
extern const unsigned char SFX_0A[]; extern const UINT16 SFX_0A_Len; BANKREF_EXTERN(SFX_0A)
extern const unsigned char SFX_0B[]; extern const UINT16 SFX_0B_Len; BANKREF_EXTERN(SFX_0B)
extern const unsigned char SFX_0C[]; extern const UINT16 SFX_0C_Len; BANKREF_EXTERN(SFX_0C)
extern const unsigned char SFX_0D[]; extern const UINT16 SFX_0D_Len; BANKREF_EXTERN(SFX_0D)
extern const unsigned char SFX_0E[]; extern const UINT16 SFX_0E_Len; BANKREF_EXTERN(SFX_0E)
extern const unsigned char SFX_0F[]; extern const UINT16 SFX_0F_Len; BANKREF_EXTERN(SFX_0F)
extern const unsigned char SFX_10[]; extern const UINT16 SFX_10_Len; BANKREF_EXTERN(SFX_10)
extern const unsigned char SFX_11[]; extern const UINT16 SFX_11_Len; BANKREF_EXTERN(SFX_11)
extern const unsigned char SFX_12[]; extern const UINT16 SFX_12_Len; BANKREF_EXTERN(SFX_12)
extern const unsigned char SFX_13[]; extern const UINT16 SFX_13_Len; BANKREF_EXTERN(SFX_13)
extern const unsigned char SFX_14[]; extern const UINT16 SFX_14_Len; BANKREF_EXTERN(SFX_14)
#endif

static void sfx_play_cbtfx_default(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(CBTFX_SFX_Jump, CBTFX_SFX_Jump_Len, BANK(CBTFX_SFX_Jump));
#endif
}

void Sfx_Jump(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_0E, SFX_0E_Len, BANK(SFX_0E));
#else
	PlayFx(CHANNEL_1, 10, 0x17, 0x9F, 0xF3, 0xC9, 0xC4);
#endif
}

void Sfx_Pickup(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_0B, SFX_0B_Len, BANK(SFX_0B));
#else
	PlayFx(CHANNEL_1, 10, 0x17, 0x9F, 0xF2, 0xCD, 0x20);
#endif
}

void Sfx_Stomp(void) {
#ifdef USE_CBT_FX
    static UINT8 alt;
    if (alt ^= 1) {
        Sfx_Cbtfx_PlayFromBanked(SFX_00, SFX_00_Len, BANK(SFX_00));
    } else {
        Sfx_Cbtfx_PlayFromBanked(SFX_06, SFX_06_Len, BANK(SFX_06));
    }
#else
	PlayFx(CHANNEL_4, 6, 0x1F, 0xA4, 0x00, 0xC0, 0xA3);
#endif
}

void Sfx_MegaStomp(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_05, SFX_05_Len, BANK(SFX_05));
#endif
}

void Sfx_Hurt(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_08, SFX_08_Len, BANK(SFX_08));
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
    Sfx_Cbtfx_PlayFromBanked(SFX_0C, SFX_0C_Len, BANK(SFX_0C));
#else
	PlayFx(CHANNEL_4, 8, 0x1F, 0x96, 0x00, 0xC0, 0x25);
#endif
}

void Sfx_WaterExit(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_0D, SFX_0D_Len, BANK(SFX_0D));
#else
	PlayFx(CHANNEL_4, 8, 0x1F, 0x96, 0x00, 0xC0, 0x25);
#endif
}

void Sfx_WaterStroke(void) {
#ifdef USE_CBT_FX
	extern UINT16 sys_time;
	static UINT16 last_t = 0;
	UINT16 now = sys_time;
	if ((UINT16)(now - last_t) >= 2) {
        Sfx_Cbtfx_PlayFromBanked(SFX_0A, SFX_0A_Len, BANK(SFX_0A));
		last_t = now;
	}
#else
	PlayFx(CHANNEL_1, 12, 0x3F, 0x5F, 0xC3, 0xC4, 0x90);
#endif
}

void Sfx_BalloonPop(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_12, SFX_12_Len, BANK(SFX_12));
#else
	PlayFx(CHANNEL_4, 8, 0x20, 0xE1, 0x40, 0x80);
#endif
}

void Sfx_PauseOpen(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_03, SFX_03_Len, BANK(SFX_03));
#else
	PlayFx(CHANNEL_1, 3, 0x10, 0xC7, 0xE3, 0xA0, 0x86);
#endif
}

void Sfx_PauseClose(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_03, SFX_03_Len, BANK(SFX_03));
#else
	PlayFx(CHANNEL_1, 3, 0x10, 0xC7, 0xE3, 0x9A, 0x86);
#endif
}

void Sfx_OneUp(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_02, SFX_02_Len, BANK(SFX_02));
#else
	SfxChain_Start(3, 2);
#endif
}

void Sfx_BowPickup(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_13, SFX_13_Len, BANK(SFX_13));
#else
	SfxChain_Start(4, 2);
#endif
}

void Sfx_MushroomBounce(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_0F, SFX_0F_Len, BANK(SFX_0F));
#endif
}

void Sfx_GemBounce(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_10, SFX_10_Len, BANK(SFX_10));
#endif
}

void Sfx_Lightning(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_11, SFX_11_Len, BANK(SFX_11));
#endif
}

void Sfx_DoorEnter(void) {
#ifdef USE_CBT_FX
    Sfx_Cbtfx_PlayFromBanked(SFX_14, SFX_14_Len, BANK(SFX_14));
#endif
}
