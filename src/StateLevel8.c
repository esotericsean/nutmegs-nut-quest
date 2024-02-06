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
#include "FlagPole.h"
#include "Water.h"

IMPORT_MAP (level8map);
IMPORT_MAP (hud);

UINT16 level8counter = 0;
UINT8 endlevel_counter8 = 0;

const UINT8 collision_tiles_level8[] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,95,96,97,98, 0};
const UINT8 collision_tiles_down_level8[] = {29,30,31,32,0};

DECLARE_MUSIC(quickstart);
DECLARE_MUSIC(mushrooms);
DECLARE_MUSIC(quickdeath);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_camera;

//Level Start! Text
const unsigned char UpperL8[] = {
	0xff,0x00,0xff,0x20,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerE8[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x24,0xff,0x38,0xff,0x20,0xff,0x1c
};
const unsigned char LowerV8[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x44,
	0xff,0x44,0xff,0x28,0xff,0x28,0xff,0x10
};
const unsigned char LowerL8[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x38
};
const unsigned char UpperS8[] = {
	0xff,0x00,0xff,0x18,0xff,0x24,0xff,0x20,
	0xff,0x18,0xff,0x04,0xff,0x24,0xff,0x18
};
const unsigned char LowerT8[] = {
	0xff,0x00,0xff,0x00,0xff,0x20,0xff,0x20,
	0xff,0x78,0xff,0x20,0xff,0x20,0xff,0x1c
};
const unsigned char LowerA8[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x04,0xff,0x1c,0xff,0x24,0xff,0x1a
};
const unsigned char LowerR8[] = {
	0xff,0x00,0xff,0x00,0xff,0x18,0xff,0x24,
	0xff,0x20,0xff,0x20,0xff,0x20,0xff,0x20
};
const unsigned char Exclam8[] = {
	0xff,0x00,0xff,0x10,0xff,0x10,0xff,0x10,
	0xff,0x10,0xff,0x10,0xff,0x00,0xff,0x10
};
const unsigned char BlankSky8[] = {
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,
	0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00
};

const unsigned char Letter1_8[]  = { 0x54 }; //54-5E
const unsigned char Letter2_8[]  = { 0x55 };
const unsigned char Letter3_8[]  = { 0x56 };
const unsigned char Letter4_8[]  = { 0x57 };
const unsigned char Letter5_8[]  = { 0x58 };
const unsigned char Letter6_8[]  = { 0x59 };
const unsigned char Letter7_8[]  = { 0x5A };
const unsigned char Letter8_8[]  = { 0x5B };
const unsigned char Letter9_8[]  = { 0x5C };
const unsigned char Letter10_8[] = { 0x5D };
const unsigned char Letter11_8[] = { 0x5E };

//timer counter
UINT16 timerlevel8;
UINT8 timerclock8;

void UpdateHud8() {
	//health system DISPLAY
	//health first number:
	if (nutmeg_death == false) {
		switch (nutmeglives - (nutmeglives % 10)) {
			case 0:  UPDATE_HUD_TILE (3, 0, 6);  break;
			case 10: UPDATE_HUD_TILE (3, 0, 7);  break;
			case 20: UPDATE_HUD_TILE (3, 0, 8);  break;
			case 30: UPDATE_HUD_TILE (3, 0, 9);  break;
			case 40: UPDATE_HUD_TILE (3, 0, 10); break;
			case 50: UPDATE_HUD_TILE (3, 0, 11); break;
			case 60: UPDATE_HUD_TILE (3, 0, 12); break;
			case 70: UPDATE_HUD_TILE (3, 0, 13); break;
			case 80: UPDATE_HUD_TILE (3, 0, 14); break;
			case 90: UPDATE_HUD_TILE (3, 0, 15); break;
		}
		//health second number:
		switch (nutmeglives % 10) {
			case 0: UPDATE_HUD_TILE (4, 0, 6);  break;
			case 1: UPDATE_HUD_TILE (4, 0, 7);  break;
			case 2: UPDATE_HUD_TILE (4, 0, 8);  break;
			case 3: UPDATE_HUD_TILE (4, 0, 9);  break;
			case 4: UPDATE_HUD_TILE (4, 0, 10); break;
			case 5: UPDATE_HUD_TILE (4, 0, 11); break;
			case 6: UPDATE_HUD_TILE (4, 0, 12); break;
			case 7: UPDATE_HUD_TILE (4, 0, 13); break;
			case 8: UPDATE_HUD_TILE (4, 0, 14); break;
			case 9: UPDATE_HUD_TILE (4, 0, 15); break;
		}
	}

	//acorns:
	//acorns first number:
	switch (acorncounter - (acorncounter % 10)) {
		case 0:  UPDATE_HUD_TILE (17, 0, 6);  break;
		case 10: UPDATE_HUD_TILE (17, 0, 7);  break;
		case 20: UPDATE_HUD_TILE (17, 0, 8);  break;
		case 30: UPDATE_HUD_TILE (17, 0, 9);  break;
		case 40: UPDATE_HUD_TILE (17, 0, 10); break;
		case 50: UPDATE_HUD_TILE (17, 0, 11); break;
		case 60: UPDATE_HUD_TILE (17, 0, 12); break;
		case 70: UPDATE_HUD_TILE (17, 0, 13); break;
		case 80: UPDATE_HUD_TILE (17, 0, 14); break;
		case 90: UPDATE_HUD_TILE (17, 0, 15); break;
	}
	//acorns second number:
	switch (acorncounter % 10) {
		case 0: UPDATE_HUD_TILE (18, 0, 6);  break;
		case 1: UPDATE_HUD_TILE (18, 0, 7);  break;
		case 2: UPDATE_HUD_TILE (18, 0, 8);  break;
		case 3: UPDATE_HUD_TILE (18, 0, 9);  break;
		case 4: UPDATE_HUD_TILE (18, 0, 10); break;
		case 5: UPDATE_HUD_TILE (18, 0, 11); break;
		case 6: UPDATE_HUD_TILE (18, 0, 12); break;
		case 7: UPDATE_HUD_TILE (18, 0, 13); break;
		case 8: UPDATE_HUD_TILE (18, 0, 14); break;
		case 9: UPDATE_HUD_TILE (18, 0, 15); break;
	}

	if (timerclock8 <= 25 && cutscenemode == disabled) timerclock8 ++; //25 seems good

	if (timerclock8 == 25) {
		timerclock8 = 0;
		timerlevel8--;
	}

	//timer:
	//timer 100s digit:
	if (timerlevel8 == 300) UPDATE_HUD_TILE (10, 0, 9);
	if (timerlevel8 < 300 && timerlevel8 >= 200) UPDATE_HUD_TILE (10, 0, 8);
	if (timerlevel8 < 200 && timerlevel8 >= 100) UPDATE_HUD_TILE (10, 0, 7);
	if (timerlevel8 < 100) UPDATE_HUD_TILE (10, 0, 6);
	//timer 10s digit:
	if (timerlevel8 < 300 && timerlevel8 >= 200) {
		switch (timerlevel8 - 200 - (timerlevel8 % 10)) {
			case 0:  UPDATE_HUD_TILE (11, 0, 6);  break;
			case 10: UPDATE_HUD_TILE (11, 0, 7);  break;
			case 20: UPDATE_HUD_TILE (11, 0, 8);  break;
			case 30: UPDATE_HUD_TILE (11, 0, 9);  break;
			case 40: UPDATE_HUD_TILE (11, 0, 10); break;
			case 50: UPDATE_HUD_TILE (11, 0, 11); break;
			case 60: UPDATE_HUD_TILE (11, 0, 12); break;
			case 70: UPDATE_HUD_TILE (11, 0, 13); break;
			case 80: UPDATE_HUD_TILE (11, 0, 14); break;
			case 90: UPDATE_HUD_TILE (11, 0, 15); break;
		}
	}
	else if (timerlevel8 < 200 && timerlevel8 >= 100) {
		switch (timerlevel8 - 100 - (timerlevel8 % 10)) {
			case 0:  UPDATE_HUD_TILE (11, 0, 6);  break;
			case 10: UPDATE_HUD_TILE (11, 0, 7);  break;
			case 20: UPDATE_HUD_TILE (11, 0, 8);  break;
			case 30: UPDATE_HUD_TILE (11, 0, 9);  break;
			case 40: UPDATE_HUD_TILE (11, 0, 10); break;
			case 50: UPDATE_HUD_TILE (11, 0, 11); break;
			case 60: UPDATE_HUD_TILE (11, 0, 12); break;
			case 70: UPDATE_HUD_TILE (11, 0, 13); break;
			case 80: UPDATE_HUD_TILE (11, 0, 14); break;
			case 90: UPDATE_HUD_TILE (11, 0, 15); break;
		}
	}
	switch (timerlevel8 - (timerlevel8 % 10)) {
		case 0:  UPDATE_HUD_TILE (11, 0, 6);  break;
		case 10: UPDATE_HUD_TILE (11, 0, 7);  break;
		case 20: UPDATE_HUD_TILE (11, 0, 8);  break;
		case 30: UPDATE_HUD_TILE (11, 0, 9);  break;
		case 40: UPDATE_HUD_TILE (11, 0, 10); break;
		case 50: UPDATE_HUD_TILE (11, 0, 11); break;
		case 60: UPDATE_HUD_TILE (11, 0, 12); break;
		case 70: UPDATE_HUD_TILE (11, 0, 13); break;
		case 80: UPDATE_HUD_TILE (11, 0, 14); break;
		case 90: UPDATE_HUD_TILE (11, 0, 15); break;
	}
	//timer 1s digit:
	switch (timerlevel8 % 10) {
		case 0: UPDATE_HUD_TILE (12, 0, 6);  break;
		case 1: UPDATE_HUD_TILE (12, 0, 7);  break;
		case 2: UPDATE_HUD_TILE (12, 0, 8);  break;
		case 3: UPDATE_HUD_TILE (12, 0, 9);  break;
		case 4: UPDATE_HUD_TILE (12, 0, 10); break;
		case 5: UPDATE_HUD_TILE (12, 0, 11); break;
		case 6: UPDATE_HUD_TILE (12, 0, 12); break;
		case 7: UPDATE_HUD_TILE (12, 0, 13); break;
		case 8: UPDATE_HUD_TILE (12, 0, 14); break;
		case 9: UPDATE_HUD_TILE (12, 0, 15); break;
	}
}

void Start_StateLevel8() {
	level8counter = 0;
	timerlevel8 = 300;
	timerclock8 = 0;
	levelorientation = horizontal;
	SPRITES_8x16;

	nut_region = 0;
	pitdeathactive = true;

	deathmusicplayed = false;

	PlayMusic(quickstart, 1);
	
	//if health is full, add the bow
	if (health == full) { SpriteManagerAdd(SpriteNutmegBow, 4, 15*8); }
	scroll_target = spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 4, 15*8); //36

	InitScrollTiles(0, &level1tiles);
	InitScroll(BANK(level8map), &level8map, collision_tiles_level8, collision_tiles_down_level8);
	INIT_HUD(hud);

	cutscenemode = enabled;
	isAcornMoving = true; //yes, it is moving
	FlagPole_Init();
	endlevel_counter8 = 0;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevel8() {
	UpdateHud8();

	if (timerlevel8 <= 0) nutmeg_death = true;

	if (nutmeg_death == true) {
		if (deathmusicplayed == false) {
			__critical { PlayMusic(quickdeath, 1); }
			deathmusicplayed = true;
		}

		if (nutmegdeathtimer >= 125) {
			if (GameOver == true) {
				SetState(StateGameOver);
			}
			else if (GameOver == false) {
				SetState(StateOverworld1); // change to correct world
			}
		}

		nutmegdeathtimer++;
	}
	
	if (cutscenemode == enabled) {
		//Level Start!
		//Make Nutmeg Walk In
		if (level8counter == 0) {
			cutscenewalkright = true;
		}
		else if (level8counter >= 36) {
			cutscenewalkright = false;
			//but leave cutscene mode enabled still until Level Start! goes away
		}
		if (level8counter >= 10 && level8counter < 40) {
			set_bkg_data (0x54, 1, UpperL8);
			set_bkg_data (0x55, 1, LowerE8);
			set_bkg_data (0x56, 1, LowerV8);
			set_bkg_data (0x57, 1, LowerE8);
			set_bkg_data (0x58, 1, LowerL8);
			set_bkg_data (0x59, 1, UpperS8);
			set_bkg_data (0x5A, 1, LowerT8);
			set_bkg_data (0x5B, 1, LowerA8);
			set_bkg_data (0x5C, 1, LowerR8);
			set_bkg_data (0x5D, 1, LowerT8);
			set_bkg_data (0x5E, 1, Exclam8);

			set_bkg_tiles ( 7, 13, 1, 1, Letter1_8); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 13, 1, 1, Letter2_8);
			set_bkg_tiles ( 9, 13, 1, 1, Letter3_8);
			set_bkg_tiles (10, 13, 1, 1, Letter4_8);
			set_bkg_tiles (11, 13, 1, 1, Letter5_8);
			set_bkg_tiles ( 7, 14, 1, 1, Letter6_8);
			set_bkg_tiles ( 8, 14, 1, 1, Letter7_8);
			set_bkg_tiles ( 9, 14, 1, 1, Letter8_8);
			set_bkg_tiles (10, 14, 1, 1, Letter9_8);
			set_bkg_tiles (11, 14, 1, 1, Letter10_8);
			set_bkg_tiles (12, 14, 1, 1, Letter11_8);
		}
		else if (level8counter >= 40 && level8counter < 70) {
			set_bkg_data (0x54, 1, BlankSky8);
			set_bkg_data (0x55, 1, BlankSky8);
			set_bkg_data (0x56, 1, BlankSky8);
			set_bkg_data (0x57, 1, BlankSky8);
			set_bkg_data (0x58, 1, BlankSky8);
			set_bkg_data (0x59, 1, BlankSky8);
			set_bkg_data (0x5A, 1, BlankSky8);
			set_bkg_data (0x5B, 1, BlankSky8);
			set_bkg_data (0x5C, 1, BlankSky8);
			set_bkg_data (0x5D, 1, BlankSky8);
			set_bkg_data (0x5E, 1, BlankSky8);

			set_bkg_tiles ( 7, 13, 1, 1, Letter1_8); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 13, 1, 1, Letter2_8);
			set_bkg_tiles ( 9, 13, 1, 1, Letter3_8);
			set_bkg_tiles (10, 13, 1, 1, Letter4_8);
			set_bkg_tiles (11, 13, 1, 1, Letter5_8);
			set_bkg_tiles ( 7, 14, 1, 1, Letter6_8);
			set_bkg_tiles ( 8, 14, 1, 1, Letter7_8);
			set_bkg_tiles ( 9, 14, 1, 1, Letter8_8);
			set_bkg_tiles (10, 14, 1, 1, Letter9_8);
			set_bkg_tiles (11, 14, 1, 1, Letter10_8);
			set_bkg_tiles (12, 14, 1, 1, Letter11_8);
		}
		else if (level8counter >= 70 && level8counter < 100) {
			set_bkg_data (0x54, 1, UpperL8);
			set_bkg_data (0x55, 1, LowerE8);
			set_bkg_data (0x56, 1, LowerV8);
			set_bkg_data (0x57, 1, LowerE8);
			set_bkg_data (0x58, 1, LowerL8);
			set_bkg_data (0x59, 1, UpperS8);
			set_bkg_data (0x5A, 1, LowerT8);
			set_bkg_data (0x5B, 1, LowerA8);
			set_bkg_data (0x5C, 1, LowerR8);
			set_bkg_data (0x5D, 1, LowerT8);
			set_bkg_data (0x5E, 1, Exclam8);

			set_bkg_tiles ( 7, 13, 1, 1, Letter1_8); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 13, 1, 1, Letter2_8);
			set_bkg_tiles ( 9, 13, 1, 1, Letter3_8);
			set_bkg_tiles (10, 13, 1, 1, Letter4_8);
			set_bkg_tiles (11, 13, 1, 1, Letter5_8);
			set_bkg_tiles ( 7, 14, 1, 1, Letter6_8);
			set_bkg_tiles ( 8, 14, 1, 1, Letter7_8);
			set_bkg_tiles ( 9, 14, 1, 1, Letter8_8);
			set_bkg_tiles (10, 14, 1, 1, Letter9_8);
			set_bkg_tiles (11, 14, 1, 1, Letter10_8);
			set_bkg_tiles (12, 14, 1, 1, Letter11_8);
		}
		else if (level8counter >= 100 && level8counter < 101) {
			set_bkg_data (0x54, 1, BlankSky8);
			set_bkg_data (0x55, 1, BlankSky8);
			set_bkg_data (0x56, 1, BlankSky8);
			set_bkg_data (0x57, 1, BlankSky8);
			set_bkg_data (0x58, 1, BlankSky8);
			set_bkg_data (0x59, 1, BlankSky8);
			set_bkg_data (0x5A, 1, BlankSky8);
			set_bkg_data (0x5B, 1, BlankSky8);
			set_bkg_data (0x5C, 1, BlankSky8);
			set_bkg_data (0x5D, 1, BlankSky8);
			set_bkg_data (0x5E, 1, BlankSky8);

			set_bkg_tiles ( 7, 13, 1, 1, Letter1_8); //x, y, w, h, *tiles
			set_bkg_tiles ( 8, 13, 1, 1, Letter2_8);
			set_bkg_tiles ( 9, 13, 1, 1, Letter3_8);
			set_bkg_tiles (10, 13, 1, 1, Letter4_8);
			set_bkg_tiles (11, 13, 1, 1, Letter5_8);
			set_bkg_tiles ( 7, 14, 1, 1, Letter6_8);
			set_bkg_tiles ( 8, 14, 1, 1, Letter7_8);
			set_bkg_tiles ( 9, 14, 1, 1, Letter8_8);
			set_bkg_tiles (10, 14, 1, 1, Letter9_8);
			set_bkg_tiles (11, 14, 1, 1, Letter10_8);
			set_bkg_tiles (12, 14, 1, 1, Letter11_8);

			cutscenemode = disabled;

			if (levelbeat == false) {
				PlayMusic(mushrooms, 1);
			}
		}

		if (level8counter < 105) level8counter++;
	}

	Water_Animate();

	FlagPole_Animate();
	
	if (levelbeat == true) {
		cutscenemode = enabled;
		cutscenewalkright = true;
		cutscenewalkleft = false;
		
		if (spr_nutmeg->x > 1956) {
			cutscenewalkright = true;
			cutscenewalkleft = false;
		}
		else if (spr_nutmeg->x < 1956) {
			cutscenewalkright = true;
			cutscenewalkleft = false;
		}
		else if (spr_nutmeg->x == 1956) {
			cutscenewalkright = true;
			cutscenewalkleft = false;
		}

		if (endlevel_counter8 >= 100) {
			//endlevel_counter8 = 0;
			//cutscenewalkleft = false;
			//cutscenewalkright = false;
			//cutscenemode = disabled;

			SetState(StateOverworld1);
		}

		if (endlevel_counter8 < 250) endlevel_counter8++;

		
	}

	if (spr_nutmeg->x >= 1936 && spr_nutmeg->x < 1944 && levelbeat == false && nutmeg_death == false) {
		FlagPole_Activate (1948, 96);
		levelbeat = true;
		endlevel_counter8 = 0;
		cutscenemode = enabled;
		cutscenewalkright = true;
	}

	// 0-63:
	if (spr_nutmeg->x > 0 && spr_nutmeg->x <= 250 && nut_region <= 0) {
		SpriteManagerAdd(SpriteAcorn, 11*8+4, 0*8+4);
		SpriteManagerAdd(SpriteAcorn, 37*8, 13*8);
		SpriteManagerAdd(SpriteMushroom, 53*8, 18*8);
		SpriteManagerAdd(EnemyBirdy, 80*8, 19*8);
		SpriteManagerAdd(SpriteAcorn, 80*8, 11*8);
		SpriteManagerAdd(EnemyBirdy, 89*8, 19*8);
		nut_region = 1;
	}
	// Up to 94:
	else if (spr_nutmeg->x > 250 && spr_nutmeg->x <= 500 && nut_region <= 1) {
		SpriteManagerAdd(SpriteAcorn, 58*8, 14*8);
    	nut_region = 2;
	}
	// Up to 125:
	else if (spr_nutmeg->x > 500 && spr_nutmeg->x <= 750 && nut_region <= 2) {
		SpriteManagerAdd(SpriteAcorn, 100*8+4, 11*8);
		SpriteManagerAdd(SpriteAcorn, 102*8+4, 15*8+4);
		SpriteManagerAdd(EnemyBunny, 110*8, 14*8);
	    nut_region = 3;
	}
	// Up to 156:
	else if (spr_nutmeg->x > 750 && spr_nutmeg->x <= 1000 && nut_region <= 3) {
		SpriteManagerAdd(SpriteAcorn, 125*8, 17*8);
		SpriteManagerAdd(SpriteAcorn, 155*8, 1*8);
	    nut_region = 4;
	}
	// Up to 188:
	else if (spr_nutmeg->x > 1000 && spr_nutmeg->x <= 1250 && nut_region <= 4) {
		SpriteManagerAdd(SpriteAcorn, 157*8, 1*8);
		SpriteManagerAdd(SpriteAcorn, 159*8, 2*8);
		SpriteManagerAdd(EnemyBirdy, 159*8+4, 18*8);
		SpriteManagerAdd(SpriteAcorn, 161*8, 4*8);
		SpriteManagerAdd(EnemyButterfly, 177*8, 11*8);
		SpriteManagerAdd(EnemyBunny, 185*8, 18*8);
	    nut_region = 5;
	}
	// Up to 219:
	else if (spr_nutmeg->x > 1250 && spr_nutmeg->x <= 1500 && nut_region <= 5) {
		SpriteManagerAdd(SpriteAcorn, 190*8, 8*8);
		SpriteManagerAdd(SpriteAcorn, 192*8, 15*8);
		SpriteManagerAdd(SpriteAcorn, 198*8, 16*8);
		SpriteManagerAdd(SpriteAcorn, 200*8, 6*8);
		SpriteManagerAdd(EnemyButterfly, 212*8, 13*8);
		SpriteManagerAdd(EnemyBunny, 220*8, 18*8);
	    nut_region = 6;
	}
	// Up to 250:
	else if (spr_nutmeg->x > 1500 && spr_nutmeg->x <= 1750 && nut_region <= 6) {
		SpriteManagerAdd(SpriteAcorn, 211*8, 4*8);
		SpriteManagerAdd(EnemyBirdy, 235*8, 14*8);
	    nut_region = 7;
	}
	else if (spr_nutmeg->x > 1750 && spr_nutmeg->x <= 2000 && nut_region <= 7) {
	    nut_region = 8;
	}
}