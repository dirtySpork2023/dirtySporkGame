#include <ncurses.h>
#include "lib.hpp"
#include "kuba.hpp"
#include "bulletManager.hpp"
using namespace std;

kuba::kuba(int x, int y, bulletManager* b, int h, double moveSpeed, int damage): entity(x,y,b,h){
	this->xSpeed = moveSpeed;
	this->lastMove = 0;

	this->damage = damage;

	//hitbox 3x2
	this->box.a.y = y-1;
}

kuba::kuba(int x, int y, bulletManager* b, int level): entity(x,y,b,0){
	this->xSpeed = 0.1;
	this->lastMove = 0;

	this->damage = 10 * level;
	this->health = 20 * level;

	//hitbox 3x2
	this->box.a.y = y-1;
}

void kuba::update(player* target, timeSpan deltaTime){
	entity::update(deltaTime);

	// WIP
	if( lastMove>=xSpeed ){
		if(this->box.b.x > target->getPos().x+3){
			entity::move('a');
			this->lastMove = 0;
		}else if(this->box.b.x < target->getPos().x-3){
			entity::move('d');
			this->lastMove = 0;
		}else if(this->box.b.x == target->getPos().x+3 && this->box.b.y == target->getPos().y){
			target->hurt(this->damage);
			entity::move('d');
			this->lastMove = -xSpeed*2;
		}else if(this->box.b.x == target->getPos().x-3 && this->box.b.y == target->getPos().y){
			target->hurt(this->damage);
			entity::move('a');
			this->lastMove = -xSpeed*2;
		}
	}

	this->lastMove += deltaTime;
}

void kuba::print(timeSpan deltaTime){
	entity::setPrintColor(PAINT_ENEMY);

	mvprintw(this->box.a.y, this->box.a.x, "<O>");
	mvprintw(this->box.b.y, this->box.a.x, "/-\\");

	attrset(COLOR_PAIR(1));
}