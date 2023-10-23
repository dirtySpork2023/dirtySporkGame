#include <ncurses.h>
#include "entity.hpp"
#include "shooter.hpp"

shooter::shooter(int x, int y, level* lM, bulletManager* bM, int h, double fireRate, int damage): entity(x,y,lM,bM,h){
	this->fireRate = fireRate;
	this->lastShot = 0;
	this->damage = damage;
	this->facingRight = true;
}

shooter::shooter(int x, int y, level* lM, bulletManager* bM):
	shooter(x, y, lM, bM, /*HEALTH*/20+5*lM->number(), /*FIRE_RATE*/1/(0.2 + 0.5*lM->number()), /*DAMAGE*/20 + 10*lM->number()){
}

void shooter::update(point target, timeSpan deltaTime){
	entity::update(deltaTime);

	if(target.x <= box.a.x) facingRight = false;
	else facingRight = true;

	if( lastShot > fireRate ){
		shoot(target);
		lastShot = 0;
	}else{
		lastShot += deltaTime;
	}
}

void shooter::print(timeSpan deltaTime){
	entity::setPrintColor(PAINT_ENEMY);

	if( facingRight ){
		mvprintw(box.a.y,   box.a.x, "_//");
		mvprintw(box.a.y+1, box.a.x, "W/p");
		mvprintw(box.b.y,   box.a.x, "O=O");
	}else{
		mvprintw(box.a.y,   box.a.x, "\\\\_");
		mvprintw(box.a.y+1, box.a.x, "q\\W");
		mvprintw(box.b.y,   box.a.x, "O=O");
	}

	attrset(COLOR_PAIR(1));
}

void shooter::shoot(point p){
	point muzzle;
	muzzle.x = box.a.x+1;
	muzzle.y = box.a.y-1;

	vector speed;
	if( facingRight ) speed.x = 100;
	else speed.x = -100;

	// int Dx = (p.x-muzzle.x-1);
	// int Dy = (p.y-muzzle.y-1);
	speed.y = -0.75*BULLET_G*(p.x-muzzle.x-1) / speed.x  +  (p.y-muzzle.y-1)*speed.x / (p.x-muzzle.x-1);
	// velocità verticale esatta necessaria per colpire il player.
	bM->add(muzzle,speed,true,damage,'G');
}