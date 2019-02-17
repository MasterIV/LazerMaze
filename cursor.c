#define CURSOR_X_MIN 8
#define CURSOR_X_MAX 136
#define CURSOR_Y_MIN 16
#define CURSOR_Y_MAX 128
#define CURSOR_SPEED 8

struct Cursor {
  UBYTE x;
  UBYTE y;
  BYTE dir_x;
  BYTE dir_y;
} cursor;

UBYTE selected ;
UBYTE counter ;

void cursor_toggle() {
  UBYTE currentObject;
  UBYTE x = (cursor.x - CURSOR_X_MIN) / 16;
  UBYTE y = (cursor.y - CURSOR_Y_MIN) / 16;
  UBYTE index = x + y * 9;
  
  cursor.dir_x = 0;
  cursor.dir_y = 0;
  counter = CURSOR_SPEED;
  
  currentObject = level_objects[index];
  if(selected) {
	if(currentObject != MapEmpty)
	  return;
	
	set_sprite_tile(5, 0);
	set_sprite_tile(6, 0);
	set_sprite_tile(9, 0);
	set_sprite_tile(10, 0);
	
	
	level_objects[index] = selected;
	selected = 0;
	
	update_background(&level_objects, &current_level);
	set_bkg_tiles(0, 0, 20, 18, current_level);
	check_transition();
  } else {
	if(
	  currentObject != MapMirrorLeft && 
	  currentObject != MapMirrorRight && 
	  currentObject != MapMovableObstacle && 
	  currentObject != MapMovableEmpty && 
	  currentObject != MapSplitterLeft && 
	  currentObject != MapSplitterDown && 
	  currentObject != MapSplitterUp && 
	  currentObject != MapSplitterRight
	) return;
	
	selected = currentObject;
	level_objects[index] = MapEmpty;
	
	set_sprite_tile(5, selected);
	set_sprite_tile(6, selected+1);
	set_sprite_tile(9, selected+2);
	set_sprite_tile(10, selected+3);
	
	update_background(&level_objects, &current_level);
	set_bkg_tiles(0, 0, 20, 18, &current_level);
	check_transition();
  }
}

void cursor_move(WORD x, WORD y) {
  WORD destx = cursor.x + x * CURSOR_SPEED;
  WORD desty = cursor.y + y * CURSOR_SPEED;
  WORD destindex;
  
  // don't move out the map
  if(destx < CURSOR_X_MIN || destx > CURSOR_X_MAX || desty < CURSOR_Y_MIN || desty > CURSOR_Y_MAX) 
	return;
  
  // when item is selected you can only move through empty tiles
  
  destindex = ((desty - CURSOR_Y_MIN) >>4 ) ; // ((desty - CURSOR_Y_MIN) >>4 )
  destindex += ((destx - CURSOR_X_MIN) >>4) + (destindex << 3); // destindex += destindex<<3 === destindex*9 
  if(selected && level_objects[destindex] != MapEmpty)
	return;
  
  cursor.dir_x = x;
  cursor.dir_y = y;
  counter = CURSOR_SPEED;
}

void cursor_update() {
  UBYTE keys, i, j;
  keys = joypad();
  
  if(counter == 0) {
	switch(keys) {
	  case J_UP: cursor_move(0, -2); break;
	  case J_DOWN: cursor_move(0, 2); break;
	  case J_LEFT: cursor_move(-2, 0); break;
	  case J_RIGHT: cursor_move(2, 0); break;
	  case J_A: cursor_toggle(); break;
	}
  } else {
	cursor.x += cursor.dir_x;
	cursor.y += cursor.dir_y;
	counter--;
  }

  for(i=0;i!=4;i++) {
  	for(j=0;j!=4;j++) {
		//i{0-15}	move_sprite(i, cursor.x + 8 * (i%4), cursor.y + 8 * (i/4));	
		move_sprite((i<<2)+j, cursor.x + (j<<3), cursor.y +  (i<<3));	
	}
  }
}

void cursor_reset() {
  counter = 0;
  selected = 0;
  cursor.x = CURSOR_X_MIN;
  cursor.y = CURSOR_Y_MIN;
  cursor.dir_x = 0;
  cursor.dir_y = 0;
}

void cursor_init() {
  // top left of cursor
  set_sprite_tile(0, 1);
  set_sprite_tile(1, 2);
  set_sprite_tile(4, 3);

  // top right of cursor
  set_sprite_tile(2, 2);
  set_sprite_prop(2, S_FLIPX);
  set_sprite_tile(3, 1);
  set_sprite_prop(3, S_FLIPX);
  set_sprite_tile(7, 3);
  set_sprite_prop(7, S_FLIPX);

  // bottom left of cursor
  set_sprite_tile(8, 3);
  set_sprite_prop(8, S_FLIPY);
  set_sprite_tile(12, 1);
  set_sprite_prop(12, S_FLIPY);
  set_sprite_tile(13, 2);
  set_sprite_prop(13, S_FLIPY);

  // bottom right of cursor
  set_sprite_tile(11, 3);
  set_sprite_prop(11, S_FLIPX | S_FLIPY);
  set_sprite_tile(14, 2);
  set_sprite_prop(14, S_FLIPX | S_FLIPY);
  set_sprite_tile(15, 1);
  set_sprite_prop(15, S_FLIPX | S_FLIPY);
  
  // transparent part of cursor
  set_sprite_tile(5, 0);
  set_sprite_tile(6, 0);
  set_sprite_tile(9, 0);
  set_sprite_tile(10, 0);
  
  cursor_update();
}
