#pragma bank 6
const unsigned char mushroomCGB[] = {
	0x00,0x00
};

const unsigned char mushroom_tiles[] = {
	//Frame 0
	0x7e,0x7e,0x09,0xf7,0xa0,0xdf,0x84,0xfb,
	0xe9,0xff,0x42,0x42,0x40,0x42,0x10,0x3c,
	
	//Frame 1
	0x00,0x00,0x7e,0x7e,0x09,0xf7,0xa0,0xdf,
	0x84,0xfb,0xe9,0xff,0x40,0x42,0x10,0x3c
};

#include "TilesInfo.h"
const struct TilesInfoInternal mushroom_internal = {
	8, //width
	8, //height
	2, //num_tiles
	mushroom_tiles, //tiles
	mushroomCGB, //CGB palette
};
struct TilesInfo mushroom = {
	6, //bank
	&mushroom_internal, //data
};