#include "yuck.hpp"
using namespace std;

yuck::yuck(int x, int y, level* lM, bulletManager* bM, int h, double fr, int dm): shooter(x,y,lM,bM,h,fr,dm){
	this->chargeTime = chargeTime;
	fireRate = 0.1;
	chargeTime = 5; // 5 secondi
	laserTime = 3; // 3 secondi
	t = 0;
	shooting = false;

	box.a.x -= 1;
	box.b.x += 1;
	box.a.y -= 1;
}

yuck::yuck(int x, int y, level* lM, bulletManager* bM): shooter(x,y,lM,bM){
	damage *= 4;
	health *= 4;
	fireRate = 0.1;
	chargeTime = 5; // 5 secondi
	laserTime = 3; // 3 secondi
	t = 0;
	shooting = false;

	box.a.x -= 1;
	box.b.x += 1;
	box.a.y -= 1;
}

void yuck::update(point target, timeSpan deltaTime){
	if(awake){
		shooter::update(target, deltaTime);
		t += deltaTime;

		if(shooting && t>laserTime){
			shooting = false;
			t = 0;
		}else if (!shooting && t>chargeTime){
			shooting = true;
			t = 0;
		}else if (shooting && t<laserTime)
			if( lastShot > fireRate ){
				shoot();
				lastShot = 0;
			}else{
				lastShot += deltaTime;
			}
		}

	}else{
		bM->check(box);					// faccio un bM->check prima senza salvare i danni
		entity::update(deltaTime);		// perchè quando dormiente yuck è immortale come un sasso
	}									// ci sarà un bM->check ridondante all'interno di entity
}

void yuck::print(timeSpan deltaTime){
	entity::setPrintColor(PAINT_ENEMY);

	if(!awake){
		mvprintw(box.a.y,   box.a.x, "#####");
		mvprintw(box.a.y+1, box.a.x, "#- -#");
		mvprintw(box.a.y+2, box.a.x, "#-- #");
		mvprintw(box.b.y,   box.a.x, "#####");
	}else if(facingRight){
		mvprintw(box.a.y,   box.a.x, "+---+");
		mvprintw(box.a.y+1, box.a.x, "|o o|");
		mvprintw(box.a.y+2, box.a.x, "| <>|");
		mvprintw(box.b.y,   box.a.x, "|___|");
	}else{
		mvprintw(box.a.y,   box.a.x, "+---+");
		mvprintw(box.a.y+1, box.a.x, "|o o|");
		mvprintw(box.a.y+2, box.a.x, "|<> |");
		mvprintw(box.b.y,   box.a.x, "|___|");
	}

	attrset(COLOR_PAIR(1));
}

void yuck::shoot(){
	vector speed;
	speed.x = 400;
	speed.y = 0;
	if( !facingRight ) speed.x *= -1;

	point muzzle;
	muzzle.x = box.a.x+2;
	muzzle.y = box.a.y+2;
	if( facingRight ) muzzle.x += 3;
	else muzzle.x -= 3;

	bM->add(muzzle, speed, false, damage, '=');
}

void yuck::wakeUp(){
	awake = true;
}