#include "kuba.hpp"
#include "level.hpp"

// costruttore
kuba::kuba(int x, int y, level* lvl, int h, int damage):
	entity(x,y,lvl,h){
	this->movingRight = false;
	this->lastMove = 0;
	this->damage = damage;

	//hitbox 3x2
	this->box.a.y = y-1;
}

// costruttore secondario
kuba::kuba(int x, int y, level* lvl):
	kuba(x, y, lvl,
		/* HEALTH */ 30+10*lvl->getDiff(),
		/* DAMAGE */ 15+5*lvl->getDiff()){
}

// direzione in cui si muove kuba in formato WASD
char kuba::direction(){
	if( movingRight )
		return 'd';
	else
		return 'a';
}

// muove kuba in base a movingRight
void kuba::move(){
	// se sbatte contro un alleato o arriva alla fine della piattaforma si gira
	hitBox step = box;
	if(movingRight)
		step.b.x = box.b.x+1;
	else
		step.b.x = box.a.x-1;
	step.a = step.b;
	infoCrash i = lvl->check(box, direction());
	if(i.type=='k' || i.type=='s' || i.type=='y' || lvl->check(step, 's').type==' ')
		movingRight = !movingRight;

	entity::move(direction());
}

void kuba::update(player* target, timeSpan deltaTime){
	entity::update(deltaTime);
	lastMove += deltaTime;

	if( lastMove>=SPEED ){

		if(isTouching(box, target->getHitBox(), 'w')){
			target->hurt(damage);
			move();
			lastMove = -SPEED*3;
		}else if(isTouching(box, target->getHitBox(), direction())){
			target->hurt(damage);
			// fa un passo indietro
			movingRight = !movingRight;
			move();
			lastMove = -SPEED*7;
			movingRight = !movingRight;
		}else{
			move();
			lastMove = 0;
		}
	}
}

// stampa
void kuba::print(timeSpan deltaTime){
	entity::setPrintColor(PAINT_ENEMY);

	mvprintw(box.a.y, box.a.x, "<A>");
	mvprintw(box.b.y, box.a.x, "/\"\\");

	attrset(COLOR_PAIR(1));
}
