#include "shooter.hpp"
#include "level.hpp"

// costruttore
shooter::shooter(int x, int y, level* lvl, int h, double fireRate, int damage, char bullet):
	entity(x,y,lvl,h){
	this->facingRight = true;
	this->fireRate = fireRate;
	this->damage = damage;
	this->texture = bullet;
	this->lastShot = fireRate - random(0,100)/(double)100;
}

// costruttore secondario
shooter::shooter(int x, int y, level* lvl):
	shooter(x, y, lvl,
		/* HEALTH */ 15+2*lvl->getDiff(),
		/* FIRE_RATE */ 1/(0.5 + 0.1*lvl->getDiff()),
		/* DAMAGE */ 20 + 5*lvl->getDiff(),
		/* TEXTURE */ 'G'){
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
		mvprintw(box.a.y,   box.a.x, " //");
		mvprintw(box.a.y+1, box.a.x, "//b");
		mvprintw(box.b.y,   box.a.x, "O=O");
	}else{
		mvprintw(box.a.y,   box.a.x, "\\\\ ");
		mvprintw(box.a.y+1, box.a.x, "d\\\\");
		mvprintw(box.b.y,   box.a.x, "O=O");
	}

	attrset(COLOR_PAIR(PAINT_DEFAULT));
}

void shooter::shoot(point p){
	point muzzle;
	muzzle.y = box.a.y-1;
	if( facingRight ) muzzle.x = box.b.x+1;
	else muzzle.x = box.a.x-1;

	// tempo di volo costante
	const timeSpan t = 1.2;
	int Dx = p.x - muzzle.x;
	int Dy = p.y - muzzle.y;

	vector speed;
	speed.x = (Dx)/t;
	speed.y = -0.5*BULLET_G*t + (Dy)/t;

	/* velocità orizzontale costante
	if( facingRight ) speed.x = 100;
	else speed.x = -100;
	speed.y = -0.5*BULLET_G*Dx / speed.x  +  Dy*speed.x / Dx;
	*/
	
	if( box.a.x-2<p.x && p.x<2+box.b.x ){
		//evito traiettoie che possono colpire lo shooter stesso
		lastShot=fireRate;
	}else{
		lvl->getBM()->add(muzzle,speed,true,damage,'G');
	}
}
