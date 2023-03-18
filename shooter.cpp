#include <ncurses.h>
#include "entity.hpp"
#include "shooter.hpp"

shooter::shooter(int x, int y, int h, bulletManager* b, double fireRate, int damage): entity(x,y,h,b){
	this->fireRate = fireRate;
	this->dmg = damage;
}

void shooter::print(timeSpan deltaTime){
	entity::setPrintColor();

	mvprintw(this->box.a.y,   this->box.a.x, "\\\\ ");
	mvprintw(this->box.a.y+1, this->box.a.x, "qWW");
	mvprintw(this->box.b.y,   this->box.a.x, "O=O");
}

void shooter::update(player* target, timeSpan deltaTime){

}

void shooter::shoot(){
	vector speed;
	speed.x = -200;
	speed.y = 0;

	point muzzle;
	muzzle.x = this->box.a.x-1;
	muzzle.y = this->box.a.y+1;

	this->bM->add(muzzle, speed, true, this->dmg, 'G');
}