#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>
#include "ZGBMain.h"
#include "Music.h"
#include "Scroll.h"
#include "Sound.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Palette.h"

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


static const LevelT levelInfo = {
	.isWaterLevel = false,
	.isSpikeLevel = false,

	// Min and max tile number for slippery ice tiles (set to NO_ICE_TILES for no ice)
	.iceTileMin = NO_ICE_TILES,
	.iceTileMax = NO_ICE_TILES,

	// vertical or horizontal Level
	.orientation = horizontal,
	.isHorizontalGoalpost = false,

	// level timer info
	.hasTimer = false,
	.timer = 300,
	.timerclock = 0,
};

void Start_StateLevelTree(void)
{
	level = levelInfo;

	cutscenemode = disabled;
	nut_region = 0;

	PlayMusic(oaktree, 1);

	scroll_target = nutmeg_Add(36+28, 104);
	nutmeg.direction = right;
	
	SpriteManagerAdd(SpriteCinnamon, 8, 96);
	SpriteManagerAdd(SpriteRuby, 32, 60);
	Sprite *s = SpriteManagerAdd(SpriteMaple, 90, 96);
	s->mirror = V_MIRROR

	
	InitScrollTiles(0, &treetiles);
	InitScroll(BANK(treemap2), &treemap2, collision_tiles_level, 0);

	LevelStart_Init(12,12);

	SPRITES_8x16;
	SHOW_SPRITES;
	SHOW_BKG;
}

void Update_StateLevelTree (void) 
{
	//if Nutmeg touches the Oak Tree Door, then leave
	if (spr_nutmeg->x >= 120 && spr_nutmeg->x < 132 && spr_nutmeg->y >=80 && spr_nutmeg->y < 104)
	{
		SetState(StateOverworld);
	}
}