#include <ncurses.h>
#include "lib.hpp"
#include "kuba.hpp"
#include "bulletManager.hpp"
using namespace std;

kuba::kuba(int x, int y, int h, bulletManager* b, double moveSpeed): entity(x,y,h,b){
	this->xSpeed = moveSpeed;

	//hitbox 3x2
	this->box.a.y = y;
}

void kuba::update(point target, double deltaTime){
	static double elapsedSinceLastMove = 0;

	entity::update(deltaTime);

	if( elapsedSinceLastMove>=xSpeed ){
		if(this->pos.x > target.x+10){
			entity::move('a');
		}else if(this->pos.x < target.x-10){
			entity::move('d');
		}
		elapsedSinceLastMove = 0;
	}

	elapsedSinceLastMove += deltaTime;
}

void kuba::print(double deltaTime){
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

	mvprintw(this->pos.y  , this->pos.x-1, "<O>");
	mvprintw(this->pos.y+1, this->pos.x-1, "/-\\");


	attrset(COLOR_PAIR(1));
}