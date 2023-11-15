#include "ncurses.h"
#include "yuck.hpp"
#include "level.hpp"
using namespace std;

yuck::yuck(int x, int y, level* lvl, bulletManager* bM, int h, double fr, int dm):
	shooter(x,y,lvl,bM,h,fr,dm,'+'){
	chargeTime = 3; // secondi
	laserTime = 1; // secondi
	lastCharge = 0;

	box.a.x -= 1;
	box.b.x += 1;
	box.a.y -= 1;
}

yuck::yuck(int x, int y, level* lvl, bulletManager* bM):
	yuck(x,y,lvl,bM,
		/* HEALTH */ 200+50*lvl->getDiff(),
		/* FIRE_RATE */ 0.004,
		/* DAMAGE */ 2 + 1*lvl->getDiff()){
}

void yuck::update(point target, timeSpan deltaTime){
	if(!awake){
		bM->check(box);		// non applico danni ma elimino comunque i proiettili che collidono
		entity::update(deltaTime);
	}else{
		entity::update(deltaTime);
		lastCharge += deltaTime;
		if(target.x < box.a.x && facingRight){
			facingRight = false;
			//cleanup
			mvprintw(box.a.y+2, box.b.x+1, " ");
		}else if(target.x > box.b.x && !facingRight){
			facingRight = true;
			mvprintw(box.a.y+2, box.a.x-1, " ");
		}

		if(lastCharge < chargeTime){
			// caricamento
			point pos;
			pos.y = box.a.y+2;
			if(facingRight) pos.x = box.b.x+1;
			else pos.x = box.a.x-1;

			switch ( (int)(lastCharge*6)%3 ){
			case 0:					//^modifica la velocità dell'animazione
				posPrintW(pos, "_");
				break;
			case 1:
				posPrintW(pos, "\\");
				break;
			case 2:
				posPrintW(pos, "/");
				break;
			}
		}else if(lastCharge < chargeTime+laserTime){
			// laser
			if( lastShot > fireRate ){
				shoot();
				lastShot = 0;
			}else{
				lastShot += deltaTime;
			}
		}else{
			//reset
			lastCharge -= chargeTime+laserTime;
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

	attrset(COLOR_PAIR(1));
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

	bM->add(muzzle, speed, false, damage, texture);
}

void yuck::wakeUp(){
	awake = true;
}

yuck::~yuck(){
	entity::~entity();
	mvprintw(box.a.y+2, box.b.x+1, " ");
	mvprintw(box.a.y+2, box.a.x-1, " ");
}

/*
struct node{
	void* obj;
	char type;
	node* next;
}


	node H;

	switch(type){
	case k:
		kuba* K = obj;
		
	case s:
		shooter* S = obj;
		if(S.getHealth==0){
			delete S;
			S = NULL;
		}
	}
	H=H->next;

*/