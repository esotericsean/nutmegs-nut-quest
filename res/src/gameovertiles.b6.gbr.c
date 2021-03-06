#pragma bank 6
const unsigned char gameovertilesCGB[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const unsigned char gameovertiles_tiles[] = {
	//Frame 0
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,
	
	//Frame 1
	0x00,0xff,0x00,0xe7,0x00,0xdb,0x00,0xdf,
	0x00,0xd3,0x00,0xdb,0x00,0xdb,0x00,0xe7,
	
	//Frame 2
	0x00,0xff,0x00,0xff,0x00,0xe7,0x00,0xdb,
	0x00,0xfb,0x00,0xe3,0x00,0xdb,0x00,0xe5,
	
	//Frame 3
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xd7,
	0x00,0xab,0x00,0xab,0x00,0xbb,0x00,0xbb,
	
	//Frame 4
	0x00,0xff,0x00,0xff,0x00,0xe7,0x00,0xdb,
	0x00,0xdb,0x00,0xc7,0x00,0xdf,0x00,0xe3,
	
	//Frame 5
	0x00,0xff,0x00,0xe7,0x00,0xdb,0x00,0xdb,
	0x00,0xdb,0x00,0xdb,0x00,0xdb,0x00,0xe7,
	
	//Frame 6
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xbb,
	0x00,0xbb,0x00,0xd7,0x00,0xd7,0x00,0xef,
	
	//Frame 7
	0x00,0xff,0x00,0xff,0x00,0xe7,0x00,0xdb,
	0x00,0xdf,0x00,0xdf,0x00,0xdf,0x00,0xdf,
	
	//Frame 8
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xdf,
	
	//Frame 9
	0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,
	0x00,0xff,0x00,0x83,0x00,0xc7,0x00,0xef,
	
	//Frame 10
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};

#include "TilesInfo.h"
const struct TilesInfoInternal gameovertiles_internal = {
	8, //width
	8, //height
	11, //num_tiles
	gameovertiles_tiles, //tiles
	gameovertilesCGB, //CGB palette
};
struct TilesInfo gameovertiles = {
	6, //bank
	&gameovertiles_internal, //data
};