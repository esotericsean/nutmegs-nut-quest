#include "Banks/SetAutoBank.h"
#include <gb/cgb.h>
#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Music.h"
#include "Keys.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "Sound.h"

IMPORT_MAP (scrollmap);
DECLARE_MUSIC (chase);

volatile UINT8 next_interrupt_ly;
volatile UINT8 backgroundoffset;
extern void LCD_isr();

void interruptLCD() {
    switch (next_interrupt_ly) {
        case 0x00:
            LYC_REG = next_interrupt_ly = 0x48; //pixel 72 (0x48)
            move_bkg (0, 0);
            break;
        case 0x48:
            LYC_REG = next_interrupt_ly = 0x60; //pixel 96 (0x60)
            move_bkg (backgroundoffset, 0);
            break;
        case 0x60:
            LYC_REG = next_interrupt_ly = 0x00;
            move_bkg (0, 0);
            break;
    }
}

void Start_StateScroll() {
    PlayMusic(chase, 1);

    backgroundoffset = 0;
    
    __critical {
        add_LCD (interruptLCD);
        STAT_REG |= 0x40;
        LYC_REG = 160u;
    }

    InitScrollTiles (0, &scrolltiles);
    InitScroll (BANK(scrollmap), &scrollmap, 0, 0);
}

void Update_StateScroll() {
    backgroundoffset += 1;
       
    if (KEY_PRESSED(J_START)) {
        __critical {
            remove_LCD (interruptLCD);
            STAT_REG -= 0x40;
        }

        SetState (StateTreeCutscene);
    }
}