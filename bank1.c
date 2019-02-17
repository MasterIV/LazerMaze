#include <gb/gb.h>

#include "title_pallet.tiles"
#include "title_img.map"
#include "complete_pallet.tiles"
#include "complete_img.map"

void reset_sprites() {
  int i;
  for(i = 0; i < 40; i++) {
	move_sprite(i, 0, 0);
  }
}

void show_victory() {
  DISPLAY_OFF;
  reset_sprites();
  set_bkg_data(0, 140, complete_pallet);
  set_bkg_tiles(0, 0, 20, 18, complete_img);
  DISPLAY_ON;
}

void show_title() {
  set_bkg_data(0, 140, title_pallet);
  set_bkg_tiles(0, 0, 20, 18, title_img);
}
