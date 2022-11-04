#pragma bank 4
const unsigned char incube8SCGB[] = {
	0x00
};

const unsigned char incube8S_tiles[] = {
	//Frame 0
	0x04,0x38,0x42,0x3c,0x00,0x66,0x48,0x30,
	0x12,0x0c,0x00,0x66,0x42,0x3c,0x20,0x1c
};

#include "TilesInfo.h"
const struct TilesInfoInternal incube8S_internal = {
	8, //width
	8, //height
	1, //num_tiles
	incube8S_tiles, //tiles
	incube8SCGB, //CGB palette
};
struct TilesInfo incube8S = {
	4, //bank
	&incube8S_internal, //data
};