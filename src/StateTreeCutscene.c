#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "Palette.h"

#include "../src/GlobalVars.h"
#include "../src/Font.h"

IMPORT_MAP (treemap);

UINT8 collision_tiles_tree[] = {2,3,4,5,7,8,9,10,12,49,50,51,52,53,54,55,56,57,58, 0};

DECLARE_MUSIC(oaktree);

UINT8 cutscenetimer = 0;

static const unsigned char font_blank2[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

static const unsigned char font_upper_M2[] = {
0x00,0x00,0x28,0x28,0x54,0x54,0x54,0x54,
0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44
};

static const unsigned char font_lower_a2[] = {
0x00,0x00,0x00,0x00,0x18,0x18,0x24,0x24,
0x04,0x04,0x1c,0x1c,0x24,0x24,0x1a,0x1a
};

static const unsigned char font_lower_m2[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x28,0x28,
0x54,0x54,0x54,0x54,0x44,0x44,0x44,0x44
};

static const unsigned char font_period2[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20
};

static const unsigned char font_arrow2[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x7c,0x7c,0x38,0x38,0x10,0x10
};

void Start_StateTreeCutscene() {
	//UINT8 i;
	SPRITES_8x16;

	cutscenetimer = 0;

	//nutmeg_direction = left;

	stop_music_on_new_state = 0;
	PlayMusic(oaktree, 1); //name, BANK, volume or speed?
	
	InitScrollTiles(0, &treetiles);
	InitScroll(BANK(treemap), &treemap, collision_tiles_tree, 0);

	cutscenemode = enabled;

	//RESET SO NUTMEG DOESN'T FLY OFF SCREEN
    accelY = 0;
    accelX = 0;
    jumpPeak = 0;
    runJump = 0;
    nutmeg_direction = right;
    movestate = grounded;

	SpriteManagerAdd(SpriteNutmeg, 12*8, 104);
	SpriteManagerAdd(SpriteCinnamon, 36, 96);
	SpriteManagerAdd(SpriteRuby, 36+11, 96);
	SpriteManagerAdd(SpriteMaple, 36+20, 96);

	SHOW_SPRITES;
	SHOW_BKG;

}

void Update_StateTreeCutscene() {
	//if you press START at any point of this opening cutscene it jumps to the next cutscene
	if (KEY_PRESSED(J_START)) {
		//set variable for first time entering overworld1
        SetState(StateCutscene1);
    }

	if (cutscenetimer >= 0 && cutscenetimer < 2) {
		cutscenewalkleft = true;
		cutscenewalkright = false;
	}
	else if (cutscenetimer >= 2 && cutscenetimer < 50) {
		cutscenewalkleft = false;
		cutscenewalkright = false;
	}
	else if (cutscenetimer == 50) set_bkg_data (0x43, 1, font_upper_M2);
	else if (cutscenetimer == 55) set_bkg_data (0x44, 1, font_lower_a2);
	else if (cutscenetimer == 60) set_bkg_data (0x45, 1, font_lower_m2);
	else if (cutscenetimer == 65) set_bkg_data (0x46, 1, font_lower_a2);
	else if (cutscenetimer == 70) set_bkg_data (0x47, 1, font_period2);
	else if (cutscenetimer == 75) set_bkg_data (0x48, 1, font_period2);
	else if (cutscenetimer == 80) set_bkg_data (0x49, 1, font_period2);
	else if (cutscenetimer == 85) set_bkg_data (0x6C, 1, font_arrow2);
	else if (cutscenetimer == 105) set_bkg_data (0x6C, 1, font_blank2);

	//need to figure out how to detect pressing A while "stuck" in the arrow loop here

	cutscenetimer++;

	if (cutscenetimer == 125) cutscenetimer = 85;
	if (KEY_PRESSED(J_A) && cutscenetimer >= 85 && cutscenetimer < 125)
	{ 
		cutscenetimer = 126;
	}

	if (cutscenetimer >= 126 && cutscenetimer < 146) {
		cutscenewalkleft = true;
		cutscenewalkright = false;
	}

	else if (cutscenetimer >= 156) SetState(StateCutscene1);
}