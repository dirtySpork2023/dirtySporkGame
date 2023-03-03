#include <ncurses.h>
#include <cmath>
#include "lib.hpp"
#include "player.hpp"
#include "bulletManager.hpp"
using namespace std;

player::player(int x, int y, bulletManager* b, double gunFireRate, int gunDamage, int h, float jumpHeight): entity(x,y,h,b){
	this->jumpSpeed = -sqrt(jumpHeight * GRAVITY * 2.1);

	this->facingRight = true;

	this->bM = b;
	this->fireRate = gunFireRate; // 0.25 = 1/4 --> 4 colpi al secondo
	this->dmg = gunDamage;
	this->elapsedSinceLastShot = 0;

/*	this->elapsedSinceLastDamage = 0;
	if(has_colors()){
		init_pair(2, COLOR_RED, COLOR_BLACK);
	}*/
}

//stampa il player
void player::print(){
	//player
	//if(this->recentDamage) attrset(COLOR_PAIR(2));
	//else attrset(COLOR_PAIR(1));
	for(int y=-1 ; y<=1 ; y++){
		for(int x=-1 ; x<=1 ; x++){
			if( facingRight ){
				mvprintw(y+this->pos.y, x+this->pos.x, "%c", texture[y+1][x+1]);
			}else{
				mvprintw(y+this->pos.y, x+this->pos.x, "%c", reverse[y+1][x+1]);
			}
		}
	}
	//attrset(COLOR_PAIR(1));
}

//aggiorna la posizione del player e/o spara
void player::update(char input, double deltaTime){
	// horizontal movement
	if( input=='a' || input=='A' ){
		facingRight = false;
		this->pos.x -= 1;
		this->box.a.x -= 1;
		this->box.b.x -= 1;
		//cleanup
		for(int y=this->pos.y-1 ; y<=this->pos.y+1 ; y++){
			mvprintw(y, this->pos.x+2, " ");
		}
	}else if( input=='d' || input=='D' ){
		facingRight = true;
		this->pos.x += 1;
		this->box.a.x += 1;
		this->box.b.x += 1;
		// cleanup
		for(int y=-1 ; y<=1 ; y++){
			mvprintw(y+this->pos.y, this->pos.x-2, " ");
		}
	}


	// vertical movement
	entity::update(deltaTime);

	if( isGrounded && ((int)'A'<=input && input<=(int)'Z' || input=='w')){
		this->ySpeed = this->jumpSpeed; //jump vertical speed
		this->isGrounded = false;
	}

	if( input=='f' || input=='F'){
		this->shoot();
	}else{
		this->elapsedSinceLastShot += deltaTime;
	}
}

void player::shoot(){
	if( this->elapsedSinceLastShot > this->fireRate ){
		this->elapsedSinceLastShot = 0;

		vector speed;
		speed.x = 200;
		speed.y = 0;
		if( !facingRight ) speed.x *= -1;

		point muzzle;
		muzzle.x = this->pos.x;
		muzzle.y = this->pos.y;
		if( facingRight ) muzzle.x += 2;
		else muzzle.x -= 2;

		this->bM->add(muzzle, speed, false, this->dmg, 'o');
	}
}