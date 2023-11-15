#include <ncurses.h>
#include "lib.hpp"
#include "kuba.hpp"
#include "bulletManager.hpp"
#include "level.hpp"
using namespace std;

kuba::kuba(int x, int y, level* lvl, bulletManager* bM, int h, double moveSpeed, int damage):
	entity(x,y,lvl,bM,h){
	this->xSpeed = moveSpeed;
	this->lastMove = 0;

	this->damage = damage;

	//hitbox 3x2
	this->box.a.y = y-1;
}

kuba::kuba(int x, int y, level* lvl, bulletManager* bM):
	kuba(x, y, lvl, bM,
		/* HEALTH */ 40+20*lvl->getDiff(),
		/* SPEED */ 0.1,
		/* DAMAGE */ 20+10*lvl->getDiff()){
}

void kuba::update(player* target, timeSpan deltaTime){
	entity::update(deltaTime);

	// TODO use level check and take a point as input instead of player*
	// should hurt all entities in its path, not only the player

	if( lastMove>=xSpeed ){
		if(this->getPos().x > target->getPos().x+3){
			entity::move('a');
			lastMove = 0;
		}else if(this->getPos().x < target->getPos().x-3){
			entity::move('d');
			lastMove = 0;
		}else if(this->getPos().x == target->getPos().x+3 && this->getPos().y == target->getPos().y){
			target->hurt(damage);
			entity::move('d');
			lastMove = -xSpeed*2;
		}else if(this->getPos().x == target->getPos().x-3 && this->getPos().y == target->getPos().y){
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
	mvprintw(box.b.y, box.a.x, "/\"\\");

	attrset(COLOR_PAIR(1));
}
