#pragma bank 4
const unsigned char fishCGB[] = {
	0x06
};

const unsigned char fish_tiles[] = {
	//Frame 0
	0x00,0x00,0x00,0x00,0x03,0x03,0x3e,0x3d,
	0x4c,0x77,0x7a,0x4d,0x28,0x3f,0x3d,0x2b,
	0x39,0x2f,0x14,0x1b,0x04,0x07,0x06,0x05,
	0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xe0,0xe0,0x18,0xf8,0x04,0xfc,
	0x66,0xfe,0x32,0xfe,0x9e,0xe2,0x24,0xdc,
	0x78,0xf8,0x80,0xc0,0x30,0xf0,0x78,0xc8,
	0x78,0xb8,0xe0,0xa0,0x60,0x60,0x00,0x00
};

#include "TilesInfo.h"
const struct TilesInfoInternal fish_internal = {
	16, //width
	16, //height
	1, //num_tiles
	fish_tiles, //tiles
	fishCGB, //CGB palette
};
struct TilesInfo fish = {
	4, //bank
	&fish_internal, //data
};