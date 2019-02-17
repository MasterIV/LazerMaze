// Lazer state x 4 for tile number
#define LAZER_STATE_NONE 0
#define LAZER_STATE_NORMAL 4
#define LAZER_STATE_OTHER 8

#define LAZER_DIRECTION_STOP 0
#define LAZER_DIRECTION_NORTH 1
#define LAZER_DIRECTION_EAST 2
#define LAZER_DIRECTION_SOUTH 4
#define LAZER_DIRECTION_WEST 8

UWORD row_col_to_cel(UWORD row, UWORD col) {
	return (row<<3) + row + col;
}

UBYTE determine_next_lazer_stat(UBYTE object, UBYTE old_direction) {
  switch(object) {
	case MapMirrorLeft:
		switch (old_direction) {
		  case LAZER_DIRECTION_NORTH:
		  case LAZER_DIRECTION_EAST:
		  	return LAZER_STATE_NORMAL;
		  case LAZER_DIRECTION_SOUTH:
		  case LAZER_DIRECTION_WEST:
		  	return LAZER_STATE_OTHER;
		  default:
		    return LAZER_STATE_NONE;
		}	
	case MapMirrorRight:
		switch (old_direction) {
		  case LAZER_DIRECTION_NORTH:
		  case LAZER_DIRECTION_WEST:
		  	return LAZER_STATE_NORMAL;
		  case LAZER_DIRECTION_EAST:
		  case LAZER_DIRECTION_SOUTH:
		  	return LAZER_STATE_OTHER;
		  default:
		    return LAZER_STATE_NONE;
		}
	case MapSplitterDown:
		if (old_direction == LAZER_DIRECTION_SOUTH) {
		  	return LAZER_STATE_NORMAL;
		}
		return LAZER_STATE_NONE;
	case MapSplitterLeft:	
		if (old_direction == LAZER_DIRECTION_WEST) {
		  	return LAZER_STATE_NORMAL;
		}
		return LAZER_STATE_NONE;
	case MapSplitterRight:
		if (old_direction == LAZER_DIRECTION_EAST) {
		  	return LAZER_STATE_NORMAL;
		}
		return LAZER_STATE_NONE;
	case MapSplitterUp:
		if (old_direction == LAZER_DIRECTION_NORTH) {
		  	return LAZER_STATE_NORMAL;
		}
		return LAZER_STATE_NONE;
	case MapEmpty:
	case MapMovableEmpty:
	 	switch (old_direction) {
		  case LAZER_DIRECTION_NORTH:
		  case LAZER_DIRECTION_SOUTH:
		  	return LAZER_STATE_NORMAL;
		  case LAZER_DIRECTION_EAST:
		  case LAZER_DIRECTION_WEST:
		  	return LAZER_STATE_OTHER;
		  default:
		    return LAZER_STATE_NONE;
		}
	case MapObjective:
	case MapMine:
		return LAZER_STATE_NORMAL;

  }
  return LAZER_STATE_NONE;
}

UBYTE determine_next_direction(UBYTE object, UBYTE old_direction) {
  switch(object) {
	case MapObstacle: 
	case MapMovableObstacle: 
	case MapGenerator: 
	case MapObjective: 
	case MapMine:
		return LAZER_DIRECTION_STOP;
	case MapMirrorLeft:
		switch (old_direction) {
		  case LAZER_DIRECTION_NORTH:
		  	return LAZER_DIRECTION_WEST;
		  case LAZER_DIRECTION_EAST:
		  	return LAZER_DIRECTION_SOUTH;
		  case LAZER_DIRECTION_SOUTH:
		  	return LAZER_DIRECTION_EAST;
		  case LAZER_DIRECTION_WEST:
		  	return LAZER_DIRECTION_NORTH;
		  default:
		    return LAZER_DIRECTION_STOP;
		}	
	case MapMirrorRight:
		switch (old_direction) {
		  case LAZER_DIRECTION_NORTH:
		  	return LAZER_DIRECTION_EAST;
		  case LAZER_DIRECTION_EAST:
		  	return LAZER_DIRECTION_NORTH;
		  case LAZER_DIRECTION_SOUTH:
		  	return LAZER_DIRECTION_WEST;
		  case LAZER_DIRECTION_WEST:
		  	return LAZER_DIRECTION_SOUTH;
		  default:
		    return LAZER_DIRECTION_STOP;
		}
	case MapSplitterDown:
		if (LAZER_DIRECTION_SOUTH==old_direction) {
		  return LAZER_DIRECTION_EAST | LAZER_DIRECTION_WEST;
		}
		return LAZER_DIRECTION_STOP;
	
	case MapSplitterLeft:
		if (LAZER_DIRECTION_WEST==old_direction) {
		  return LAZER_DIRECTION_NORTH | LAZER_DIRECTION_SOUTH;
		}
		return LAZER_DIRECTION_STOP;
	
	case MapSplitterRight:
		if (LAZER_DIRECTION_EAST==old_direction) {
		  return LAZER_DIRECTION_NORTH | LAZER_DIRECTION_SOUTH;
		}
		return LAZER_DIRECTION_STOP;
	
	case MapSplitterUp:
		if (LAZER_DIRECTION_NORTH==old_direction) {
		  return LAZER_DIRECTION_EAST | LAZER_DIRECTION_WEST;
		}
		return LAZER_DIRECTION_STOP;
  }
  return old_direction;
}

