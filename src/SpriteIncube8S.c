#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

UINT8 moveS;

void Start_SpriteIncube8S (void) 
{
    moveS = 0;
}

void Update_SpriteIncube8S (void) 
{
    if      (moveS == 10+3) TranslateSprite(THIS, 0, -1);
    else if (moveS == 15+3) TranslateSprite(THIS, 0, -1);
    else if (moveS == 20+3) TranslateSprite(THIS, 0, -1);
    else if (moveS == 25+3) TranslateSprite(THIS, 0, -1);
    else if (moveS == 30+3) TranslateSprite(THIS, 0, -1);
    else if (moveS == 37+3) TranslateSprite(THIS, 0, -1);
    else if (moveS == 47+3) TranslateSprite(THIS, 0, -1);

    moveS++;
}

void Destroy_SpriteIncube8S (void) 
{
}