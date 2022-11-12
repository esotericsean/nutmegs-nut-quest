#include "Banks/SetAutoBank.h"

#include "..\res\src\cutscenegordontiles.h"
#include "..\res\src\cutscenegordonmap.h"

#include "..\res\src\gordon1.h"
#include "..\res\src\nutmeg.h"
#include "..\res\src\acorn.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Palette.h"
#include "Sound.h"
#include "Keys.h"

#include "../src/GlobalVars.h"
#include "../src/Font.h"

IMPORT_MAP (cutscenegordonmap);

UINT16 cutscenegordoncounter;
UINT8 cutscenegordonspeed;
UINT8 cutscenegordonspeedlimit;

const UINT8 collision_tiles_cutscenegordon[] = {3,4};

/*
const UWORD pal_cut13[] = {
	RGB(9, 23, 27),
	RGB(22, 28, 19),
	RGB(17, 26, 17),
	RGB(16, 23, 20)
};
const UWORD pal_cut14[] = {
	RGB(31, 31, 31),
	RGB(22, 28, 19),
	RGB(17, 26, 17),
	RGB(16, 23, 20)
};
const UWORD pal_cut15[] = {
	RGB(16, 27, 12),
    RGB(8, 23, 8),
	RGB(17, 10, 7),
	0
};
const UWORD pal_cut16[] = {
	RGB(31, 31, 31),
    RGB(9, 23, 27),
	0,
	0
};
const UWORD pal_cut17[] = {
	RGB(16, 23, 20),
    RGB(23, 17, 10),
	RGB(19, 10, 5),
	0
};
const UWORD pal_cut18[] = {
	RGB(23, 17, 10),
    RGB(19, 10, 5),
	RGB(17, 8, 4),
	0
};
const UWORD pal_cut19[] = {
	RGB(31, 31, 31),
    RGB(23, 17, 10),
	RGB(19, 10, 5),
	0
};
*/

//color palette for a sprite, first number doesn't matter (cause it's transparent) so use 0
/*
const UWORD acornPalette[] = {
	0, RGB(30, 23, 17), RGB(20, 9, 0), 0
};
*/

//extern struct Sprite * spr_nutmeg1;
//extern struct Sprite * spr_nutmeg2;
Sprite * spr_nutmeg;
//extern Sprite * spr_nutmeg2;

const UINT16 bg_palette_cutscenegordon[] = {
    PALETTE_FROM_HEADER (cutscenegordontiles)
};

const UINT16 sprites_palette_cutscenegordon[] = {
    PALETTE_INDEX (gordon1, 0),
    PALETTE_INDEX (nutmeg, 0),
	PALETTE_INDEX (acorn, 1)
};

//extern UINT8* oaktree_mod_Data[];

Sprite * spr_gordoncamera;
Sprite * spr_gordonposition;
Sprite * spr_gordon2position;
Sprite * spr_acorn;

//need to specify a param when loading bg
//SetPalette only has 2 options: BG_PAL and SPRITES_PAL
//PALETTE_FROM_HEADER I don't think is it
//void InitScrollTiles(UINT8 first_tile, UINT8 n_tiles, UINT8* tile_data, UINT8 tile_bank);

