#include <ncurses.h>
#include <cmath>
#include "lib.hpp"
#include "player.hpp"
#include "bulletManager.hpp"
using namespace std;

#define GRAVITY 120

player::player(int x, int y, bulletManager* b, double gunFireRate, int gunDamage, int health, float jumpHeight){
	this->hp = health;
	// la posizione indica il torso del player
	this->pos.x = x;
	this->pos.y = y;
	this->yMod = 0;
	this->ySpeed = 0;
	this->isGrounded = false;
	this->jumpSpeed = -sqrt((jumpHeight+1) * GRAVITY * 2);

	// hitbox 3x3
	this->box.a.x = x-1;
	this->box.a.y = y-1;
	this->box.b.x = x+1;
	this->box.b.y = y+1;
	this->facingRight = true;

	this->bM = b;
	this->fireRate = gunFireRate; // 0.25 = 1/4 --> 4 colpi al secondo
	this->dmg = gunDamage;
	this->elapsedSinceLastShot = 0;
}

//stampa il player
void player::print(){
	//player
	for(int y=-1 ; y<=1 ; y++){
		for(int x=-1 ; x<=1 ; x++){
			if( facingRight ){
				mvprintw(y+this->pos.y, x+this->pos.x, "%c", texture[y+1][x+1]);
			}else{
				mvprintw(y+this->pos.y, x+this->pos.x, "%c", reverse[y+1][x+1]);
			}
		}
	}
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
	if(isGrounded ){
		this->pos.y = 30;
		this->ySpeed = 0;
		this->yMod = 0;
		if( (int)'A'<=input && input<=(int)'Z' || input=='w'){
			this->ySpeed = this->jumpSpeed; //jump vertical speed
			this->isGrounded = false;
		}
	}else{
		this->ySpeed += GRAVITY * deltaTime;
		this->yMod += this->ySpeed * deltaTime;
		if(this->yMod > 1){
			this->yMod -= 1;
			this->pos.y += 1;
			this->box.a.y += 1;
			this->box.b.y += 1;
			// cleanup
			for(int x=this->pos.x-1 ; x<=this->pos.x+1 ; x++){
				mvprintw(this->pos.y-2, x, " ");
			}
		}else if(this->yMod < -1){
			this->yMod += 1;
			this->pos.y -= 1;
			this->box.a.y -= 1;
			this->box.b.y -= 1;
			// cleanup
			for(int x=this->pos.x-1 ; x<=this->pos.x+1 ; x++){
				mvprintw(this->pos.y+2, x, " ");
			}
		}
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
		speed.x = 500;
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

// danneggia il player e ritorna true se è morto
bool player::hurt(int value){
	this->hp -= value;
	if(this->hp <= 0){
		this->hp = 0;
		return true;
	}else{
		return false;
	}
}

/* WIP non utilizzato
void player::kill(){
	this->hp = 0;

	for(int y=-1 ; y<=1 ; y++){
		for(int x=-1 ; x<=1 ; x++){
			mvprintw(y+this->pos.y, x+this->pos.x, " ");
		}
	}
}*/

// ritorna i punti vita del player
int player::getHealth(){
	return this->hp;
}

// ritorna la posizione del player
point player::getPos(){
	return this->pos;
}

// ritorna la hitBox del player
hitBox player::getHitBox(){
	return this->box;
}

// quando il player è a terra (o sopra un nemico), bisogna invocare questo metodo.
void player::setGrounded(bool playerGrounded){
	if(playerGrounded && ySpeed>=0 ){
		this->isGrounded = true;
	}else{
		this->isGrounded = false;
	}
}