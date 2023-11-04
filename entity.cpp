#include <ncurses.h>

#include "lib.hpp"
#include "level.hpp"
#include "entity.hpp"
using namespace std;

entity::entity(int x, int y, level* lvl, bulletManager* bM, int hp){
	this->yMod = 0;
	this->ySpeed = 0;
	this->isGrounded = false;

	this->health = hp;
	this->lastDamage = 0;

	this->bM = bM;
	this->lvl = lvl;

	//default hitbox. da sovrascrivere se necessario
	this->box.a.x = x-2;
	this->box.a.y = y-2;
	this->box.b.x = x;
	this->box.b.y = y;
}

void entity::update(timeSpan deltaTime){
	hurt(bM->check(box));
	lastDamage += deltaTime;
	applyGravity(deltaTime);
}

void entity::applyGravity(timeSpan deltaTime){
	if( isGrounded ){
		ySpeed = 0;
		yMod = 0;
	}else{
		ySpeed += ENTITY_G * deltaTime;
		yMod += ySpeed * deltaTime;
		if(yMod > 1){
			yMod -= 1;
			move('s');
		}else if(yMod < -1){
			yMod += 1;
			move('w');
		}
	}
}

void entity::move(char input){
	infoCrash i = lvl->check(box, input);
	if( i.type=='n' ){
		if( input=='a' ){
			box.a.x -= 1;
			box.b.x -= 1;
			// cleanup
			for(int y=box.a.y ; y<=box.b.y ; y++){
				mvprintw(y, box.b.x+1, " ");
			}
		}else if( input=='d' ){
			box.a.x += 1;
			box.b.x += 1;
			// cleanup
			for(int y=box.a.y ; y<=box.b.y ; y++){
				mvprintw(y, box.a.x-1, " ");
			}
		}else if( input=='s' /*&& i.type=='n'*/){
			box.a.y += 1;
			box.b.y += 1;
			// cleanup
			for(int x=box.a.x ; x<=box.b.x ; x++){
				mvprintw(box.a.y-1, x, " ");
			}
		}
		setGrounded(lvl->check(box, 's').type != 'n');
	}
	if( input=='w' ){
		box.a.y -= 1;
		box.b.y -= 1;
		setGrounded(false);
		// cleanup
		for(int x=box.a.x ; x<=box.b.x ; x++){
			mvprintw(box.b.y+1, x, " ");
		}
	}
}

void entity::setPrintColor(int paint){
	if(lastDamage <= DAMAGE_TIMESPAN){
		attrset(COLOR_PAIR( PAINT_DAMAGE ));
	}else{
		attrset(COLOR_PAIR( paint ));
	}
}

point entity::getPos(){
	return this->box.b;
}

hitBox entity::getHitBox(){
	return this->box;
}

int entity::getHealth(){
	return this->health;
}

bool entity::hurt(int value){
	if( value!=0 ){
		lastDamage = 0;
		health -= value;
	}

	if(health <= 0){
		health = 0;
		return true;
	}else{
		return false;
	}
}

void entity::setGrounded(bool grounded){
	if(grounded && ySpeed>=0 ){
		isGrounded = true;
	}else{
		isGrounded = false;
	}
}

entity::~entity(){
	for(int x=box.a.x ; x<=box.b.x ; x++){
		for(int y=box.a.y ; y<=box.b.y ; y++){
			mvprintw(y,x," ");
		}
	}
}
