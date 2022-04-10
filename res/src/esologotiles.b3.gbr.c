#pragma bank 3
const unsigned char esologotilesCGB[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const unsigned char esologotiles_tiles[] = {
	//Frame 0
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,
	
	//Frame 1
	0xf8,0xf8,0xf0,0xf0,0xe7,0xe7,0xe0,0xe0,
	0xe7,0xe7,0xe3,0xe3,0xf0,0xf0,0xf8,0xf8,
	
	//Frame 2
	0x70,0x70,0x20,0x20,0x27,0x27,0x70,0x70,
	0xf8,0xf8,0x2f,0x2f,0x20,0x20,0x70,0x70,
	
	//Frame 3
	0x78,0x78,0x30,0x30,0xa6,0xa6,0xe7,0xe7,
	0x67,0x67,0x23,0x23,0x30,0x30,0x78,0x78,
	
	//Frame 4
	0xf0,0xf0,0x60,0x60,0x39,0x39,0x39,0x39,
	0x39,0x39,0x39,0x39,0x78,0x78,0xfc,0xfc,
	
	//Frame 5
	0x38,0x38,0x70,0x70,0xe7,0xe7,0xe0,0xe0,
	0xe7,0xe7,0xe3,0xe3,0x70,0x70,0xf8,0xf8,
	
	//Frame 6
	0x62,0x62,0x30,0x30,0x31,0x31,0x73,0x73,
	0xf3,0xf3,0x33,0x33,0x33,0x33,0x71,0x71,
	
	//Frame 7
	0x63,0x63,0x31,0x31,0x39,0x39,0xf9,0xf9,
	0xf9,0xf9,0xf9,0xf9,0xf8,0xf8,0xfc,0xfc,
	
	//Frame 8
	0xe1,0xe1,0xc0,0xc0,0x9c,0x9c,0x9f,0x9f,
	0x9f,0x9f,0x8c,0x8c,0xc0,0xc0,0x61,0x61,
	
	//Frame 9
	0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,
	0xfc,0xfc,0xf8,0xf8,0xf9,0xf9,0xf9,0xf9,
	
	//Frame 10
	0xff,0xff,0xff,0xff,0xff,0xff,0x3e,0x3e,
	0x1c,0x1c,0x8f,0x8f,0xcc,0xcc,0xc8,0xc8,
	
	//Frame 11
	0xff,0xff,0xff,0xff,0xff,0xff,0x18,0x18,
	0x0c,0x0c,0xcc,0xcc,0x0c,0x0c,0x0c,0x0c,
	
	//Frame 12
	0xff,0xff,0xff,0xff,0xff,0xff,0x99,0x99,
	0x00,0x00,0x44,0x44,0xcc,0xcc,0xcc,0xcc,
	
	//Frame 13
	0xff,0xff,0xff,0xff,0xff,0xff,0xe1,0xe1,
	0xc0,0xc0,0x9c,0x9c,0x81,0x81,0x9f,0x9f,
	
	//Frame 14
	0xff,0xff,0xff,0xff,0xff,0xff,0xc1,0xc1,
	0x80,0x80,0x9e,0x9e,0xc3,0xc3,0xe1,0xe1,
	
	//Frame 15
	0xf8,0xf8,0xfc,0xfc,0xfe,0xfe,0xff,0xff,
	0xfc,0xfc,0xfc,0xfc,0xfe,0xfe,0xff,0xff,
	
	//Frame 16
	0x89,0x89,0x18,0x18,0x0c,0x0c,0x8f,0x8f,
	0xcf,0xcf,0x1f,0x1f,0x3f,0x3f,0xff,0xff,
	
	//Frame 17
	0xcc,0xcc,0x0c,0x0c,0x5c,0x5c,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	
	//Frame 18
	0xcc,0xcc,0xcc,0xcc,0x4c,0x4c,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	
	//Frame 19
	0x8c,0x8c,0xc0,0xc0,0xe1,0xe1,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	
	//Frame 20
	0xbc,0xbc,0x80,0x80,0xc1,0xc1,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};

#include "TilesInfo.h"
const struct TilesInfoInternal esologotiles_internal = {
	8, //width
	8, //height
	21, //num_tiles
	esologotiles_tiles, //tiles
	esologotilesCGB, //CGB palette
};
struct TilesInfo esologotiles = {
	3, //bank
	&esologotiles_internal, //data
};