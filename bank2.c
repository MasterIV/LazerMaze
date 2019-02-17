#include <gb/gb.h>
#include "sprites.tiles"
#include "tiles.c"
#include "levels.c"

void copy_map(UBYTE *dest, UBYTE *src) {
  UBYTE i;
  for(i = 0; i != 72; i++) {
	dest[i] = src[i];
  }
}

void show_level(UBYTE level, UBYTE *dest) {
  set_sprite_data(0, 200, sprites);
  set_bkg_data(0, 200, sprites);
  
  switch(level) {
  	case 0: 
		copy_map(dest, &level1);
		break;
	case 1: 
		copy_map(dest, &level2);
		break;
	case 2: 
		copy_map(dest, &level3);
		break;
		
	
  	default: 	
		copy_map(dest, &level1);
  }
}
