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
	for(int y=this->pos.y-1 ; y<=this->pos.y+1 ; y++){
		for(int x=this->pos.x-1 ; x<=this->pos.x+1 ; x++){
			move(y, x) ;
			printw("%c", texture[y-pos.y+1][x-pos.x+1]) ;
		}
	}
}