#include "player.hpp"
#include "level.hpp"

player::player(int x, int y, level* lvl, int weapon, float jumpHeight, float armor):
	shooter(x,y,lvl,MAX_HEALTH,1,1,'1'){ //fireRate, damage e texture sono temporanei qui

	lastShot = 0;

	setGun(weapon);
	this->gunID = weapon;

	this->jumpSpeed = -sqrt(jumpHeight * ENTITY_G * 2.1);
	this->armor = armor; // 0-1
}

//aggiorna la posizione del player e/o spara
void player::update(char input, timeSpan deltaTime){

	hurt(lvl->getBM()->check(box));
	entity::update(deltaTime);

	if( input=='a' || input=='A' || input=='q' ){
		facingRight = false;
		entity::move('a');
	}
	if( input=='d' || input=='D' || input=='e' ){
		facingRight = true;
		entity::move('d');
	}
	if( isGrounded() && (input=='F' || input=='w' || input=='e' || input=='q')){
		ySpeed = jumpSpeed;
	}

	lastShot += deltaTime;
	if( (input=='f'||input=='F') && lastShot > fireRate ){
		shoot();
		lastShot = 0;
	}
}

//stampa il player
void player::print(timeSpan deltaTime){
	entity::setPrintColor(PAINT_PLAYER);
	if( facingRight ){
		mvprintw(box.a.y,   box.a.x, " p ");
		mvprintw(box.a.y+1, box.a.x, ">W=");
		mvprintw(box.b.y,   box.a.x, "/\"\\");
	}else{
		mvprintw(box.a.y,   box.a.x, " q ");
		mvprintw(box.a.y+1, box.a.x, "=W<");
		mvprintw(box.b.y,   box.a.x, "/\"\\");
	}
	attrset(COLOR_PAIR(PAINT_DEFAULT));
}

bool player::hurt(int value){
	return entity::hurt(value * (1-armor));
}

void player::heal(int value){
	health += value;
	if( health>MAX_HEALTH )
		health = MAX_HEALTH;
}

void player::shoot(){
	vector speed;
	speed.x = 200;
	speed.y = 0;
	if( !facingRight ) speed.x *= -1;

	point muzzle;
	muzzle.y = box.a.y+1;
	if( facingRight ) muzzle.x = box.b.x+1;
	else muzzle.x = box.a.x-1;

	lvl->getBM()->add(muzzle, speed, false, damage, texture);
}

void player::setGun(int id){
	if( id==PISTOL ){
		// DPS = 30
		fireRate = 0.5;
		damage = 15;
		texture = '-';
	}
	if( id==SHOTGUN ){
		// DPS = 80
		fireRate = 1;
		damage = 80;
		texture = 'E';
	}
	if( id==RIFLE ){
		// DPS = 160
		fireRate = 0.1;
		damage = 16;
		texture = 'o';
	}
}

int player::getGun(){
	return gunID;
}

void player::setArmor(int percentage){
	armor = (double)percentage/100;
}

double player::getArmor(){
	return armor;
}

void player::changeLevel(level* newLvl){
	if( newLvl->number() > lvl->number() ){
		box.a.x = 0;
		box.b.x = 2;
	}else{
		box.a.x = COLS-3;
		box.b.x = COLS-1;
	}
	box.a.y = LINES-WIN_HEIGHT-4;
	box.b.y = LINES-WIN_HEIGHT-2;
	this->lvl = newLvl;
}

void player::reset(level* newLvl){
	box.a.x = 2;
	box.b.x = 4;
	box.a.y = -2;
	box.b.y = 0;
	this->lvl = newLvl;
	health = 100;
}