void check_transition() {
	UWORD x, y, objectives = 0;
	UBYTE tile, exploded = MapMine + 4;
	
	for(x=1;x!=19;x+=2) 
		for(y=20;y!=340;y+=40) {
			tile = current_level[y+x];
			
			if(tile == MapObjective) 
				objectives++;
			if(tile == exploded) {
				mines[detonated<<1] = (x<<3)+8;
				mines[(detonated<<1)+1] = ((y/20)<<3)+16;
				detonated++;
			}
		}
		
	if(detonated) {
		detonate_mines();
	} if(!objectives) {
		delay(500);
		level++;
		display_victory();
  		waitpad(255);
 		display_level();
	}
}
	

