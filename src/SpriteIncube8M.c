#include "Banks/SetBank4.h"
#include "SpriteManager.h"

UINT8 moveM;

void Start_SpriteIncube8M() {
    moveM = 0;
}

void Update_SpriteIncube8M() {
    if      (moveM == 10-1) TranslateSprite(THIS, 0, -1);
    else if (moveM == 15-1) TranslateSprite(THIS, 0, -1);
    else if (moveM == 20-1) TranslateSprite(THIS, 0, -1);
    else if (moveM == 25-1) TranslateSprite(THIS, 0, -1);
    else if (moveM == 30-1) TranslateSprite(THIS, 0, -1);
    else if (moveM == 37-1) TranslateSprite(THIS, 0, -1);
    else if (moveM == 47-1) TranslateSprite(THIS, 0, -1);

    moveM++;
}

void Destroy_SpriteIncube8M() {
}