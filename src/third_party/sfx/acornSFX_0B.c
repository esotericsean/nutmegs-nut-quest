/*

	SFX_0B

	Sound Effect File.
	
	Info:
		Length		:	3
		Priority		:	0
		Channels used	:	Noise channel
		SGB Support		:	No
*/

#include "Banks/SetAutoBank.h"
#include <gbdk/platform.h>
BANKREF(SFX_0B)
const unsigned char SFX_0B[] = {
0x80,0x03,0x81,0x22,0x80,0xF0,0x16,0x84,0x01,
0x80,0xF0,0x63,0x85,0x01,0x80,0xF0,0x0A,0x86
};
const UINT16 SFX_0B_Len = (UINT16)sizeof(SFX_0B);