#include "yuck.hpp"
#include "level.hpp"

yuck::yuck(int x, int y, level* lvl, int h, double fr, int dm):
	shooter(x,y,lvl,h,fr,dm,'+'){
	laserTime = 1; // secondi
	lastCharge = 0;
	lastShot = 0;
	awake = false;

	box.a.x -= 1;
	box.b.x += 1;
	box.a.y -= 1;
}

yuck::yuck(int x, int y, level* lvl):
	yuck(x,y,lvl,
		/* HEALTH */ 180+5*lvl->getDiff(),
		/* FIRE_RATE */ 0.004,
		/* DAMAGE */ 2 + 1*lvl->getDiff()){
}

void yuck::update(point target, timeSpan deltaTime){
	if(!awake){
		// non applico danni ma elimino comunque i proiettili che collidono
		lvl->getBM()->check(box);
		entity::update(deltaTime);
	}else{
		entity::update(deltaTime);
		lastCharge += deltaTime;
		if(target.x < box.a.x && facingRight){
			facingRight = false;
		}else if(target.x > box.b.x && !facingRight){
			facingRight = true;
		}

		if(lastCharge < CHARGE_TIME){
			// caricamento
		}else if(lastCharge < CHARGE_TIME+laserTime){
			// laser
			if( lastShot > fireRate ){
				shoot();
				lastShot = 0;
			}else{
				lastShot += deltaTime;
			}
		}else{
			//reset
			lastCharge -= CHARGE_TIME+laserTime;
		}
	}
		
}

void yuck::print(timeSpan deltaTime){
	entity::setPrintColor(PAINT_ENEMY);

	if(!awake){
		mvprintw(box.a.y,   box.a.x, "#####");
		mvprintw(box.a.y+1, box.a.x, "#- -#");
		mvprintw(box.a.y+2, box.a.x, "#-- #");
		mvprintw(box.b.y,   box.a.x, "#####");
	}else if(facingRight){
		mvprintw(box.a.y,   box.a.x, "+-V-+");
		mvprintw(box.a.y+1, box.a.x, "|o o|");
		mvprintw(box.a.y+2, box.a.x, "| <>|");
		mvprintw(box.b.y,   box.a.x, "!___|");
	}else{
		mvprintw(box.a.y,   box.a.x, "+-V-+");
		mvprintw(box.a.y+1, box.a.x, "|o o|");
		mvprintw(box.a.y+2, box.a.x, "|<> |");
		mvprintw(box.b.y,   box.a.x, "|___!");
	}

	attrset(COLOR_PAIR(PAINT_DEFAULT));

	if(lastCharge < CHARGE_TIME && awake){
		point pos;
		pos.y = box.a.y+2;
		if(facingRight) pos.x = box.b.x+1;
		else pos.x = box.a.x-1;

		switch ( (int)(lastCharge*4)%3 ){
		case 0: posPrintW(pos, "-");
			break;
		case 1: posPrintW(pos, "\\");
			break;
		case 2: posPrintW(pos, "/");
			break;
		}
	}
}

void yuck::shoot(){
	vector speed;
	speed.x = 800;
	speed.y = 0;
	if( !facingRight ) speed.x *= -1;

	point muzzle;
	muzzle.y = box.a.y+2;
	if( facingRight ) muzzle.x = box.b.x+1;
	else muzzle.x = box.a.x-1;

	lvl->getBM()->add(muzzle, speed, false, damage, texture);
}

void yuck::wakeUp(){
	awake = true;
}