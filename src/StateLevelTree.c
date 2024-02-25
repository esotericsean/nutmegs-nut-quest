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
#include "Hud.h"
#include "LevelStart.h"
#include "SpriteNutmeg.h"

#include "GlobalVars.h"

IMPORT_MAP (treemap2);

static const UINT8 collision_tiles_level[] = {2, 3, 4, 5, 7, 8, 9, 10, 12, 0};

DECLARE_MUSIC(oaktree);

// You can reference it from other files by including this
// (or by adding it to a .h include file and including that)
extern Sprite * spr_nutmeg;
extern Sprite * spr_nutmegbow;
extern Sprite * spr_camera;

void nutmegBow_update (void) BANKED;

void Start_StateLevelTree(void)
{
	SPRITES_8x16;

	pitdeathactive = true;

	nut_region = 0;

	deathmusicplayed = false;

	PlayMusic(oaktree, 1);

	//SpriteManagerLoad(14); 	//cinnamon
	//SpriteManagerLoad(15); 	//maple
	//SpriteManagerLoad(28); 	//ruby

	if (hasbow == true) {
		spr_nutmegbow = SpriteManagerAdd(SpriteNutmegBow, 36+28, 104);
	}
	scroll_target = spr_nutmeg = SpriteManagerAdd(SpriteNutmeg, 36+28, 104);
	nutmeg_direction = right;
	
	SpriteManagerAdd(SpriteCinnamon, 8, 96);
	
	SpriteManagerAdd(SpriteRuby, 32, 60);
	
	Sprite *s = SpriteManagerAdd(SpriteMaple, 90, 96);
	s->mirror = V_MIRROR

	
	InitScrollTiles(0, &treetiles);
	InitScroll(BANK(treemap2), &treemap2, collision_tiles_level, 0);

	LevelStart_Init(12,12);
	
	cutscenemode = disabled;

	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevelTree (void) 
{
	//if Nutmeg touches the Oak Tree Door, then leave
	if (spr_nutmeg->x >= 120 && spr_nutmeg->x < 132 && spr_nutmeg->y >=80 && spr_nutmeg->y < 104)
	{
		SetState(StateOverworld1);
	}
}