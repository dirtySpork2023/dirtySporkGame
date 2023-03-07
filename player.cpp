#include <ncurses.h>
#include <cmath>
#include "lib.hpp"
#include "player.hpp"
#include "bulletManager.hpp"
using namespace std;

player::player(int x, int y, bulletManager* b, double gunFireRate, int gunDamage, float jumpHeight, float armor): entity(x,y,HEALTH,b){
	this->jumpSpeed = -sqrt(jumpHeight * GRAVITY * 2.1);

	this->facingRight = true;

	this->bM = b;
	this->fireRate = gunFireRate; // 0.25 = 1/4 --> 4 colpi al secondo
	this->dmg = gunDamage;

	this->armor = armor; // 0-1 moltiplica i danni subiti
}

//stampa il player
void player::print(timeSpan deltaTime){
	static double elapsedSinceLastDamage = 0; //in secondi
	static int lastHP = HEALTH;

	if( lastHP != this->hp ){
		attrset(COLOR_PAIR(2));
		elapsedSinceLastDamage += deltaTime;
		if(elapsedSinceLastDamage >= 0.10){
			lastHP=this->hp;
			elapsedSinceLastDamage = 0;
		}
	}

	//TODO stampa barra della vita

	if( facingRight ){
		mvprintw(this->pos.y-1, this->pos.x-1, " p ");
		mvprintw(this->pos.y  , this->pos.x-1, ">W=");
		mvprintw(this->pos.y+1, this->pos.x-1, "/\"\\");
	}else{
		mvprintw(this->pos.y-1, this->pos.x-1, " q ");
		mvprintw(this->pos.y  , this->pos.x-1, "=W<");
		mvprintw(this->pos.y+1, this->pos.x-1, "/\"\\");
	}

	attrset(COLOR_PAIR(1));
}

//aggiorna la posizione del player e/o spara
void player::update(char input, timeSpan deltaTime){
	static double elapsedSinceLastShot = 0; //in secondi

	// horizontal movement
	if( input=='a' || input=='A' ){
		facingRight = false;
		entity::move('a');
	}else if( input=='d' || input=='D' ){
		facingRight = true;
		entity::move('d');
	}

	// vertical movement
	entity::applyGravity(deltaTime);

	if( isGrounded && ((int)'A'<=input && input<=(int)'Z' || input=='w')){
		this->ySpeed = this->jumpSpeed; //jump vertical speed
		this->isGrounded = false;
	}

	// applica danno se collide con proiettili
	this->hurt(bM->check(this->box));

	if( (input=='f'||input=='F') && elapsedSinceLastShot > this->fireRate ){
		this->shoot();
		elapsedSinceLastShot = 0;
	}else{
		elapsedSinceLastShot += deltaTime;
	}
}

bool player::hurt(int value){
	return entity::hurt(value * (1-this->armor));
}

void player::shoot(){
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