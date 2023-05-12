#include "Banks/SetAutoBank.h"

#include "..\res\src\cutscenegordontiles.h"
#include "..\res\src\cutscenegordonmap.h"

#include "..\res\src\gordon1.h"
#include "..\res\src\nutmeg.h"
#include "..\res\src\acorn.h"

#include "ZGBMain.h"
#include "Music.h"s
#include "Scroll.h"
#include "SpriteManager.h"

#include "Palette.h"
#include "Sound.h"
#include "Keys.h"

#include "../src/GlobalVars.h"
#include "../src/Font.h"

IMPORT_MAP (cutscenegordonmap);

DECLARE_MUSIC (gordoncutscene);
DECLARE_MUSIC (nutmeghey);

UINT16 cutscenegordoncounter;
UINT8 cutscenegordonspeed;
UINT8 cutscenegordonspeedlimit;

const UINT8 collision_tiles_cutscenegordon[] = {3,4,0};

Sprite * spr_nutmeg;

Sprite * spr_gordoncamera;
Sprite * spr_gordonposition;
Sprite * spr_gordon2position;
Sprite * spr_acorn;

void Start_StateCutsceneGordon() {
    SPRITES_8x16;

    spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 8, 96);

    spr_gordonposition =  SpriteManagerAdd(SpriteGordon1, 196, 96); //96, 96
    spr_gordon2position = SpriteManagerAdd(SpriteGordon2, 196+16, 96);

    spr_acorn = SpriteManagerAdd(SpriteAcorn, 50, 16);

    isAcornMoving = false;

    InitScrollTiles(0, &cutscenegordontiles);
    InitScroll(BANK(cutscenegordonmap), &cutscenegordonmap, collision_tiles_cutscenegordon, 0);

    SHOW_SPRITES;
	SHOW_BKG;

    cutscenegordoncounter = 1;
    cutscenegordonspeed = 0;
    cutscenegordonspeedlimit = 3;

    PlayMusic(gordoncutscene, 0);
}

