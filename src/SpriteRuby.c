#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

UINT8 ruby_counter;
const UINT8 anim_ruby_idle[] = {5, 0, 0, 0, 0, 1};

void Start_SpriteRuby() {
	ruby_counter = 0;

	SetSpriteAnim(THIS, anim_ruby_idle, 8);
}

void Update_SpriteRuby() {
}

void Destroy_SpriteRuby() {
}