void Start_StateCutsceneGordon() {
    SPRITES_8x16;

    //PlayMusic(oaktree_mod_Data, 4, 1);

    //SetPalette (BG_PALETTE, 0, 8, bg_palette_cutscenegordon, bank_StateCutsceneGordon);
	//SetPalette (SPRITES_PALETTE, 0, 1, sprites_palette_cutscenegordon, bank_StateCutsceneGordon);

    //set_sprite_palette(1, 1, acornPalette); //start at BG1 and load 1 palette

    SpriteManagerLoad(35);   //nutmeg
    //SpriteManagerLoad(7);   //nutmeg2
    SpriteManagerLoad(24);  //gordon1
    SpriteManagerLoad(25);  //gordon2
    SpriteManagerLoad(2);   //acorn
    SpriteManagerLoad(29);  //gordon camera

    spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 8, 96);
    //spr_nutmeg2 = SpriteManagerAdd(SpriteNutmeg2, 4+16, 96);

    spr_gordonposition =  SpriteManagerAdd(SpriteGordon1, 196, 96); //96, 96
    spr_gordon2position = SpriteManagerAdd(SpriteGordon2, 196+16, 96);

    spr_acorn = SpriteManagerAdd(SpriteAcorn, 50, 16);

    isAcornMoving = false;

    InitScrollTiles(0, &cutscenegordontiles);
    //InitScroll(&cutscenegordonmap, collision_tiles_cutscenegordon, 0);
    InitScroll(BANK(cutscenegordonmap), &cutscenegordonmap, collision_tiles_cutscenegordon, 0);

    SHOW_SPRITES;
	SHOW_BKG;

    cutscenegordoncounter = 75;
    cutscenegordonspeed = 0;
    cutscenegordonspeedlimit = 3;
}

