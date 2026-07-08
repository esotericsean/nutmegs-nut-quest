#include "Banks/SetAutoBank.h"
#include "Sound.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "GlobalVars.h"
#include "Sfx.h"
#include "StateLevel1b.h"
#include "StateLevel1c.h"

extern Sprite * spr_nutmeg;
extern UINT8 level_playing;
extern bool levelGoldenCollected[MAX_LEVEL_TRACKING];

static const INT8 acornMoveYAtTime [] = {0,0,0,1,1,0,0,0,-1,-1};

#define IS_STILL_POS (0)
#define MOVE_POS (1)
#define TIMER_POS (2)

// acorn moves once per this many frames
#define MOVE_SPEED (10)

void Start_SpriteAcorn(void) {
    UINT8 meta = THIS->custom_data[3];
    bool hasMeta = (meta & ACORN_META_ASSIGNED) != 0;
    bool isGolden = hasMeta && ((meta & ACORN_META_GOLDEN) != 0);
    if (!hasMeta) {
        THIS->custom_data[3] = 0;
    }
    if (isGolden && (level_playing < MAX_LEVEL_TRACKING) && levelGoldenCollected[level_playing]) {
        SpriteManagerRemoveSprite(THIS);
        return;
    }

	if (level.orientation == horizontal) {
		THIS->lim_x = 350;
		THIS->lim_y = 144;
	}
	else if (level.orientation == vertical) {
		THIS->lim_x = 288;
		THIS->lim_y = 250;
	}

	// setup these variables so the defaults are all 0
	// because the actorPosT stuff is overriding all the custom data fields
	THIS->custom_data[IS_STILL_POS] = false;
	THIS->custom_data[MOVE_POS] = 0;
	THIS->custom_data[TIMER_POS] = 0;
}


void Update_SpriteAcorn(void) 
{
	if (THIS->custom_data[IS_STILL_POS] == false)
	{
		THIS->custom_data[TIMER_POS] ++;
		if (THIS->custom_data[TIMER_POS] >= MOVE_SPEED)
		{
			THIS->custom_data[TIMER_POS] = 0;

			THIS->y += acornMoveYAtTime[THIS->custom_data[MOVE_POS]];
			THIS->custom_data[MOVE_POS]++;

			if (THIS->custom_data[MOVE_POS] >= sizeof (acornMoveYAtTime))
			{
				THIS->custom_data[MOVE_POS] =0;
			}
		}
	}

    UINT8 meta = THIS->custom_data[3];
    bool hasMeta = (meta & ACORN_META_ASSIGNED) != 0;
    bool isGolden = hasMeta && ((meta & ACORN_META_GOLDEN) != 0);
    if (isGolden && (level_playing < MAX_LEVEL_TRACKING) && levelGoldenCollected[level_playing]) {
        SpriteManagerRemoveSprite(THIS);
        return;
    }

	if (CheckCollision(THIS, spr_nutmeg)) {
        bool hasMeta = (meta & ACORN_META_ASSIGNED) != 0;
        bool fromLevel1c = (meta & ACORN_META_LEVEL1C) != 0;
        UINT8 slot = (UINT8)(meta & ACORN_META_INDEX_MASK);

        if (hasMeta) {
            if (fromLevel1c) {
                Level1c_MarkSpawnCollected(slot);
            } else {
                Level1b_MarkSpawnCollected(slot);
            }
            THIS->custom_data[3] = 0;
        }

        if (isGolden) {
            levelGoldenAcornFound = true;
            if (nutmeg.goldenAcorns < 255u) {
                nutmeg.goldenAcorns++;
            }
            if (gameStats.totalGoldenAcorns < 0xFFFFu) {
                gameStats.totalGoldenAcorns++;
            }
            Sfx_OneUp();
        } else {
            Sfx_Pickup();
        }

        if (nutmeg.acorns < 99u) {
            nutmeg.acorns++;
        }
        gameStats.totalAcorns++;
		SpriteManagerRemoveSprite (THIS);
	}
}

void Destroy_SpriteAcorn(void) 
{
}

void SpriteAcornFreeze(Sprite *acorn) BANKED 
{
	acorn->custom_data[IS_STILL_POS] = true;
}