#include <ncurses.h>
#include "lib.hpp"
#include "kuba.hpp"
#include "bulletManager.hpp"
using namespace std;

kuba::kuba(int x, int y, level* lM, bulletManager* bM, int h, double moveSpeed, int damage): entity(x,y,lM,bM,h){
	this->xSpeed = moveSpeed;
	this->lastMove = 0;

	this->damage = damage;

	//hitbox 3x2
	this->box.a.y = y-1;
}

kuba::kuba(int x, int y, level* lM, bulletManager* bM):
	kuba(x, y, lM, bM, /*HEALTH*/40+20*lM->number(), /*SPEED*/0.1, /*DAMAGE*/20+10*lM->number() ){

}

void kuba::update(player* target, timeSpan deltaTime){
	entity::update(deltaTime);

	// WIP
	if( lastMove>=xSpeed ){
		if(box.b.x > target->getPos().x+3){
			entity::move('a');
			lastMove = 0;
		}else if(box.b.x < target->getPos().x-3){
			entity::move('d');
			lastMove = 0;
		}else if(box.b.x == target->getPos().x+3 && box.b.y == target->getPos().y){
			target->hurt(damage);
			entity::move('d');
			lastMove = -xSpeed*2;
		}else if(box.b.x == target->getPos().x-3 && box.b.y == target->getPos().y){
			target->hurt(damage);
			entity::move('a');
			lastMove = -xSpeed*2;
		}
	}

	lastMove += deltaTime;
}

void kuba::print(timeSpan deltaTime){
	entity::setPrintColor(PAINT_ENEMY);

	mvprintw(box.a.y, box.a.x, "<O>");
	mvprintw(box.b.y, box.a.x, "/-\\");

	attrset(COLOR_PAIR(1));
}