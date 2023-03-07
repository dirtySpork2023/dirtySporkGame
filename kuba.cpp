#include <ncurses.h>
#include "lib.hpp"
#include "kuba.hpp"
#include "bulletManager.hpp"
using namespace std;

kuba::kuba(int x, int y, int h, bulletManager* b, double moveSpeed, int damage): entity(x,y,h,b){
	this->xSpeed = moveSpeed;

	this->damage = damage;

	//hitbox 3x2
	this->box.a.y = y;
}

void kuba::update(player* target, timeSpan deltaTime){
	static timeSpan lastMove = 0;

	entity::update(deltaTime);

	if( lastMove>=xSpeed ){
		if(this->pos.x > target->getPos().x+3){
			entity::move('a');
			lastMove = 0;
		}else if(this->pos.x < target->getPos().x-3){
			entity::move('d');
			lastMove = 0;
		}else if(this->pos.x == target->getPos().x+3 && this->pos.y == target->getPos().y){
			target->hurt(this->damage);
			entity::move('d');
			lastMove = -xSpeed*2;
		}else if(this->pos.x == target->getPos().x-3 && this->pos.y == target->getPos().y){
			target->hurt(this->damage);
			entity::move('a');
			lastMove = -xSpeed*2;
		}
	}

	lastMove += deltaTime;
}

void kuba::print(timeSpan deltaTime){
	static timeSpan lastDamage = 0; //in secondi
	static int lastHP = HEALTH;

	if( lastHP != this->hp ){
		attrset(COLOR_PAIR(2));
		lastDamage += deltaTime;
		if(lastDamage >= 0.10){
			lastHP=this->hp;
			lastDamage = 0;
		}
	}

	//TODO stampa barra della vita

	mvprintw(this->pos.y  , this->pos.x-1, "<O>");
	mvprintw(this->pos.y+1, this->pos.x-1, "/-\\");


	attrset(COLOR_PAIR(1));
}