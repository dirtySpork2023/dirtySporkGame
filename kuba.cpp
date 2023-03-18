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

	// WIP
	if( lastMove>=xSpeed ){
		if(this->box.b.x > target->getPos().x+3){
			entity::move('a');
			lastMove = 0;
		}else if(this->box.b.x < target->getPos().x-3){
			entity::move('d');
			lastMove = 0;
		}else if(this->box.b.x == target->getPos().x+3 && this->box.b.y == target->getPos().y){
			target->hurt(this->damage);
			entity::move('d');
			lastMove = -xSpeed*2;
		}else if(this->box.b.x == target->getPos().x-3 && this->box.b.y == target->getPos().y){
			target->hurt(this->damage);
			entity::move('a');
			lastMove = -xSpeed*2;
		}
	}

	lastMove += deltaTime;
}

void kuba::print(timeSpan deltaTime){
	entity::setPrintColor();

	mvprintw(this->box.a.y, this->box.a.x, "<O>");
	mvprintw(this->box.b.y, this->box.a.x, "/-\\");
}