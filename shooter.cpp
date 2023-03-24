#include <ncurses.h>
#include "entity.hpp"
#include "shooter.hpp"

shooter::shooter(int x, int y, bulletManager* b, int h, double fireRate, int damage): entity(x,y,b,h){
	this->fireRate = fireRate;
	this->lastShot = 0;
	this->dmg = damage;
	this->facingRight = true;
}

void shooter::update(point target, timeSpan deltaTime){
	entity::update(deltaTime);

	if(target.x <= this->box.a.x) facingRight = false;
	else facingRight = true;

	if( this->lastShot > this->fireRate ){
		this->shoot(target);
		this->lastShot = 0;
	}else{
		this->lastShot += deltaTime;
	}
}

void shooter::print(timeSpan deltaTime){
	entity::setPrintColor(PAINT_ENEMY);

	if( facingRight ){
		mvprintw(this->box.a.y,   this->box.a.x, "_//");
		mvprintw(this->box.a.y+1, this->box.a.x, "W/p");
		mvprintw(this->box.b.y,   this->box.a.x, "O=O");
	}else{
		mvprintw(this->box.a.y,   this->box.a.x, "\\\\_");
		mvprintw(this->box.a.y+1, this->box.a.x, "q\\W");
		mvprintw(this->box.b.y,   this->box.a.x, "O=O");
	}

	attrset(COLOR_PAIR(1));
}

void shooter::shoot(point p){
	point muzzle;
	muzzle.x = this->box.a.x+1;
	muzzle.y = this->box.a.y-1;

	vector speed;
	if( facingRight ) speed.x = 150;
	else speed.x = -150;

	//int Dx = (p.x-muzzle.x-1);
	//int Dy = (p.y-muzzle.y-1);
	speed.y = -112*(p.x-muzzle.x-1) / speed.x  +  (p.y-muzzle.y-1)*speed.x / (p.x-muzzle.x-1);
	// velocità verticale esatta necessaria per colpire il player. (imprecisa su distanze più lunghe del terminale)
	// yeah mista white
	// yeah SCIENCE
	this->bM->add(muzzle,speed,true,this->dmg,'G');
}