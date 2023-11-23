#include <ncurses.h>
#include "lib.hpp"
#include "kuba.hpp"
#include "bulletManager.hpp"
#include "level.hpp"
using namespace std;

kuba::kuba(int x, int y, level* lvl, bulletManager* bM, int h, double moveSpeed, int damage):
	entity(x,y,lvl,bM,h){
	this->xSpeed = moveSpeed;
	this->movingRight = false;
	this->lastMove = 0;

	this->damage = damage;

	//hitbox 3x2
	this->box.a.y = y-1;
}

kuba::kuba(int x, int y, level* lvl, bulletManager* bM):
	kuba(x, y, lvl, bM,
		/* HEALTH */ 30+10*lvl->getDiff(),
		/* SPEED */ 0.07,
		/* DAMAGE */ 15+5*lvl->getDiff()){
}

void kuba::update(player* target, timeSpan deltaTime){
	entity::update(deltaTime);

	
	if( lastMove>=xSpeed ){
		//controllo se è possibile muoversi ancora a destra
		hitBox step = this->box;
		if(movingRight){
			step.b.x++;
			step.a = step.b;
		}else{
			step.b.x-=3;
			step.a = step.b;
		}
		infoCrash i = lvl->check(step, 's');
		if(i.type==' ' && movingRight) movingRight = false;
		else if(i.type==' ' && !movingRight) movingRight = true;

		if(movingRight) i = lvl->check(box, 'd');
		else i = lvl->check(box, 'a');

		if(isTouching(box, target->getHitBox(), 'w')){
			target->hurt(damage);
			if(movingRight) entity::move('d');
			else entity::move('a');
			lastMove = -xSpeed*3;
		}else if(isTouching(box, target->getHitBox(), 'a') && !movingRight){
			target->hurt(damage);
			entity::move('d');
			lastMove = -xSpeed*2;
		}else if(isTouching(box, target->getHitBox(), 'd') && movingRight){
			target->hurt(damage);
			entity::move('a');
			lastMove = -xSpeed*2;
		}else if(i.type=='k' || i.type=='s' || i.type=='y'){
			movingRight = !movingRight;
		}else if(movingRight){
			entity::move('d');
			lastMove = 0;
		}else{
			entity::move('a');
			lastMove = 0;
		}
	}

	lastMove += deltaTime;
}

void kuba::print(timeSpan deltaTime){
	entity::setPrintColor(PAINT_ENEMY);

	mvprintw(box.a.y, box.a.x, "<A>");
	mvprintw(box.b.y, box.a.x, "/\"\\");

	attrset(COLOR_PAIR(1));
}
