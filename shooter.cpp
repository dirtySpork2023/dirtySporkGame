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
		/* HEALTH */ 20+5*lvl->number(),
		/* FIRE_RATE */ 1/(1 + 0.5*lvl->number()),
		/* DAMAGE */ 20 + 10*lvl->number(),
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
	muzzle.y = box.a.y-1;
	if( facingRight ) muzzle.x = box.b.x+1;
	else muzzle.x = box.a.x-1;

	/*

	vector speed;
	if( facingRight ) speed.x = 100;
	else speed.x = -100;

	int Dx = p.x-muzzle.x-1;
	int Dy = p.y-muzzle.y-1;
	speed.y = -0.5*BULLET_G*Dx / speed.x  +  Dy*speed.x / Dx;
	// velocità verticale esatta necessaria per colpire il player.

	*/
	// BUG: può accadere che shooter si spara da solo
	// TODO rendere fissa l'altezza a cui arriva il proiettile e
	//		variabile la velocità orizzontale
	// speed.x = 

/*	const double height = 5;
	const double maxS = 300;

	vector speed;
	speed.y = -sqrt(height * BULLET_G * 2);

	double Dx = p.x - muzzle.x;
	double Dy = p.y - muzzle.y;
	double delta = Dx*Dx*speed.y*speed.y + 2*BULLET_G*Dx*Dx*Dy;
	
	mvprintw(2, 3, "Dx = %.5f | Dy = %.5f", Dx, Dy);
	mvprintw(3, 3, "delta = %.5f", delta);

	if(delta>=0){
		speed.x = (-speed.y + sqrt(speed.y*speed.y + 2*BULLET_G*Dy))*Dx/2*-Dy;
		if(speed.x>maxS) speed.x = maxS;
		else if(speed.x<-maxS) speed.x = -maxS;
		mvprintw(4, 3, "Vx = %.5f", speed.x);
		bM->add(muzzle,speed,true,damage,'A');
		speed.x = (-speed.y - sqrt(speed.y*speed.y + 2*BULLET_G*Dy))*Dx/2*-Dy;
		if(speed.x>maxS) speed.x = maxS;
		else if(speed.x<-maxS) speed.x = -maxS;
		mvprintw(5, 3, "Vx = %.5f", speed.x);
		bM->add(muzzle,speed,true,damage,'B');
	}*/
	

/*	speed.x = std::min(	(-speed.y*Dx + sqrt(Dx*Dx*speed.y*speed.y + 2*BULLET_G*Dy*Dx) )/2*Dy,
						(-speed.y*Dx - sqrt(Dx*Dx*speed.y*speed.y + 2*BULLET_G*Dy*Dx) )/2*Dy);*/


	// CONSTANT TIME
	const timeSpan t = 1;
	int Dx = p.x - muzzle.x;
	int Dy = p.y - muzzle.y;

	vector speed;
	speed.x = (Dx)/t;
	speed.y = -0.5*BULLET_G*t + (Dy)/t;
	
	if( -4<Dx && Dx<4 && muzzle.y<p.y ){
		// il player sta sotto shooter quindi aspetto che se ne vada
		// senno shooter si colpisce da solo
		lastShot=fireRate*0.8;
	}else{
		bM->add(muzzle,speed,true,damage,'G');
	}
}
