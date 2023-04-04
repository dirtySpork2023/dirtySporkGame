#include <ncurses.h>
#include <cmath>
#include "lib.hpp"
#include "player.hpp"
#include "bulletManager.hpp"
using namespace std;

#define HEALTH_LENGTH 20

player::player(int x, int y, bulletManager* b, double gunFireRate, int gunDamage, float jumpHeight, float armor): shooter(x,y,b,MAX_HEALTH,gunFireRate,gunDamage){
	this->jumpSpeed = -sqrt(jumpHeight * GRAVITY * 2.1);
	this->armor = armor; // 0-1 moltiplica i danni subiti
}

//aggiorna la posizione del player e/o spara
void player::update(char input, timeSpan deltaTime){

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

	this->hurt(bM->check(this->box));
	this->lastDamage += deltaTime;

	if( (input=='f'||input=='F') && this->lastShot > this->fireRate ){
		this->shoot();
		this->lastShot = 0;
	}else{
		this->lastShot += deltaTime;
	}
}

//stampa il player
void player::print(timeSpan deltaTime){
	entity::setPrintColor(PAINT_PLAYER);

	// body
	if( facingRight ){
		mvprintw(this->box.a.y,   this->box.a.x, " p ");
		mvprintw(this->box.a.y+1, this->box.a.x, ">W=");
		mvprintw(this->box.b.y,   this->box.a.x, "/\"\\");
	}else{
		mvprintw(this->box.a.y,   this->box.a.x, " q ");
		mvprintw(this->box.a.y+1, this->box.a.x, "=W<");
		mvprintw(this->box.b.y,   this->box.a.x, "/\"\\");
	}

	// health bar
	attrset(COLOR_PAIR(1));
	mvprintw(1, 1, "health: %3d |", this->health);
	for(int i=0 ; i<HEALTH_LENGTH ; i++){
		if(this->health - i*MAX_HEALTH/HEALTH_LENGTH > 0)
			printw("#");
		else
			printw(".");
	}
	printw("|");
	mvprintw(2, 1, "armor: %3.0f%%", this->armor*100);
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
	muzzle.x = this->box.a.x+1;
	muzzle.y = this->box.a.y+1;
	if( facingRight ) muzzle.x += 2;
	else muzzle.x -= 2;

	this->bM->add(muzzle, speed, false, this->dmg, 'o');
}