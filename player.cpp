#include "player.hpp"
#include "ncurses.h"

extern long int deltaTime ;

player::player(int y, int x){
	// la posizione indica il torso del player
	this->pos.x = x ;
	this->pos.y = y ;

	this->yMod = 0 ;
	this->ySpeed = 0 ;

	// hitbox 3x3
	this->box.a.x = -1 ;
	this->box.a.y = -1 ;
	this->box.b.x = +1 ;
	this->box.b.y = +1 ;
}

void player::print(){
	for(int y=-1 ; y<=1 ; y++){
		for(int x=-1 ; x<=1 ; x++){
			mvprintw(y+this->pos.y, x+this->pos.x, "%c", texture[y+1][x+1]) ;
		}
	}
}

void player::move(char input){
	bool jump = false ;
	bool left = false ;
	bool right = false ;

	if( input=='a' ) left = true ;
	if( input=='d' ) right = true ;
	if( input=='A' ){
		left = true ;
		jump = true ;
	}
	if( input=='D' ){
		right = true ;
		jump = true ;
	}


	// horizontal
	if( left ){
		this->pos.x -= 1 ;
		//cleanup
		for(int y=this->pos.y-1 ; y<=this->pos.y+1 ; y++){
			mvprintw(y, this->pos.x+2, " ") ;
		}
	}else if( right ){
		this->pos.x += 1 ;
		// cleanup
		for(int y=-1 ; y<=1 ; y++){
			mvprintw(y+this->pos.y, this->pos.x-2, " ") ;
		}
	}

	// vertical
	if( jump ){
		this->ySpeed = -0.005 ; //jump vertical speed
	}


	this->ySpeed += 0.000001 ; // gravity //TODO deltaTime
	this->yMod += this->ySpeed ;

	if(this->yMod > 1){
		this->yMod -= 1 ;
		this->pos.y += 1 ;
		// cleanup
		for(int x=this->pos.x-1 ; x<=this->pos.x+1 ; x++){
			mvprintw(this->pos.y-2, x, " ") ;
		}
	}else if(this->yMod < -1){
		this->yMod += 1 ;
		this->pos.y -= 1 ;
		// cleanup
		for(int x=this->pos.x-1 ; x<=this->pos.x+1 ; x++){
			mvprintw(this->pos.y+2, x, " ") ;
		}
	}
}