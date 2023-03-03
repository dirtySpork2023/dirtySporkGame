#include <ncurses.h>
#include "lib.hpp"
#include "entity.hpp"
using namespace std;

entity::entity(int x, int y, int health, bulletManager* b){
	this->pos.x = x;
	this->pos.y = y;
	this->yMod = 0;
	this->ySpeed = 0;
	this->isGrounded = false;

	this->hp = health;

	this->bM = b;

	//default hitbox. da sovrascrivere se necessario
	this->box.a.x = x-1;
	this->box.a.y = y-1;
	this->box.b.x = x+1;
	this->box.b.y = y+1;
}

void entity::update(double deltaTime){
	// applica danno se collide con proiettili
	this->hurt(bM->check(this->box));

	this->applyGravity(deltaTime);
}

void entity::applyGravity(double deltaTime){
	if( this->isGrounded ){
		this->pos.y = 30;
		this->ySpeed = 0;
		this->yMod = 0;
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
}

// ritorna la posizione
point entity::getPos(){
	return this->pos;
}

// ritorna la hitBox
hitBox entity::getHitBox(){
	return this->box;
}


// ritorna i punti vita
int entity::getHealth(){
	return this->hp;
}

// danneggia entity e ritorna true se è morto
bool entity::hurt(int value){
	this->hp -= value;
	if(this->hp <= 0){
		this->hp = 0;
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