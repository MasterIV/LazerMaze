#define EXPLOSION_SPEED 10

UWORD detonation_frames = 0;
UBYTE detonated = 0;
UBYTE mines[24];

void detonate_mines() {
	UBYTE i, j;
	
	for(i=0;i!=detonated;i++) {
		j = i<<1;
			
		set_sprite_tile(16+j, MineAnimation);
		move_sprite(16+j, mines[j]+4, mines[j+1]+4);	
		
		set_sprite_tile(17+j, MineRingAnimation);
		move_sprite(17+j, mines[j], mines[j+1]);
		set_sprite_prop(17+j, 0);
	}
	
	detonation_frames = 120;
}

void update_mines() {
	UBYTE i, j;
	UWORD current;
	detonation_frames--;
	
	if(detonation_frames == 0) {
		display_defeat();
		game_over_sound();
  		waitpad(255);
 		display_level();
	} else if(!(detonation_frames%EXPLOSION_SPEED)) {
		current = (detonation_frames/EXPLOSION_SPEED) % 4;
	
		for(i=0;i!=detonated;i++) {
			j = i<<1;
			set_sprite_tile(16+j, MineAnimation + current);
			
			switch (current) {
				case 0 :
				  set_sprite_prop(17+j, 0);
				  move_sprite(17+j, mines[j], mines[j+1]);
				  break;
				case 1 :
				  set_sprite_prop(17+j, S_FLIPX );
				  move_sprite(17+j, mines[j]+8, mines[j+1]);
				  break;
				case 2 :
				  set_sprite_prop(17+j, S_FLIPY |S_FLIPX );
				  move_sprite(17+j, mines[j]+8, mines[j+1]+8);
				  break;
				case 3 :
				  set_sprite_prop(17+j, S_FLIPY );
				  move_sprite(17+j, mines[j], mines[j+1]+8);
				  break;
			}
		}
	}
}
