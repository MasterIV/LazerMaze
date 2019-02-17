void check_transition() {
	UWORD x, y, objectives = 0, defeat = 0;
	UBYTE tile, exploded = MapMine + 4;
	
	for(x=1;x!=19;x+=2) 
		for(y=20;y!=340;y+=40) {
			tile = current_level[y+x];
			
			if(tile == MapObjective) 
				objectives++;
			if(tile == exploded) 
				defeat = 1;
		}
		
	if(defeat) {
		delay(500);
		display_defeat();
		game_over_sound();
  		waitpad(255);
 		display_level();
	} else if(!objectives) {
		delay(500);
		level++;
		display_victory();
  		waitpad(255);
 		display_level();
	}
	
	
}