void Update_StateCutsceneGordon() {
    //acorn shake
    switch (cutscenegordoncounter) {
        case 25: spr_acorn->x = spr_acorn->x - 2; spr_acorn->y = spr_acorn->y + 1; break;
        case 40: spr_acorn->x = spr_acorn->x + 2; spr_acorn->y = spr_acorn->y - 1; break;
        case 55: spr_acorn->x = spr_acorn->x + 2; spr_acorn->y = spr_acorn->y + 1; break;
        case 70: spr_acorn->x = spr_acorn->x - 2; spr_acorn->y = spr_acorn->y - 1; break;
    }

    //acorn fall
    if (cutscenegordoncounter >= 105 && cutscenegordoncounter < 115 && cutscenegordonspeed == 0) {
        spr_acorn->y = spr_acorn->y - 1;
    }
    else if (cutscenegordoncounter >= 115 && cutscenegordoncounter < 125 && cutscenegordonspeed == 0) {
        cutscenegordonspeedlimit = 6;
        spr_acorn->y = spr_acorn->y - 1;
    }
    else if (cutscenegordoncounter >= 140 && cutscenegordoncounter < 150 && cutscenegordonspeed == 0) {
        cutscenegordonspeedlimit = 6;
        spr_acorn->y = spr_acorn->y + 2;
    }
    else if (cutscenegordoncounter >= 150 && cutscenegordoncounter < 170) {
        cutscenegordonspeedlimit = 3;
        if (cutscenegordonspeed == 0) {
            spr_acorn->y = spr_acorn->y + 5;
        }
    }
    else if (cutscenegordoncounter >= 170 && cutscenegordoncounter < 190) {
        if (cutscenegordonspeed == 0) {
            spr_acorn->y = spr_acorn->y + 13;
        }
    }
    
    //fix acorn
    if (cutscenegordoncounter == 190) {
        spr_acorn->y = spr_acorn->y + 1;
    }

    //acorn bounce
    if (cutscenegordoncounter >= 190 && cutscenegordoncounter < 195) {
        if (cutscenegordonspeed == 0) spr_acorn->y = spr_acorn->y - 2;
    }
    else if (cutscenegordoncounter >= 195 && cutscenegordoncounter < 200) {
        if (cutscenegordonspeed == 0) spr_acorn->y = spr_acorn->y - 1;
    }
    else if (cutscenegordoncounter >= 210 && cutscenegordoncounter < 214) {
        if (cutscenegordonspeed == 0) spr_acorn->y = spr_acorn->y + 1;
    }
    else if (cutscenegordoncounter >= 214 && cutscenegordoncounter < 219) {
        if (cutscenegordonspeed == 0) spr_acorn->y = spr_acorn->y + 2;
    }
    else if (cutscenegordoncounter == 220) {
        spr_acorn->y = spr_acorn->y + 1;
    }

    //gordon walks to acorn
    if (cutscenegordoncounter >= 230 && cutscenegordoncounter < 515) {
        gordonwalkleft = true;
        gordonwalkright = false;
    }

    //gordon pauses
    else if (cutscenegordoncounter >= 515 && cutscenegordoncounter < 525) {
        gordonwalkleft = false;
        gordonwalkright = false;
    }

    //gordon picks up acorn
    if (cutscenegordoncounter >= 525 && cutscenegordoncounter < 543) {
        if (cutscenegordonspeed == 0) {
            spr_acorn->x = spr_acorn->x + 1;
            spr_acorn->y = spr_acorn->y - 1;
        }
    }
    else if (cutscenegordoncounter >= 543 && cutscenegordoncounter < 549) {
        cutscenegordonspeedlimit = 3;
        if (cutscenegordonspeed == 0) {
            spr_acorn->x = spr_acorn->x + 2;
        }
    }

    //gordon turns around + move acorn
    if (cutscenegordoncounter == 569) {
        gordonwalkleft = false;
        gordonwalkright = true;
        spr_acorn->mirror = V_MIRROR;
        spr_acorn->x = spr_acorn->x + 18;
    }
    else if (cutscenegordoncounter >= 570 && cutscenegordoncounter < 670) {
        //gordon
        gordonwalkleft = false;
        gordonwalkright = true;

        //nutmeg
        if (cutscenegordoncounter >= 620 && cutscenegordoncounter < 670) {
            cutscenewalkleft = false;
		    cutscenewalkright = true;
        }

        //acorn sync to gordon
        spr_acorn->x = spr_gordonposition->x + 6;
    }
    else if (cutscenegordoncounter == 670) {
        gordonwalkleft = false;
        gordonwalkright = false;
        cutscenewalkleft = false;
		cutscenewalkright = false;
    }

    //gordon turns around
    if (cutscenegordoncounter == 672) {
        PlayMusic(nutmeghey, 0);

        gordonwalkleft = true;
        gordonwalkright = false;
        spr_acorn->mirror = NO_MIRROR;
        spr_acorn->x = spr_acorn->x - 20;
    }
    else if (cutscenegordoncounter >= 673 && cutscenegordoncounter < 683) {
        gordonwalkleft = false;
        gordonwalkright = false;
    }

    //gordon runs away and nutmeg chases after
    if (cutscenegordoncounter == 703) {
        gordonwalkleft = false;
        gordonwalkright = true;
        cutscenewalkleft = false;
		cutscenewalkright = true;
        spr_acorn->mirror = V_MIRROR;
        spr_acorn->x = spr_acorn->x + 18;
    }
    else if (cutscenegordoncounter >= 704) {
        spr_acorn->x = spr_gordonposition->x + 6;

        if (cutscenegordonspeed == 0) {
            spr_gordonposition->x = spr_gordonposition->x + 1;
            spr_gordon2position->x = spr_gordon2position->x + 1;
        }
    }

    //end
    if (cutscenegordoncounter >= 840) {
        SetState(StateOverworld1);
    }
    
    cutscenegordoncounter++;
    if (cutscenegordoncounter >= 1000) cutscenegordoncounter = 1000;

    cutscenegordonspeed++;
    if (cutscenegordonspeed > cutscenegordonspeedlimit) cutscenegordonspeed = 0;

    if (KEY_PRESSED(J_START)) {
        SetState(StateOverworld1);
    }
}