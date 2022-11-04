#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateIncube8)\
_STATE(StateLogo)\
_STATE(StateTitle)\
_STATE(StateTreeCutscene)\
_STATE(StateLevel1)\
_STATE(StateOverworld1)\
_STATE(StateCutscene1)\
_STATE(StateCutscene2)\
_STATE(StateCutscene3)\
_STATE(StateCutsceneGordon)\
_STATE(StateTree)\
_STATE(StateLevel2)\
_STATE(StateGameOver)\
_STATE(StateLevel3)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpriteFire, esofire)\
_SPRITE_DMG(SpriteLeaf, leaf)\
_SPRITE_DMG(SpriteAcorn, acorn)\
_SPRITE_DMG(EnemyButterfly, butterfly)\
_SPRITE_DMG(EnemyBunny, bunny)\
_SPRITE_DMG(SpriteCamera, camera)\
_SPRITE_DMG(SpriteNutmeg1, nutmeg1)\
_SPRITE_DMG(SpriteNutmeg2, nutmeg2)\
_SPRITE_DMG(SpriteNutmegTiny, nutmegtiny)\
_SPRITE_DMG(SpriteNutHead, nuthead)\
_SPRITE_DMG(SpriteStarLeft, star)\
_SPRITE_DMG(SpriteStarRight, star)\
_SPRITE_DMG(SpritePuffLeft, puff)\
_SPRITE_DMG(SpritePuffRight, puff)\
_SPRITE_DMG(SpriteCinnamon, cinnamon)\
_SPRITE_DMG(SpriteMaple, maple)\
_SPRITE_DMG(SpriteIncube8G, incube8G)\
_SPRITE_DMG(SpriteIncube8A, incube8A)\
_SPRITE_DMG(SpriteIncube8M, incube8M)\
_SPRITE_DMG(SpriteIncube8E, incube8E)\
_SPRITE_DMG(SpriteIncube8S, incube8S)\
_SPRITE_DMG(EnemyFish, fish)\
_SPRITE_DMG(SpriteBlinkCinnamon, blink)\
_SPRITE_DMG(SpriteBlinkMaple, blink)\
_SPRITE_DMG(SpriteGordon1, gordon1)\
_SPRITE_DMG(SpriteGordon2, gordon2)\
_SPRITE_DMG(SpriteBlinkRuby, blink)\
_SPRITE_DMG(SpriteBow, bow)\
_SPRITE_DMG(SpriteRuby, ruby)\
_SPRITE_DMG(SpriteGordonCamera, camera)\
_SPRITE_DMG(SpritePowerLeaf, powerleaf)\
_SPRITE_DMG(SpriteMushroom, mushroom)\
_SPRITE_DMG(SpriteNutmegBow, nutmegbow)\
_SPRITE_DMG(EnemyRockith, rockith)\
_SPRITE_DMG(EnemyTopSpike, topspike)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif