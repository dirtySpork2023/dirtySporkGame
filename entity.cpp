#include <ncurses.h>

#include "lib.hpp"
#include "level.hpp"
#include "entity.hpp"
using namespace std;

entity::entity(int x, int y, level* lM, bulletManager* bM, int hp){
	this->yMod = 0;
	this->ySpeed = 0;
	this->isGrounded = false;

	this->health = hp;
	this->lastDamage = 0;

	this->bM = bM;
	this->lM = lM;

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
	setGrounded( lM->check(box, 's').type!='n' );
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
	if( lM->check(box, input).type == 'n'){
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
		}else if( input=='w' ){
			box.a.y -= 1;
			box.b.y -= 1;
			setGrounded(false);
			// cleanup
			for(int x=box.a.x ; x<=box.b.x ; x++){
				mvprintw(box.b.y+1, x, " ");
			}
		}else if( input=='s' ){
			box.a.y += 1;
			box.b.y += 1;
			//if( lM->check(box, input).type != 'n') setGrounded(true); //needs testing. setgrounded is in update()
			// cleanup
			for(int x=box.a.x ; x<=box.b.x ; x++){
				mvprintw(box.a.y-1, x, " ");
			}
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

// ritorna la hitBox
hitBox entity::getHitBox(){
	return this->box;
}

// ritorna i punti vita
int entity::getHealth(){
	return this->health;
}

// danneggia entity e ritorna se è morto
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

// quando entity è a terra (o sopra un nemico), bisogna invocare questo metodo
void entity::setGrounded(bool grounded){
	if(grounded && ySpeed>=0 ){
		isGrounded = true;
	}else{
		isGrounded = false;
	}
}

// distruttore: cancella l'entity solo graficamente. ipotizzando che hitbox e grafica coincidano
entity::~entity(){
	for(int x=box.a.x ; x<=box.b.x ; x++){
		for(int y=box.a.y ; y<=box.b.y ; y++){
			mvprintw(y,x," ");
		}
	}
}