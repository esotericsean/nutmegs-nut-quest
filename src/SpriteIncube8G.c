#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

UINT8 moveG;

void Start_SpriteIncube8G() {
    moveG = 0;
}

void Update_SpriteIncube8G() {
    if      (moveG == 10-5) TranslateSprite(THIS, 0, -1);
    else if (moveG == 15-5) TranslateSprite(THIS, 0, -1);
    else if (moveG == 20-5) TranslateSprite(THIS, 0, -1);
    else if (moveG == 25-5) TranslateSprite(THIS, 0, -1);
    else if (moveG == 30-5) TranslateSprite(THIS, 0, -1);
    else if (moveG == 37-5) TranslateSprite(THIS, 0, -1);
    else if (moveG == 47-5) TranslateSprite(THIS, 0, -1);

    moveG++;
}

void Destroy_SpriteIncube8G() {
}