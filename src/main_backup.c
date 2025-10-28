#include "main.h"

#include <gb/gb.h> 
#include <string.h>

#include "OAMManager.h"
#include "Scroll.h"
#include "Keys.h"
#include "Music.h"
#include "SpriteManager.h"
#include "BankManager.h"
#include "Fade.h"
#include "Palette.h"
#include "Sfx.h"
#include "SfxChain.h"
#ifdef USE_CBT_FX
#include "third_party/cbtfx/include/cbtfx.h"
#endif

// --- Minimal frame-gated SFX chain (no banks, no pointers) ---
typedef struct {
    UINT8 active;
    UINT8 step;
    UINT8 timer;
    UINT8 period;
    UINT8 which; // 1=pauseUp,2=pauseDown,3=oneUp,4=bow
} SfxChainT;
static SfxChainT sfxChain;

void SfxChain_Start(UINT8 which, UINT8 period) {
    sfxChain.active = 1; sfxChain.step = 0; sfxChain.timer = 0; sfxChain.period = period; sfxChain.which = which;
}

static void SfxChain_Tick(void) {
    if (!sfxChain.active) return;
    if (sfxChain.timer) { sfxChain.timer--; return; }
    // sequences use CH1: len, sweep, duty, env, freq
    if (sfxChain.which == 1) { // pause up: longer notes
        switch (sfxChain.step++) {
            case 0: PlayFx(CHANNEL_2, 10, 0x00, 0x1C, 0x96, 0xA0, 0x86); break;
            case 1: PlayFx(CHANNEL_2, 10, 0x00, 0x1C, 0x96, 0xA8, 0x86); break;
            case 2: PlayFx(CHANNEL_2, 12, 0x00, 0x1C, 0x96, 0xB0, 0x86); sfxChain.active = 0; break;
        }
    } else if (sfxChain.which == 2) { // pause down: longer notes
        switch (sfxChain.step++) {
            case 0: PlayFx(CHANNEL_2, 10, 0x00, 0x1C, 0x96, 0xB0, 0x86); break;
            case 1: PlayFx(CHANNEL_2, 10, 0x00, 0x1C, 0x96, 0xA8, 0x86); break;
            case 2: PlayFx(CHANNEL_2, 12, 0x00, 0x1C, 0x96, 0xA0, 0x86); sfxChain.active = 0; break;
        }
    } else if (sfxChain.which == 3) { // one-up: C-E-G-C'
        switch (sfxChain.step++) {
            case 0: PlayFx(CHANNEL_1, 10, 0x10, 0xC7, 0xE4, 0x9C, 0x86); break;
            case 1: PlayFx(CHANNEL_1, 10, 0x10, 0xC7, 0xE4, 0xA6, 0x86); break;
            case 2: PlayFx(CHANNEL_1, 10, 0x10, 0xC7, 0xE4, 0xB0, 0x86); break;
            case 3: PlayFx(CHANNEL_1, 14, 0x10, 0xC7, 0xE4, 0xBC, 0x86); sfxChain.active = 0; break;
        }
    } else if (sfxChain.which == 4) { // bow: 3-note twinkle
        switch (sfxChain.step++) {
            case 0: PlayFx(CHANNEL_1, 10, 0x10, 0xC7, 0xE4, 0xA2, 0x86); break;
            case 1: PlayFx(CHANNEL_1, 10, 0x10, 0xC7, 0xE4, 0xAC, 0x86); break;
            case 2: PlayFx(CHANNEL_1, 14, 0x10, 0xC7, 0xE4, 0xB6, 0x86); sfxChain.active = 0; break;
        }
    }
    sfxChain.timer = sfxChain.period;
}
#include <gb/cgb.h>

#include "ZGBMain.h"

#include "GlobalVars.h"

#ifdef USE_SAVEGAME
	#include "savegame.h"
#endif

// in scroll.h - used to adjust the window when we pause
extern INT8 scroll_h_border;

extern UINT8 next_state;

UINT8 delta_time;
UINT8 current_state;
UINT8 state_running = 0;

UINT8 backgroundoffsetmain = 0;

void SetState(UINT8 state) {
	state_running = 0;
	next_state = state;
}

UINT8 vbl_count = 0;
UINT8 music_mute_frames = 0;

void vbl_update(void) {
	vbl_count ++;
	
	SCX_REG = scroll_x_vblank + (scroll_offset_x << 3);
	SCY_REG = scroll_y_vblank + (scroll_offset_y << 3);

	if(music_mute_frames != 0) {
		music_mute_frames --;
		if(music_mute_frames == 0) {
			UNMUTE_ALL_CHANNELS;
		}
	}
}

void InitStates(void);
void InitSprites(void);

extern UWORD ZGB_Fading_BPal[32];
extern UWORD ZGB_Fading_SPal[32];
#ifdef CGB	
void SetPalette(PALETTE_TYPE t, UINT8 first_palette, UINT8 nb_palettes, UINT16 *rgb_data, UINT8 bank) {
	if(first_palette + nb_palettes > 8)
		return; //Adding more palettes than supported

	UWORD* pal_ptr = (t == BG_PALETTE) ? ZGB_Fading_BPal : ZGB_Fading_SPal;
	PUSH_BANK(bank);
	if(t == BG_PALETTE) {
		set_bkg_palette(first_palette, nb_palettes, rgb_data);
	} else {
		set_sprite_palette(first_palette, nb_palettes, rgb_data);
	}
	memcpy(&pal_ptr[first_palette << 2], rgb_data, nb_palettes << 3);
	POP_BANK();
}
#endif

