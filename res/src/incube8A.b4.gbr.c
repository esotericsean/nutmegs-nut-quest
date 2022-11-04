#pragma bank 4
const unsigned char incube8ACGB[] = {
	0x00
};

const unsigned char incube8A_tiles[] = {
	//Frame 0
	0x28,0x10,0x00,0x38,0x44,0x38,0x00,0x6c,
	0x00,0x6c,0x82,0x7c,0x28,0xc6,0x00,0xc6
};

#include "TilesInfo.h"
const struct TilesInfoInternal incube8A_internal = {
	8, //width
	8, //height
	1, //num_tiles
	incube8A_tiles, //tiles
	incube8ACGB, //CGB palette
};
struct TilesInfo incube8A = {
	4, //bank
	&incube8A_internal, //data
};