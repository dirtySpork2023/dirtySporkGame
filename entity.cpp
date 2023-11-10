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
	this->box.a.x = x-1;
	this->box.a.y = y-2;
	this->box.b.x = x+1;
	this->box.b.y = y;
}

void entity::update(timeSpan deltaTime){
	hurt(bM->check(box));
	lastDamage += deltaTime;
	applyGravity(deltaTime);
}

// muove entity in base alla forza di gravità e il tempo passato
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

// muove entity di una posizione verso una direzione WASD
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
		}else if( input=='s' ){
			box.a.y += 1;
			box.b.y += 1;
			// cleanup
			for(int x=box.a.x ; x<=box.b.x ; x++){
				mvprintw(box.a.y-1, x, " ");
			}
		}
		// controllo se il player è a terra nella nuova posizione
		if( lvl->check(box, 's').type!='n' && ySpeed>=0 ){
			isGrounded = true;
		}else{
			isGrounded = false;
		}
	}
	if( input=='w' ){
		box.a.y -= 1;
		box.b.y -= 1;
		isGrounded = false;
		// cleanup
		for(int x=box.a.x ; x<=box.b.x ; x++){
			mvprintw(box.b.y+1, x, " ");
		}
	}
}

// applica il colore con cui stampare
void entity::setPrintColor(int paint){
	if(lastDamage <= DAMAGE_TIMESPAN){
		attrset(COLOR_PAIR( PAINT_DAMAGE ));
	}else{
		attrset(COLOR_PAIR( paint ));
		attron(A_BOLD);
	}
}

// ritorna la posizione più centrale alla base dell'entity
point entity::getPos(){
	point pos = box.b;
	pos.x = (box.a.x + box.b.x )/2;
	return pos;
}

// ritorna la hitBox
hitBox entity::getHitBox(){
	return this->box;
}

// ritorna i punti vita
int entity::getHealth(){
	return this->health;
}

// danneggia entity e ritorna 'se è morto'
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

entity::~entity(){
	// cleanup
	for(int x=box.a.x ; x<=box.b.x ; x++){
		for(int y=box.a.y ; y<=box.b.y ; y++){
			mvprintw(y, x, " ");
		}
	}
	
	// esplosione
	point pos = this->getPos();

	for(int i=0; i<5; i++){
		bM->add(pos, randVector(), true, 0, ':');
	}
}
