void check_transition() {
	UWORD x, objectives = 0;
	UBYTE tile, exploded = MapMine + 4;
	
	if (!defeat) {
		for(x=0;x!=72;x++) {
			tile = level_objects[x];
			if(tile == MapObjective && !lazer_map[x]) 
				objectives++;
			if(tile == MapMine && lazer_map[x]) {
				defeat = 1;
				break;
			}
		}
		
	}
		
	if (defeat == 1 ) { // on first defeat
		explosion_sound();
	}
		
	if(defeat) {
		defeat++;
		// play animation
		if (defeat % 10 == 0) {
			x =(defeat / 10) % 4;
			set_sprite_tile(16, MineAnimation + x);
			move_sprite(16, 64+4, 24+4);	
			set_sprite_tile(17, MineRingAnimation);
			explosion_sound();
			
			switch (x) {
				case 0 :
				  set_sprite_prop(17, 0 );

				  move_sprite(17, 64, 24);
				  break;
			
				case 1 :
				  set_sprite_prop(17, S_FLIPX );
				  move_sprite(17, 64+8, 24);
				  break;
				case 2 :
				  set_sprite_prop(17,  S_FLIPY |S_FLIPX );
				  move_sprite(17, 64+8, 24+8);
				  break;
				case 3 :
				  set_sprite_prop(17,S_FLIPY );
				  move_sprite(17, 64, 24+8);
				  break;
		
			}


		}

	}
	
	if (defeat == 200) { // go to defeat screen
		display_defeat();
		game_over_sound();
  		waitpad(255);
 		display_level();
		return;
	}
	
	if(!defeat && !objectives) {
		delay(500);
		level++;
		display_victory();
		victory_sound();
  		waitpad(255);
 		display_level();
	}
	
	
}
