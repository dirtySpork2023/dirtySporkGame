#include "player.hpp"

#include <ncurses.h>

#include <cmath>
#include "lib.hpp"
#include "bulletManager.hpp"
using namespace std;

player::player(int x, int y, level* lvl, bulletManager* b, int weapon, float jumpHeight, float armor):
	shooter(x,y,lvl,b,MAX_HEALTH,1,1,'?'){ //fireRate, damage e texture sono temporanei qui

	lastShot = 0;

	setGun(weapon);
	this->gunID = weapon;

	this->jumpSpeed = -sqrt(jumpHeight * ENTITY_G * 2.1);
	this->armor = armor; // 0-1 moltiplica i danni subiti
}

//aggiorna la posizione del player e/o spara
void player::update(char input, timeSpan deltaTime){

	// faccio un bM->check prima per usare l'override della funzione hurt
	// quindi ci sarà un bM->check ridondante all'interno di entity
	hurt(bM->check(box));
	entity::update(deltaTime);

	if( input=='a' || input=='A' || input=='q' ){
		facingRight = false;
		entity::move('a');
	}
	if( input=='d' || input=='D' || input=='e' ){
		facingRight = true;
		entity::move('d');
	}
	if( isGrounded && (upperCase(input) || input=='w' || input=='e' || input=='q')){
		ySpeed = jumpSpeed;
		isGrounded = false;
	}
	if( (input=='f'||input=='F') && lastShot > fireRate ){
		shoot();
		lastShot = 0;
	}else{
		lastShot += deltaTime;
	}
	if( input=='g'){
		gunID = (gunID+1)%3;
		setGun(gunID);
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

void player::shoot(){
	vector speed;
	speed.x = 200;
	speed.y = 0;
	if( !facingRight ) speed.x *= -1;

	point muzzle;
	muzzle.y = box.a.y+1;
	if( facingRight ) muzzle.x = box.b.x+1;
	else muzzle.x = box.a.x-1;

	bM->add(muzzle, speed, false, damage, texture);
}

void player::setGun(int id){
	if( id==PISTOL ){
		// DPS = 30
		fireRate = 0.5;
		damage = 15;
		texture = '-';
	}
	if( id==SHOTGUN ){
		// DPS = 40
		fireRate = 1;
		damage = 40;
		texture = 'E';
	}
	if( id==RIFLE ){
		// DPS = 100
		fireRate = 0.1;
		damage = 10;
		texture = 'o';
	}
}

double player::getArmor(){
	return armor;
}

void player::changeLevel(level* newLvl){
	this->lvl = newLvl;
	this->box.a.x = 0;
	this->box.b.x = 2;
}