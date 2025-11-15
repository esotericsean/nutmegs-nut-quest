#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "GlobalVars.h"
#include "SpriteNutmeg.h"

void Start_StateInitGame(void)
{
	nutmeg_SetupGame();
	SetState(StateIncube8);
}

void Update_StateInitGame (void) 
{
	// immediate hand-off in Start
}

void Destroy_StateInitGame(void)
{
	
}