#include "player.hpp"
#include "ncurses.h"

player::player(int x, int y){
	// la posizione indica il torso del player
	this->pos.x = x ;
	this->pos.y = y ;

	// hitbox 3x3
	this->box.NE.x = +1 ;
	this->box.NE.y = +1 ;
	this->box.SO.x = -1 ;
	this->box.SO.y = -1 ;
}

void player::print(){
	for(int y=5 ; y<=7 ; y++){
		for(int x=5 ; x<=7 ; x++){
			move(y, x) ;
			printw("%c", texture[y-5][x-5]) ;
		}
	}
}