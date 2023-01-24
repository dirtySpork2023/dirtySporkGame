#ifndef PLAYER_CPP
#define PLAYER_CPP

#include <ncurses.h>
#include "lib.hpp"
#include "bullet.hpp"
#include "player.hpp"

player::player(int y, int x, bulletManager* b, double gunFireRate, int gunDamage, int health){
	this->hp = health;
	// la posizione indica il torso del player
	this->pos.x = x;
	this->pos.y = y;
	this->yMod = 0;
	this->ySpeed = 0;

	// hitbox 3x3
	this->box.a.x = -1;
	this->box.a.y = -1;
	this->box.b.x = +1;
	this->box.b.y = +1;
	this->facing = true; // destra

	this->bM = b;
	this->fireRate = gunFireRate; // 0.25 = 4 colpi al secondo
	this->damage = gunDamage;
}

void player::print(){
	//player
	for(int y=-1 ; y<=1 ; y++){
		for(int x=-1 ; x<=1 ; x++){
			if( facing ){
				mvprintw(y+this->pos.y, x+this->pos.x, "%c", texture[y+1][x+1]);
			}else{
				mvprintw(y+this->pos.y, x+this->pos.x, "%c", reverse[y+1][x+1]);
			}
		}
	}
}

void player::update(char input, long int deltaTime){
	// horizontal movement
	if( input=='a' || input=='A' ){
		facing = false;
		this->pos.x -= 1;
		//cleanup //da spostare nel metodo print ?
		for(int y=this->pos.y-1 ; y<=this->pos.y+1 ; y++){
			mvprintw(y, this->pos.x+2, " ");
		}
	}else if( input=='d' || input=='D' ){
		facing = true;
		this->pos.x += 1;
		// cleanup //da spostare nel metodo print ?
		for(int y=-1 ; y<=1 ; y++){
			mvprintw(y+this->pos.y, this->pos.x-2, " ");
		}
	}



	// vertical movement
	if( this->pos.y==30 ) isGrounded=true; // temporaneo
	else isGrounded=false;
	if(isGrounded){
		this->pos.y = 30;
		this->ySpeed = 0;
		this->yMod = 0;
		if( (int)'A'<input && input<(int)'Z' || input=='w'){
			this->ySpeed = -0.0035 ; //jump vertical speed
			//this->isGrounded = false;
			this->pos.y -= 1;
			// cleanup
			for(int x=this->pos.x-1 ; x<=this->pos.x+1 ; x++){
				mvprintw(this->pos.y+2, x, " ");
			}
		}
	}else{
		this->ySpeed += 0.025 / deltaTime; //gravity
		this->yMod += this->ySpeed;
		if(this->yMod > 1){
			this->yMod -= 1;
			this->pos.y += 1;
			// cleanup
			for(int x=this->pos.x-1 ; x<=this->pos.x+1 ; x++){
				mvprintw(this->pos.y-2, x, " ");
			}
		}else if(this->yMod < -1){
			this->yMod += 1;
			this->pos.y -= 1;
			// cleanup
			for(int x=this->pos.x-1 ; x<=this->pos.x+1 ; x++){
				mvprintw(this->pos.y+2, x, " ");
			}
		}
	}


	if( input=='f' || input=='F'){
		this->shoot(deltaTime);
	}

	this->elapsedSinceLastShot += deltaTime/(double)1000000000;
}

void player::shoot(long int deltaTime){
	//static long elapsed = 0;
	//double secondsElapsed = elapsed/(double)1000000000;
	if( this->elapsedSinceLastShot > this->fireRate ){
		this->elapsedSinceLastShot = 0;
		int speed = 300;
		if( facing==false ) speed *= -1;
		this->bM->add(this->pos, speed, this->damage, 'o');
	}
	//elapsed += deltaTime;
}

int player::getHealth(){
	return this->hp;
}

void player::setGrounded(bool playerGrounded){
	this->isGrounded = playerGrounded;
}

#endif //PLAYER_CPP