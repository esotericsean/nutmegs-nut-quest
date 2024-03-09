#include "Banks/SetAutoBank.h"
#include <gb/cgb.h>
#include "ZGBMain.h"
#include "Scroll.h"

#include "../src/GlobalVars.h"

bool showLevelStart;

static const unsigned char StrLevel[] = { 0x54, 0x55, 0x56, 0x57, 0x58};
static const unsigned char StrStart[] = {0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e};

static const unsigned char blank [] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

static const unsigned char LevelStartTiles [] = {
	// L
	0xff,0x00,0xff,0x20,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x1c,
	// e
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x24,0xff,0x38,0xff,0x20,0xff,0x1c, 
	// v
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x44,
	0xff,0x44,0xff,0x28,0xff,0x28,0xff,0x10,
	// e
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x24,0xff,0x38,0xff,0x20,0xff,0x1c, 
	// l
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x38,
	// S
	0xff,0x00,0xff,0x18,0xff,0x24,0xff,0x20,
	0xff,0x18,0xff,0x04,0xff,0x24,0xff,0x18,
	// t
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x78,0xff,0x20,0xff,0x20,0xff,0x1c,
	// a
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x04,0xff,0x1c,0xff,0x24,0xff,0x1a,
	// r
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x20,
	// t
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x78,0xff,0x20,0xff,0x20,0xff,0x1c,
	// !
	0xff,0x00,0xff,0x10,0xff,0x10,0xff,0x10,
	0xff,0x10,0xff,0x10,0xff,0x00,0xff,0x10
};

static UINT8 c = 0;

static UINT8 x = 7;
static UINT8 y = 5;

void LevelStart_Init (UINT8 xstart, UINT8 ystart) BANKED
{
	set_bkg_data (0x54, 11, LevelStartTiles);
    c = 0;
	x = xstart;
	y = ystart;
	showLevelStart = true;
}

static void drawLevelStart(void)
{
	UINT8 *t = (UINT8 *) (0x9800 + x + (y<<5));

	set_vram_byte (t, 0x54);
	t++;
	set_vram_byte (t, 0x55);
	t++;
	set_vram_byte (t, 0x56);
	t++;
	set_vram_byte (t, 0x57);
	t++;
	set_vram_byte (t, 0x58);
	t += 32 - 4;
	set_vram_byte (t, 0x59);
	t++;
	set_vram_byte (t, 0x5a);
	t++;
	set_vram_byte (t, 0x5b);
	t++;
	set_vram_byte (t, 0x5c);
	t++;
	set_vram_byte (t, 0x5d);
	t++;
	set_vram_byte (t, 0x5e);
}

static void drawBlank(void)
{
	UINT8 *t = (UINT8 *) (0x9800 + x + (y<<5));

	set_vram_byte (t, 1);
	t++;
	set_vram_byte (t, 1);
	t++;
	set_vram_byte (t, 1);
	t++;
	set_vram_byte (t, 1);
	t++;
	set_vram_byte (t, 1);
	t += 32 - 4;
	set_vram_byte (t, 1);
	t++;
	set_vram_byte (t, 1);
	t++;
	set_vram_byte (t, 1);
	t++;
	set_vram_byte (t, 1);
	t++;
	set_vram_byte (t, 1);
	t++;
	set_vram_byte (t, 1);

}
void LevelStart_Update(void) BANKED
{
	if (!showLevelStart)
	{
		return;
	}
    c++;
    
    if (c == 10) 
    {
		drawLevelStart();
    }
    else if (c == 40) {
        drawBlank();
    }
    else if (c == 70) {
       	drawLevelStart();
    }
    else if (c == 100) {
        drawBlank();
		showLevelStart = false;
    }
    else {
        // don't advance past 101, if we get called more often 
        c == 101;
    }
}

