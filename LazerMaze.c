#include <gb/gb.h>
#include <stdio.h>
#include "tiles.c"
#include "sounds.c"


// bank 1: title screen
void show_title();
void display_title();
void show_victory();
void display_victory();
void show_defeat();
void display_defeat();
void show_end();
void display_end();

// bank 2: levels
void show_level(UBYTE level, UBYTE *dest);
void display_level();

UBYTE level_objects[72];
UBYTE current_level[360];
UBYTE level = 0;
UBYTE loop = 1;

#include "lazer.c"
#include "background.c"
#include "mines.c"
#include "transition.c"
#include "cursor.c"

void display_title() {
  SWITCH_ROM_MBC1(1);
  show_title();
}

void display_end() {
  SWITCH_ROM_MBC1(1);
  show_end();
}

void display_level() {
  if(level > 10 ) {
  	loop = 0;
	display_end();
	return;
  }

  SWITCH_ROM_MBC1(2);
  DISPLAY_OFF;

  init_background(&current_level);
  show_level(level, level_objects);
  
  update_background(&level_objects, &current_level);
  set_bkg_tiles(0, 0, 20, 18, current_level);
  detonated = 0;
	
  cursor_reset();
  DISPLAY_ON;  
}

void display_victory() {
  SWITCH_ROM_MBC1(1);
  show_victory();
  victory_sound();
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
  init_sound();
  
  display_title();
  DISPLAY_ON;
  title_sound();
  waitpad(255);
  explosion_sound();
  
  printf(" \n Move the elements\n in the level to\n hit all objectives\n with the laser.\n\n");
  printf(" Use the arrows to\n move the cursor.\n\n");
  printf(" Press A to move an\n element. Only some\n elements can be\n moved.\n\n");
  printf(" Press start to\n continue\n");
  
  waitpad(J_START);
  
  SHOW_SPRITES;
  display_level();
  cursor_init();
  
  while(loop) {
    if (detonated) {
		update_mines();
	} else {
		cursor_update();
	}

	update_music();
	wait_vbl_done();
  }
}
