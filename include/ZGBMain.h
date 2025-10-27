#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateIncube8)\
_STATE(StateLogo)\
_STATE(StateTitle)\
_STATE(StateInitGame)\
_STATE(StateTreeCutscene)\
_STATE(StateLevel1)\
_STATE(StateLevel1b)\
_STATE(StateOverworld)\
_STATE(StateCutscene1)\
_STATE(StateCutscene2)\
_STATE(StateCutscene3)\
_STATE(StateCutsceneGordon)\
_STATE(StateTree)\
_STATE(StateLevel2)\
_STATE(StateGameOver)\
_STATE(StateLevel3)\
_STATE(StateLevel4)\
_STATE(StateLevel5)\
_STATE(StateLevel6)\
_STATE(StateLevel7)\
_STATE(StateLevel8)\
_STATE(StateW1Boss)\
_STATE(StateLevel2_1)\
_STATE(StateOverworldChange)\
_STATE(StateCredits)\
_STATE(StateLevelTree)\
_STATE(StateLevel2_2)\
_STATE(StateLevel2_glidefall)\
_STATE(StateLevel1_platform)\
_STATE(StateLevel2_platform)\
_STATE(StateLevel2_multi)\
_STATE(StateWaterLevel1)\
_STATE(StateIceLevel1)\
STATE_DEF_END

#define SPRITES \
_SPRITE_COLOR(SpriteFire, esofire)\
_SPRITE_COLOR(SpriteLeaf, leaf)\
_SPRITE_COLOR(SpriteAcorn, acorn)\
_SPRITE_COLOR(EnemyButterfly, butterfly)\
_SPRITE_COLOR(EnemyBunny, bunny)\
_SPRITE_COLOR(SpriteCamera, camera)\
_SPRITE_COLOR(SpriteNutmegTiny, nutmegtiny)\
_SPRITE_COLOR(SpriteNutHead, nuthead)\
_SPRITE_COLOR(SpriteOneUp, nuthead)\
_SPRITE_COLOR(SpriteStar, star)\
_SPRITE_COLOR(SpritePuff, puff)\
_SPRITE_COLOR(SpriteCinnamon, cinnamon)\
_SPRITE_COLOR(SpriteMaple, maple)\
_SPRITE_COLOR(SpriteIncube8G, incube8G)\
_SPRITE_COLOR(SpriteIncube8A, incube8A)\
_SPRITE_COLOR(SpriteIncube8M, incube8M)\
_SPRITE_COLOR(SpriteIncube8E, incube8E)\
_SPRITE_COLOR(SpriteIncube8S, incube8S)\
_SPRITE_COLOR(EnemyFish, fish)\
_SPRITE_COLOR(SpriteBlinkCinnamon, blink)\
_SPRITE_COLOR(SpriteBlinkMaple, blink)\
_SPRITE_COLOR(SpriteGordon1, gordon1)\
_SPRITE_COLOR(SpriteGordon2, gordon2)\
_SPRITE_COLOR(SpriteBlinkRuby, blink)\
_SPRITE_COLOR(SpriteBow, bow)\
_SPRITE_COLOR(SpriteRuby, ruby)\
_SPRITE_COLOR(SpriteLevelStart, levelStartSpr)\
_SPRITE_COLOR(SpriteGordonCamera, camera)\
_SPRITE_COLOR(SpritePowerLeaf, powerleaf)\
_SPRITE_COLOR(SpriteMushroom, mushroom)\
_SPRITE_COLOR(SpriteNutmegBow, nutmegbow)\
_SPRITE_COLOR(SpriteBowPickup, nutmegbow)\
_SPRITE_COLOR(EnemyRockith, rockith)\
_SPRITE_COLOR(EnemyTopSpike, topspike)\
_SPRITE_COLOR(SpriteNutmeg, nutmegSpr)\
_SPRITE_COLOR(EnemyBatty, batty)\
_SPRITE_COLOR(EnemyLightning, lightning)\
_SPRITE_COLOR(EnemyLightningSpot, lightningspot)\
_SPRITE_COLOR(EnemyEarthy, earthy)\
_SPRITE_COLOR(EnemyBirdy, birdy)\
_SPRITE_COLOR(SpriteBalloon, balloon)\
_SPRITE_COLOR(EnemyHand, hand)\
_SPRITE_COLOR(EnemySpatula, spatula)\
_SPRITE_COLOR(EnemyPopsicle, popsicle)\
_SPRITE_COLOR(EnemyCola, cola)\
_SPRITE_COLOR(SpriteShockline1, shockline1)\
_SPRITE_COLOR(SpriteShockline2, shockline2)\
_SPRITE_COLOR(SpriteShockline3, shockline3)\
_SPRITE_COLOR(SpritePlatform, platform)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif