#define MAP_SIZE 72
#define MAP_FACTOR 2
#define MAP_WIDTH 9
#define MAP_LINE 20
#define MAP_SQR 4

UBYTE lazer_map[72];

// draw the border, that never changes
void init_background(UBYTE *output) {
  	UBYTE i;

    for(i=0; i!=72; i++) {
		lazer_map[i] = 0;
  	}
  
  	output[0] = 84;
  	output[19] = 85;
  	output[340] = 86;
  	output[359] = 87;
	
	for(i=1; i!=19; i++) {
		output[i] = 80;
		output[340 + i] = 81;
  	}
	
	for(i=1; i!=17; i++) {
		output[i*20] = 82;
		output[i*20+19] = 83;
  	}
}

void update_background(UBYTE *maze, UBYTE *output) {
  	// UWORD i,j, offset, index;
//    UWORD i, offset, tile;
    UWORD x,y, offset, tile;

  	project_lazer(maze, lazer_map);
	
  
/**
	for(i = 0; i != MAP_SIZE; i++) {
		offset = (i % MAP_WIDTH) * MAP_FACTOR + ( i / MAP_WIDTH ) * 40U  + 21; // MAP_LINE*2 MAP_LINE+1

	 
	    tile = maze[i] + lazer_map[i];
	  	
		output[offset]            = tile;
	  	output[offset + 1]        = tile + 1;
	  	output[offset + MAP_LINE] = tile + 2;
	  	output[offset + 21]       = tile + 3;
	  
		
		//for(j = 0; j != MAP_SQR; j++) {
	  //		index = offset + j % MAP_FACTOR + (j / MAP_FACTOR) * MAP_LINE;
	  //		output[index] = maze[i] + lazer_map[i] * MAP_SQR + j;
	//	}
	
	}
		**/
	
	
	for(x = 0; x != 8; x++) {
		for(y = 0; y != 9; y++) {
			offset = y + (x<<3) + x ; //  y + x * MAP_WIDTH (9)
			tile = maze[offset] + lazer_map[offset];
			offset = (y << 1) + (x<<3) + (x<< 5)  + 21; //  x * 40 + y*2 + line+1

			output[offset]            = tile;
			output[offset + 1]        = tile + 1;
			output[offset + MAP_LINE] = tile + 2;
			output[offset + 21]       = tile + 3;
		}
	}
    
}

