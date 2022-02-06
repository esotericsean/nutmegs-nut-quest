#pragma bank 4
const unsigned char incube8ECGB[] = {
	0x00
};

const unsigned char incube8E_tiles[] = {
	//Frame 0
	0x42,0x3c,0x00,0x7e,0x00,0x60,0x00,0x7e,
	0x00,0x7e,0x00,0x60,0x00,0x7e,0x42,0x3c
};

#include "TilesInfo.h"
const struct TilesInfoInternal incube8E_internal = {
	8, //width
	8, //height
	1, //num_tiles
	incube8E_tiles, //tiles
	incube8ECGB, //CGB palette
};
struct TilesInfo incube8E = {
	4, //bank
	&incube8E_internal, //data
};