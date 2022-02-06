#pragma bank 4
const unsigned char incube8GCGB[] = {
	0x00
};

const unsigned char incube8G_tiles[] = {
	//Frame 0
	0x24,0x18,0x00,0x7e,0x80,0x66,0x00,0xc0,
	0x00,0xce,0x80,0x66,0x00,0x7e,0x24,0x18
};

#include "TilesInfo.h"
const struct TilesInfoInternal incube8G_internal = {
	8, //width
	8, //height
	1, //num_tiles
	incube8G_tiles, //tiles
	incube8GCGB, //CGB palette
};
struct TilesInfo incube8G = {
	4, //bank
	&incube8G_internal, //data
};