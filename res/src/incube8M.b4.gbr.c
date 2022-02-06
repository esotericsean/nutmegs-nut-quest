#pragma bank 4
const unsigned char incube8MCGB[] = {
	0x00
};

const unsigned char incube8M_tiles[] = {
	//Frame 0
	0x00,0xc3,0x00,0xc3,0x00,0xe7,0x18,0xe7,
	0x00,0xff,0x24,0xdb,0x00,0xdb,0x18,0xc3
};

#include "TilesInfo.h"
const struct TilesInfoInternal incube8M_internal = {
	8, //width
	8, //height
	1, //num_tiles
	incube8M_tiles, //tiles
	incube8MCGB, //CGB palette
};
struct TilesInfo incube8M = {
	4, //bank
	&incube8M_internal, //data
};