void determine_lazer_path(UBYTE *maze, UBYTE *lazer_map, UBYTE direction,UBYTE x,UBYTE y) {
	UWORD row;
    UWORD col;
	UWORD next_row;
    UWORD next_col;
    UWORD next_cell;
    UBYTE next_direction;
	UBYTE next_object;
	UBYTE next_lazer_state;
	UBYTE curr_lazer_state;
	
    row = y;
    col = x;
  
 	next_row = row;
	next_col = col;

	switch(direction) {
	case 0: return; // stop moving
	case 1:
		if (row != 0) {
			next_row--;
		}
		break;
	case 2:
		if (col != 8) {
			next_col++;
		}
		break;
	case 4:
		if (row != 7) {
			next_row++;
		}
		break;
	case 8:
		if (col != 0) {
			next_col--;
		}
		break;
	default:
	  	return;
  }

   // if position did not change, end
  if (next_row == row && next_col == col) {
  	return;
  }

  next_cell = row_col_to_cel(next_row, next_col);

  next_object = maze[next_cell];
  next_direction = determine_next_direction(next_object, direction);

  // depending on object, different lazer state
  curr_lazer_state = lazer_map[next_cell];

  // update lazer map LAZER_STATE_NORMAL
  next_lazer_state = determine_next_lazer_stat(next_object, direction);
  lazer_map[next_cell] |= next_lazer_state; 
  
  // (curr_lazer_state | add_state) == add_state
  if (next_lazer_state == 0 || (curr_lazer_state & next_lazer_state == curr_lazer_state)) {
  	return;
  }

  // next recursion with next direction
 
  if ((next_direction & LAZER_DIRECTION_NORTH) != 0 ) {
	  determine_lazer_path(maze, lazer_map, LAZER_DIRECTION_NORTH,next_col,next_row);
  }
 
  if ((next_direction & LAZER_DIRECTION_EAST) != 0 ) {
	  determine_lazer_path(maze,lazer_map, LAZER_DIRECTION_EAST,next_col,next_row);
  }
  
  if ((next_direction & LAZER_DIRECTION_SOUTH) != 0 ) {
	  determine_lazer_path(maze,lazer_map, LAZER_DIRECTION_SOUTH,next_col,next_row);
  }
  
  if ((next_direction & LAZER_DIRECTION_WEST) != 0 ) {
	  determine_lazer_path(maze,lazer_map, LAZER_DIRECTION_WEST,next_col,next_row);
  }
}

void project_lazer(UBYTE *maze, UBYTE *output) {
	UWORD startIdx;

	UBYTE lazer_direction,x,y;
  	/* 72 input 360 output
  	 given objects eg25, output tilemap 25,26/27,28
	 */
  
    /* clear lazer map*/
    startIdx = 0;
	for (; startIdx != 72; startIdx++) {
		output[startIdx] = 0;
 	}

  
  	/* find start MapStart. Assumes that start is always present */
  
  
    startIdx = 0;
  	for (; startIdx != 72; startIdx++) {
		if (maze[startIdx] == MapGenerator) {
			break;
		}
 	}

	x = startIdx % 9;
	y = startIdx / 9;
 
 	/* given start cel, find row and column */
 
  	/* from start and direction */
   lazer_direction = LAZER_DIRECTION_NORTH;

   determine_lazer_path(maze, output, lazer_direction,x,y);    
}




