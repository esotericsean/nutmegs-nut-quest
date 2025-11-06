/*

	SFX_0D

	Sound Effect File.
	
	Info:
		Length		:	3
		Priority		:	0
		Channels used	:	Duty channel 2
		SGB Support		:	No
*/

#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>
BANKREF(SFX_0D)
const unsigned char SFX_0D[] = {
0x20,0x03,0x84,0x88,0x0F,0x30,0x02,0x0A,0x20,
0x01,0x06,0x20
};
const UINT16 SFX_0D_Len = (UINT16)sizeof(SFX_0D);