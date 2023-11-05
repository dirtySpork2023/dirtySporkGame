#include <ncurses.h>
#include "entity.hpp"
#include "shooter.hpp"
#include "level.hpp"

shooter::shooter(int x, int y, level* lvl, bulletManager* bM, int h, double fireRate, int damage, char bullet):
	entity(x,y,lvl,bM,h){
	this->facingRight = true;
	this->fireRate = fireRate;
	this->damage = damage;
	this->texture = bullet;
	this->lastShot = 0;
}

shooter::shooter(int x, int y, level* lvl, bulletManager* bM):
	shooter(x, y, lvl, bM,
		/*HEALTH*/20+5*lvl->number(),
		/*FIRE_RATE*/1/(1 + 0.5*lvl->number()),
		/*DAMAGE*/20 + 10*lvl->number(),
		'G'){
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

	int Dx = p.x-muzzle.x-1;
	int Dy = p.y-muzzle.y-1;
	speed.y = -0.75*BULLET_G*Dx / speed.x  +  Dy*speed.x / Dx;
	// velocità verticale esatta necessaria per colpire il player.

	// TODO rendere fissa l'altezza a cui arriva il proiettile e
	//		variabile la velocità orizzontale
	// speed.x = 
	bM->add(muzzle,speed,true,damage,'G');
}
