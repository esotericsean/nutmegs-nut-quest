#pragma bank 3
const unsigned char leafCGB[] = {
	0x01,0x01,0x01,0x01,0x01
};

const unsigned char leaf_tiles[] = {
	//Frame 0
	0x00,0x02,0x06,0x18,0x39,0x06,0x36,0x09,
	0x4f,0x30,0x6f,0x10,0x56,0x28,0x38,0x40,
	
	//Frame 1
	0x00,0x04,0x06,0x18,0x38,0x06,0x36,0x09,
	0x2f,0x50,0x66,0x18,0x58,0x24,0x10,0x20,
	
	//Frame 2
	0x00,0x08,0x3c,0x00,0x42,0x3c,0x34,0x4a,
	0x76,0x08,0x0c,0x30,0x30,0x0c,0x08,0x10,
	
	//Frame 3
	0x00,0x10,0x30,0x0c,0x0e,0x30,0x36,0x48,
	0x7a,0x05,0x33,0x0c,0x0d,0x12,0x04,0x02,
	
	//Frame 4
	0x00,0x20,0x30,0x0c,0x4e,0x30,0x36,0x48,
	0x79,0x06,0x7b,0x04,0x35,0x0a,0x0e,0x01
};

#include "TilesInfo.h"
const struct TilesInfoInternal leaf_internal = {
	8, //width
	8, //height
	5, //num_tiles
	leaf_tiles, //tiles
	leafCGB, //CGB palette
};
struct TilesInfo leaf = {
	3, //bank
	&leaf_internal, //data
};