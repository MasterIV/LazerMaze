#include <gb/gb.h>
#include <stdio.h>
#include "tiles.c"
#include "sounds.c"

UBYTE level_objects[72];
UBYTE current_level[360];
UBYTE level = 0;

// bank 1: title screen
void show_title();
void display_title();
void show_victory();
void display_victory();
void show_defeat();
void display_defeat();

// bank 2: levels
void show_level(UBYTE level, UBYTE *dest);
void display_level();


#include "lazer.c"
#include "background.c"
#include "transition.c"
#include "cursor.c"

void display_title() {
  SWITCH_ROM_MBC1(1);
  show_title();
}

void display_level() {
  SWITCH_ROM_MBC1(2);
  DISPLAY_OFF;
  
  init_background(&current_level);
  show_level(level, level_objects);
  
  update_background(&level_objects, &current_level);
  set_bkg_tiles(0, 0, 20, 18, current_level);
	
  cursor_reset();
  DISPLAY_ON;  
}

void display_victory() {
  SWITCH_ROM_MBC1(1);
  show_victory();
}

void display_defeat() {
  SWITCH_ROM_MBC1(1);
  show_defeat();
}

void main() {  

  SPRITES_8x8;
  VBK_REG = 1;
  VBK_REG = 0;
  
  SHOW_BKG;
  
  display_title();
  DISPLAY_ON;  
  waitpad(255);
  
  printf(" \n Move the elements\n in the level to\n hit all objectives\n with the laser.\n\n");
  printf(" Use the arrors to\n movethe cursor.\n\n");
  printf(" Press A to move an\n element. Only some\n elements can be\n moved.\n\n");
  printf(" Press start to\n continue\n");
  
  waitpad(J_START);
  
  SHOW_SPRITES;
  display_level();
  cursor_init();
  init_sound();
  
  while(1) {
	cursor_update();
	wait_vbl_done();
  }
}
