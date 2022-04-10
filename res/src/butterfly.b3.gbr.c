#pragma bank 3
const unsigned char butterflyCGB[] = {
	0x02,0x02,0x02,0x02
};

const unsigned char butterfly_tiles[] = {
	//Frame 0
	0x0d,0x0d,0x6e,0x72,0xfa,0x96,0x8d,0xff,
	0x73,0x7d,0x6e,0x5e,0x30,0x30,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 1
	0x0d,0x0d,0x6e,0x72,0xfa,0x96,0x8d,0xff,
	0x73,0x7d,0x6e,0x5e,0x30,0x30,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 2
	0x00,0x00,0x00,0x00,0x0d,0x0d,0x6e,0x72,
	0xe4,0x9c,0xb8,0xdc,0x70,0x70,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 3
	0x00,0x00,0x01,0x01,0x16,0x1e,0x2b,0x3d,
	0x37,0x79,0xde,0xee,0xf8,0x88,0x70,0x70,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

#include "TilesInfo.h"
const struct TilesInfoInternal butterfly_internal = {
	8, //width
	16, //height
	4, //num_tiles
	butterfly_tiles, //tiles
	butterflyCGB, //CGB palette
};
struct TilesInfo butterfly = {
	3, //bank
	&butterfly_internal, //data
};