void LCD_Title_isr(void) NONBANKED{
	switch (LYC_REG)
		{
        case 0x00:
            LYC_REG = 0x48;
            break;
        case 0x48:
            move_bkg(backgroundoffsetmain,0);
            LYC_REG = 0x60;
            break;
        case 0x60:
			move_bkg(0,0);
            LYC_REG = 0x00;
            break;            
		}
}

void LCD_NoSpritesOnHUD_isr(void) NONBANKED {
	// turn sprites off over the window
	if (LYC_REG == 0) {
		if (WY_REG == 0) {
			HIDE_SPRITES;
		} else {
			SHOW_SPRITES;
			LYC_REG = WY_REG; // was  - 1;
		}
	} else {
		HIDE_SPRITES;
		LYC_REG = 0;
	}
}

extern UINT8 last_bg_pal_loaded;
extern UINT8 last_tile_loaded;
static const UINT16 default_palette[] = {RGB(31, 31, 31), RGB(20, 20, 20), RGB(10, 10, 10), RGB(0, 0, 0)};

void main(void) {
	// this delay is required for PAL SNES SGB border commands to work
	for (UINT8 i = 4; i != 0; i--) {
		wait_vbl_done();
	}

#ifdef USE_SAVEGAME
	CheckSRAMIntegrity((UINT8*)&savegame, sizeof(Savegame));
#endif

#ifdef CGB
	UINT8 i;
	cpu_fast();
#endif
	INIT_MUSIC;

	PUSH_BANK(1);
	InitStates();
	InitSprites();
	POP_BANK();
	
	CRITICAL {
#ifdef CGB
		// turn on the double speed cpu, as there seem to be sone performance issues
 		//cpu_fast();
		TMA_REG = _cpu == CGB_TYPE ? 120U : 0xBCU;
#else
		TMA_REG = 0xBCU;
#endif
		TAC_REG = 0x04U;
		//Instead of calling add_TIM add_low_priority_TIM is used because it can be interrupted. This fixes a random
		//bug hiding sprites under the window (some frames the call is delayed and you can see sprites flickering under the window)
		add_low_priority_TIM(MusicCallback); 
		                          
		add_VBL(vbl_update);
	}

	set_interrupts(VBL_IFLAG | TIM_IFLAG | LCD_IFLAG);
	
	STAT_REG |= 0x40; 
	LCDC_REG |= LCDCF_OBJDEFAULT | LCDCF_OBJON | LCDCF_BGON;
	WY_REG = 145;

	// FOR TEST - Skip past the start stuff
	
	// 6 = force scroll
	// w1 = 10 - stage 8
	W1LevelSelection = 0;
	next_state = StateInitGame;
	levelbeat = true;
	level_max = 1;
	level_current = 0;
	level_next = 1;
	nutmeg.lives = 99;
	add_LCD (LCD_NoSpritesOnHUD_isr);
	// END FOR TEST
	

	while(1) {
		DISPLAY_OFF

		if (current_state == 2)	
		{
			remove_LCD(LCD_Title_isr);
			add_LCD (LCD_NoSpritesOnHUD_isr);
		}

		if(stop_music_on_new_state)
		{
			StopMusic;
		}

		SpriteManagerReset();
		state_running = 1;
		current_state = next_state;
		scroll_target = 0;
		last_bg_pal_loaded = 0;
		last_tile_loaded = 0;
		
#ifdef CGB
		if (_cpu == CGB_TYPE) {
			for(i = 0; i < 8; ++ i)
			{
				SetPalette(BG_PALETTE, i, 1, default_palette, 1);
				SetPalette(SPRITES_PALETTE, i, 1, default_palette, 1);
			}
		} else 
#endif
		BGP_REG = OBP0_REG = OBP1_REG = PAL_DEF(0, 1, 2, 3);

		PUSH_BANK(stateBanks[current_state]);
			(startFuncs[current_state])();
		POP_BANK();
		scroll_x_vblank = scroll_x;
		scroll_y_vblank = scroll_y;

		if(state_running) {
			if (current_state == 2)	
			{
				remove_LCD (LCD_NoSpritesOnHUD_isr);
				add_LCD (LCD_Title_isr);
			}

			// FadeOut (from white to our real colors)
			// This takes a second, so update the sprite manager one time,
			// so our starting sprites are on the screne during the fade
            SpriteManagerUpdate();
            SfxChain_Tick();
#ifdef USE_CBT_FX
            __critical { CBTFX_update(); }
#endif
			DISPLAY_ON;
			FadeOut();
		}

		while (state_running) {
		
			if(!vbl_count)
			{
				wait_vbl_done();
			}
			delta_time = vbl_count == 1u ? 0u : 1u;
			vbl_count = 0;

                UPDATE_KEYS();
                SfxChain_Tick();
#ifdef USE_CBT_FX
                __critical { CBTFX_update(); }
#endif
			
			if (isPaused == true)
			{
				// While paused, allow Select to return to overworld if replaying a beaten level
				if (KEY_PRESSED(J_SELECT))
				{
					if ((level_current < level_max) && (state_running))
					{
						isPaused = false;
						rWY = 144-8;
						SetState(StateOverworld);
						continue;
					}
				}
				if (KEY_TICKED(J_START))	
				{
					isPaused = false;
					rWY = 144-8;
				}
			}
			else
			{
				// Do not touch music here; states control PlayMusic on unpause. This prevents rogue tones during pause.
				SpriteManagerUpdate();
				PUSH_BANK(stateBanks[current_state]);
					updateFuncs[current_state]();
				POP_BANK();
			}
		}

		FadeIn();
	}
}

