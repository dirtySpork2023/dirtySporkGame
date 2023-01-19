#ifndef PLAYER_CPP
#define PLAYER_CPP

#include <ncurses.h>
#include "lib.hpp"
#include "bullet.hpp"
#include "player.hpp"

player::player(int y, int x, double gunFireRate, int gunDamage, int health){
	this->hp = health ;
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
	this->facing = true ; // destra

	this->B = bullet();
	this->B.texture = 'o' ;
	this->fireRate = gunFireRate ; // 0.25 = 4 colpi al secondo
	this->damage = gunDamage ;
}

void player::print(){
	//bullets
	B.print();

	//player
	for(int y=-1 ; y<=1 ; y++){
		for(int x=-1 ; x<=1 ; x++){
			if( facing ){
				mvprintw(y+this->pos.y, x+this->pos.x, "%c", texture[y+1][x+1]) ;
			}else{
				mvprintw(y+this->pos.y, x+this->pos.x, "%c", reverse[y+1][x+1]) ;
			}
		}
	}
}

void player::move(char input, long int deltaTime){
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
	if( input=='w' ){
		jump = true ;
	}
	if( input=='F' ){
		jump = true ;
	}


	// horizontal
	if( left ){
		facing = false ;
		this->pos.x -= 1 ;
		//cleanup
		for(int y=this->pos.y-1 ; y<=this->pos.y+1 ; y++){
			mvprintw(y, this->pos.x+2, " ") ;
		}
	}else if( right ){
		facing = true ;
		this->pos.x += 1 ;
		// cleanup
		for(int y=-1 ; y<=1 ; y++){
			mvprintw(y+this->pos.y, this->pos.x-2, " ") ;
		}
	}

	// vertical
	if( jump && this->pos.y >= 30 ){
		this->ySpeed = -0.0035 ; //jump vertical speed
	}


	this->ySpeed += 0.025 / deltaTime ;
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

void player::shoot(bool input, long int deltaTime){
	static long elapsed = 0 ;
	double secondsElapsed = elapsed/(double)1000000000 ;
	if( input==true && this->fireRate < secondsElapsed ){
		elapsed = 0 ;
		if( facing==true ){
			this->B.add(this->pos, +500, this->damage) ;
		}else{
			this->B.add(this->pos, -500, this->damage) ;
		}
	}
	elapsed += deltaTime ;
	this->B.update(deltaTime) ;
}

int player::checkCollisions(hitBox enemy){
	//postCondition: ritorna -1 se non ci sono collisioni, altrimenti ritorna il danno del proiettile
	return B.check(enemy);
}

int player::getHealth(){
	return this->hp;
}

#endif //PLAYER_CPP