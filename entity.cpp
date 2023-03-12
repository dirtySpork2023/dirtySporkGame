#include <ncurses.h>
#include "lib.hpp"
#include "entity.hpp"
using namespace std;

entity::entity(int x, int y, int hp, bulletManager* b){
	//this->pos.x = x;
	//this->pos.y = y;
	this->yMod = 0;
	this->ySpeed = 0;
	this->isGrounded = false;

	this->health = hp;

	this->bM = b;

	//default hitbox. da sovrascrivere se necessario
	this->box.a.x = x-1;
	this->box.a.y = y-1;
	this->box.b.x = x+1;
	this->box.b.y = y+1;
}

void entity::update(timeSpan deltaTime){
	// applica danno se collide con proiettili
	this->hurt(bM->check(this->box));

	this->applyGravity(deltaTime);
}

void entity::applyGravity(timeSpan deltaTime){
	if( this->isGrounded ){
		//this->pos.y = 30;
		this->ySpeed = 0;
		this->yMod = 0;
	}else{
		this->ySpeed += GRAVITY * deltaTime;
		this->yMod += this->ySpeed * deltaTime;
		if(this->yMod > 1){
			this->yMod -= 1;
			this->move('s');
		}else if(this->yMod < -1){
			this->yMod += 1;
			this->move('w');
		}
	}
}

void entity::move(char input){
	if( input=='a' ){
		//this->pos.x -= 1;
		this->box.a.x -= 1;
		this->box.b.x -= 1;
		// cleanup
		for(int y=this->box.a.y ; y<=this->box.b.y ; y++){
			mvprintw(y, this->box.b.x+1, " ");
		}
	}else if( input=='d' ){
		//this->pos.x += 1;
		this->box.a.x += 1;
		this->box.b.x += 1;
		// cleanup
		for(int y=this->box.a.y ; y<=this->box.b.y ; y++){
			mvprintw(y, this->box.a.x-1, " ");
		}
	}else if( input=='w' ){
		//this->pos.y -= 1;
		this->box.a.y -= 1;
		this->box.b.y -= 1;
		// cleanup
		for(int x=this->box.a.x ; x<=this->box.b.x ; x++){
			mvprintw(this->box.b.y+1, x, " ");
		}
	}else if( input=='s' ){
		//this->pos.y += 1;
		this->box.a.y += 1;
		this->box.b.y += 1;
		// cleanup
		for(int x=this->box.a.x ; x<=this->box.b.x ; x++){
			mvprintw(this->box.a.y-1, x, " ");
		}
	}
}

// deprecated
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

// danneggia entity e ritorna true se è morto
bool entity::hurt(int value){
	this->health -= value;
	if(this->health <= 0){
		this->health = 0;
		return true;
	}else{
		return false;
	}
}

// quando entity è a terra (o sopra un nemico), bisogna invocare questo metodo
void entity::setGrounded(bool grounded){
	if(grounded && ySpeed>=0 ){
		this->isGrounded = true;
	}else{
		this->isGrounded = false;
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