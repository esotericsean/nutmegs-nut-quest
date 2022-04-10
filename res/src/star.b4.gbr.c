#pragma bank 4
const unsigned char starCGB[] = {
	0x02,0x02,0x02
};

const unsigned char star_tiles[] = {
	//Frame 0
	0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x0c,
	0x18,0x14,0x00,0x08,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 1
	0x00,0x00,0x12,0x12,0x14,0x1c,0x2c,0x34,
	0x7a,0x46,0x14,0x1c,0x10,0x10,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 2
	0x30,0x30,0x3f,0x2f,0x5d,0x63,0x9e,0xe2,
	0xf2,0xce,0x31,0x2f,0x2b,0x3b,0x30,0x30,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

#include "TilesInfo.h"
const struct TilesInfoInternal star_internal = {
	8, //width
	16, //height
	3, //num_tiles
	star_tiles, //tiles
	starCGB, //CGB palette
};
struct TilesInfo star = {
	4, //bank
	&star_internal, //data
};