#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

UINT8 moveE;

void Start_SpriteIncube8E (void) 
{
    moveE = 0;
}

void Update_SpriteIncube8E (void) 
{
    if      (moveE == 10+1) TranslateSprite(THIS, 0, -1);
    else if (moveE == 15+1) TranslateSprite(THIS, 0, -1);
    else if (moveE == 20+1) TranslateSprite(THIS, 0, -1);
    else if (moveE == 25+1) TranslateSprite(THIS, 0, -1);
    else if (moveE == 30+1) TranslateSprite(THIS, 0, -1);
    else if (moveE == 37+1) TranslateSprite(THIS, 0, -1);
    else if (moveE == 47+1) TranslateSprite(THIS, 0, -1);

    moveE++;
}

void Destroy_SpriteIncube8E (void) 
{
}