#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "../src/GlobalVars.h"

IMPORT_MAP (creditsmap);
DECLARE_MUSIC (credits);

UINT8 anim_water_counterc = 0;

const UINT8 collision_tiles_levelc[] = {0};
const UINT8 collision_tiles_down_levelc[] = {0};

extern Sprite * spr_camera;

//water tiles are stored in 1A, 1B, and 1C
//in GBTD, water is 26, 27, 28
const unsigned char levelc_water1[] = {
	0x00,0x08,0x08,0x3c,0x3c,0xff,0xff,0xfb,
	0xff,0xdf,0xf7,0xff,0x7f,0xff,0xfd,0xff
};
const unsigned char levelc_water2[] = {
	0x00,0x20,0x20,0xf3,0xf3,0xff,0xff,0xff,
	0xdf,0xff,0xff,0xf7,0x7f,0xff,0xfd,0xff
};
const unsigned char levelc_water3[] = {
	0x00,0x82,0x82,0xcf,0xcf,0xff,0xff,0xfb,
	0xdf,0xff,0xff,0xf7,0x7f,0xff,0xfd,0xff
};

//water anim data locations
const unsigned char levelc_water_anim1[] = { 0x1A };
const unsigned char levelc_water_anim2[] = { 0x1B };
const unsigned char levelc_water_anim3[] = { 0x1C };

void START() {
	levelorientation = vertical;

	//PlayMusic(quickstart, 1);
	
	scroll_target = spr_camera = SpriteManagerAdd(SpriteCamera, 1, 100);

	InitScrollTiles (0, &creditstiles);
	InitScroll (BANK(creditsmap), &creditsmap, collision_tiles_levelc, collision_tiles_down_levelc);

	isAcornMoving = true;
	SpriteManagerAdd (SpriteAcorn, 5*8, 6*8);

	PlayMusic(credits, 1);
}

void UPDATE() {
	if (KEY_PRESSED (J_DOWN) && spr_camera->y < 800) { TranslateSprite (spr_camera, 0, 1); }
	else if (KEY_PRESSED (J_UP) && spr_camera->y > 0) { TranslateSprite (spr_camera, 0, -1); }

	if (KEY_PRESSED (J_START)) { SetState (StateTitle); }

	//animate water
	if (anim_water_counterc >= 0 && anim_water_counterc < 10) {
		set_bkg_data (0x1A, 1, levelc_water1);
		set_bkg_data (0x1B, 1, levelc_water2);
		set_bkg_data (0x1C, 1, levelc_water3);
	}
	else if (anim_water_counterc >= 10 && anim_water_counterc < 20) {
		set_bkg_data (0x1A, 1, levelc_water2);
		set_bkg_data (0x1B, 1, levelc_water3);
		set_bkg_data (0x1C, 1, levelc_water1);
	}
	else if (anim_water_counterc >= 20 && anim_water_counterc < 30) {
		set_bkg_data (0x1A, 1, levelc_water3);
		set_bkg_data (0x1B, 1, levelc_water1);
		set_bkg_data (0x1C, 1, levelc_water2);
	}
	anim_water_counterc++;
	if (anim_water_counterc >= 30) anim_water_counterc = 0;
}

void DESTROY() { }