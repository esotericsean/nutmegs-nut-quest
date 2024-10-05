#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "GlobalVars.h"
#include "SpriteNutmeg.h"



void Start_StateInitGame(void)
{
	nutmeg_SetupGame();
}

void Update_StateInitGame (void) 
{
	//SetState(StateLevelTree);
	SetState(StateWaterLevel1);
}

void Destroy_StateInitGame(void)
{
	
}