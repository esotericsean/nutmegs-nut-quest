#include "Banks/SetAutoBank.h"

#include "BankManager.h"
#include "ZGBMain.h"
#include "../src/GlobalVars.h"

void Start_StateOverworldChange (void) 
{
	HIDE_BKG;
	HIDE_SPRITES;
	HIDE_WIN;
	fill_rect (0,0, 20, 18, 0x38);
}

// This stage exists to do a fade out and fade in when we are travelling between worlds on the overworld map
// ie between world 1 and 2.
// we just want to hop straight back to the overworld map
void Update_StateOverworldChange (void) 
{
	SetState(StateOverworld1);
}
