#include "yuck.hpp"
using namespace std;

yuck::yuck(int x, int y, level* lM, bulletManager* bM, int h, double fr, int dm): shooter(x,y,lM,bM,h,fr,dm){
	box.a.x -= 1;
	box.b.x += 1;
	box.a.y -= 1;
}

yuck::yuck(int x, int y, level* lM, bulletManager* bM): shooter(x,y,lM,bM){
	damage *= 4;
	health *= 4;
	fireRate *= 0.8;

	box.a.x -= 1;
	box.b.x += 1;
	box.a.y -= 1;
}

void yuck::update(point target, timeSpan deltaTime){
	if(awake){
		shooter::update(target, deltaTime);
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

void yuck::shoot(point p){
	//se il laser è carico, inizia a sparare.
	//il laser dura tot poi si ferma e riinizia a caricarsi
	//implementato come tantissimi proiettili
}