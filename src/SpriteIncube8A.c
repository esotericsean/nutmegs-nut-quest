#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

UINT8 moveA;

void Start_SpriteIncube8A() {
    moveA = 0;
}

void Update_SpriteIncube8A() {
    if      (moveA == 10-3) TranslateSprite(THIS, 0, -1);
    else if (moveA == 15-3) TranslateSprite(THIS, 0, -1);
    else if (moveA == 20-3) TranslateSprite(THIS, 0, -1);
    else if (moveA == 25-3) TranslateSprite(THIS, 0, -1);
    else if (moveA == 30-3) TranslateSprite(THIS, 0, -1);
    else if (moveA == 37-3) TranslateSprite(THIS, 0, -1);
    else if (moveA == 47-3) TranslateSprite(THIS, 0, -1);

    moveA++;
}

void Destroy_SpriteIncube8A() {
}