void Update_StateCutsceneGordon() {
    if (cutscenegordoncounter == 0) {
        scroll_target = spr_gordoncamera = SpriteManagerAdd(SpriteGordonCamera, 112, 10); //112, 10
    }

    if (cutscenegordoncounter >= 75 && cutscenegordoncounter < 77) {
        //set_sprite_palette(1, 1, acornPalette); //start at BG1 and load 1 palette
    }
    
    //acorn shake
    switch (cutscenegordoncounter) {
        case 165: spr_acorn->x = spr_acorn->x - 2; spr_acorn->y = spr_acorn->y + 1; break;
        case 180: spr_acorn->x = spr_acorn->x + 2; spr_acorn->y = spr_acorn->y - 1; break;
        case 195: spr_acorn->x = spr_acorn->x + 2; spr_acorn->y = spr_acorn->y + 1; break;
        case 210: spr_acorn->x = spr_acorn->x - 2; spr_acorn->y = spr_acorn->y - 1; break;
    }

    //acorn fall
    if (cutscenegordoncounter >= 280 && cutscenegordoncounter < 290 && cutscenegordonspeed == 0) {
        spr_acorn->y = spr_acorn->y - 1;
    }
    else if (cutscenegordoncounter >= 290 && cutscenegordoncounter < 300 && cutscenegordonspeed == 0) {
        cutscenegordonspeedlimit = 6;
        spr_acorn->y = spr_acorn->y - 1;
    }
    else if (cutscenegordoncounter >= 320 && cutscenegordoncounter < 330 && cutscenegordonspeed == 0) {
        cutscenegordonspeedlimit = 6;
        spr_acorn->y = spr_acorn->y + 2;
    }
    else if (cutscenegordoncounter >= 330 && cutscenegordoncounter < 350) {
        cutscenegordonspeedlimit = 3;
        if (cutscenegordonspeed == 0) {
            spr_acorn->y = spr_acorn->y + 5;
        }
    }
    else if (cutscenegordoncounter >= 350 && cutscenegordoncounter < 370) {
        if (cutscenegordonspeed == 0) {
            spr_acorn->y = spr_acorn->y + 13;
        }
    }

    //acorn bounce
    if (cutscenegordoncounter >= 370 && cutscenegordoncounter < 375) {
        if (cutscenegordonspeed == 0) spr_acorn->y = spr_acorn->y - 2;
    }
    else if (cutscenegordoncounter >= 375 && cutscenegordoncounter < 380) {
        if (cutscenegordonspeed == 0) spr_acorn->y = spr_acorn->y - 1;
    }
    else if (cutscenegordoncounter >= 390 && cutscenegordoncounter < 394) {
        if (cutscenegordonspeed == 0) spr_acorn->y = spr_acorn->y + 1;
    }
    else if (cutscenegordoncounter >= 394 && cutscenegordoncounter < 399) {
        if (cutscenegordonspeed == 0) spr_acorn->y = spr_acorn->y + 2;
    }
    else if (cutscenegordoncounter == 400) {
        spr_acorn->y = spr_acorn->y + 1;
    }

    //gordon walks to acorn
    if (cutscenegordoncounter >= 410 && cutscenegordoncounter < 695) {
        gordonwalkleft = true;
        gordonwalkright = false;
    }

    //gordon pauses
    else if (cutscenegordoncounter >= 695 && cutscenegordoncounter < 705) {
        gordonwalkleft = false;
        gordonwalkright = false;
    }

    //gordon picks up acorn
    if (cutscenegordoncounter >= 705 && cutscenegordoncounter < 723) {
        if (cutscenegordonspeed == 0) {
            spr_acorn->x = spr_acorn->x + 1;
            spr_acorn->y = spr_acorn->y - 1;
        }
    }
    else if (cutscenegordoncounter >= 723 && cutscenegordoncounter < 729) {
        cutscenegordonspeedlimit = 3;
        if (cutscenegordonspeed == 0) {
            spr_acorn->x = spr_acorn->x + 2;
        }
    }

    //gordon turns around + move acorn
    if (cutscenegordoncounter == 749) {
        gordonwalkleft = false;
        gordonwalkright = true;
        //SPRITE_SET_VMIRROR (spr_acorn);
        spr_acorn->mirror = V_MIRROR;
        spr_acorn->x = spr_acorn->x + 18;
    }
    else if (cutscenegordoncounter >= 750 && cutscenegordoncounter < 850) {
        //gordon
        gordonwalkleft = false;
        gordonwalkright = true;

        //nutmeg
        if (cutscenegordoncounter >= 800 && cutscenegordoncounter < 850) {
            cutscenewalkleft = false;
		    cutscenewalkright = true;
        }

        //acorn sync to gordon
        spr_acorn->x = spr_gordonposition->x + 6;
    }
    else if (cutscenegordoncounter == 850) {
        gordonwalkleft = false;
        gordonwalkright = false;
        cutscenewalkleft = false;
		cutscenewalkright = false;
    }

    //gordon turns around
    if (cutscenegordoncounter == 852) {
        gordonwalkleft = true;
        gordonwalkright = false;
        //SPRITE_UNSET_VMIRROR (spr_acorn);
        spr_acorn->mirror = NO_MIRROR;
        spr_acorn->x = spr_acorn->x - 20;
    }
    else if (cutscenegordoncounter >= 853 && cutscenegordoncounter < 863) {
        gordonwalkleft = false;
        gordonwalkright = false;
    }

    //gordon runs away and nutmeg chases after
    if (cutscenegordoncounter == 883) {
        gordonwalkleft = false;
        gordonwalkright = true;
        cutscenewalkleft = false;
		cutscenewalkright = true;
        //SPRITE_SET_VMIRROR (spr_acorn);
        spr_acorn->mirror = V_MIRROR;
        spr_acorn->x = spr_acorn->x + 18;
    }
    else if (cutscenegordoncounter >= 884) {
        spr_acorn->x = spr_gordonposition->x + 6;

        if (cutscenegordonspeed == 0) {
            spr_gordonposition->x = spr_gordonposition->x + 1;
            spr_gordon2position->x = spr_gordon2position->x + 1;
        }
    }

    //end
    if (cutscenegordoncounter >= 1020) {
        SetState(StateOverworld1);
    }
    
    cutscenegordoncounter++;
    if (cutscenegordoncounter >= 65000) cutscenegordoncounter = 65000;

    cutscenegordonspeed++;
    if (cutscenegordonspeed > cutscenegordonspeedlimit) cutscenegordonspeed = 0;

    /*if (KEY_PRESSED(J_A) || KEY_PRESSED(J_START)) {
        SetState(StateOverworld1);
    }*/

    if (KEY_PRESSED(J_START)) {
        SetState(StateOverworld1);
    }
}