#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

static UINT8 leaf_counter;

static const UINT8 leaf_static[] = {1, 0};
static const UINT8 leaf_fall[]   = {16, 0, 0, 0, 1, 1, 2, 3, 3, 4, 4, 4, 3, 3, 2, 1, 1};

void Start_SpriteLeaf(void) {
	leaf_counter = 0;

	SetSpriteAnim(THIS, leaf_fall, 16);
}

void Update_SpriteLeaf(void) {
	if 		(leaf_counter == 2)   TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 5)   TranslateSprite (THIS, -1,  0);
	else if (leaf_counter == 6)   TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 10)  TranslateSprite (THIS, -1,  0);
	else if (leaf_counter == 12)  TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 18)  TranslateSprite (THIS,  0,  1);

	else if (leaf_counter == 24)  TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 27)  TranslateSprite (THIS,  1,  0);
	else if (leaf_counter == 34)  TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 36)  TranslateSprite (THIS,  1,  1);
	else if (leaf_counter == 42)  TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 50)  TranslateSprite (THIS,  1,  0);

	else if (leaf_counter == 60)  TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 65)  TranslateSprite (THIS, -1,  0);
	else if (leaf_counter == 70)  TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 80)  TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 85)  TranslateSprite (THIS, -1,  1);
	else if (leaf_counter == 90)  TranslateSprite (THIS,  0,  1);

	else if (leaf_counter == 100) TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 110) TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 115) TranslateSprite (THIS,  1,  0);
	else if (leaf_counter == 120) TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 130) TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 135) TranslateSprite (THIS,  1,  0);
	else if (leaf_counter == 140) TranslateSprite (THIS,  0,  1);

	else if (leaf_counter == 150) TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 160) TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 165) TranslateSprite (THIS, -1,  0);
	else if (leaf_counter == 170) TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 180) TranslateSprite (THIS,  0,  1);
	else if (leaf_counter == 190) TranslateSprite (THIS,  0,  1);

	else if (leaf_counter == 191) SetSpriteAnim(THIS, leaf_static, 1);
	else TranslateSprite (THIS,  0,  0);
	
	if (leaf_counter < 254) leaf_counter++;
}

void Destroy_SpriteLeaf(void) {
}