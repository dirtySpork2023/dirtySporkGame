#include "entity.hpp"
#include "level.hpp"

// costruttore
entity::entity(int x, int y, level* lvl, int hp){
	this->yMod = 0;
	this->ySpeed = 0;

	this->health = hp;
	this->lastDamage = DAMAGE_TIMESPAN+1;

	this->lvl = lvl;

	//default hitbox. da sovrascrivere se necessario
	this->box.a.x = x-1;
	this->box.a.y = y-2;
	this->box.b.x = x+1;
	this->box.b.y = y;
}

bool entity::isGrounded(){
	return (lvl->check(box, 's').type!=' ' && ySpeed>=0);
}

// muove entity in base alla forza di gravità e il tempo passato
void entity::applyGravity(timeSpan deltaTime){
	if( isGrounded() ){
		ySpeed = 0;
		yMod = 0;
	}else{
		ySpeed += ENTITY_G * deltaTime;
		yMod += ySpeed * deltaTime;
		if(yMod > 1){
			yMod -= 1;
			move('s');
		}else if(yMod < -1){
			yMod += 1;
			move('w');
		}
	}
}

// muove entity di una posizione verso una direzione WASD
void entity::move(char input){
	infoCrash i = lvl->check(box, input);
	if( input=='a' && i.type==' ' ){
		box.a.x -= 1;
		box.b.x -= 1;
	}else if( input=='d' && i.type==' ' ){
		box.a.x += 1;
		box.b.x += 1;
	}else if( input=='s' && i.type==' ' ){
		box.a.y += 1;
		box.b.y += 1;
	}else if( input=='w'){
		if( i.type==' ' || i.type=='#' && box.a.x>1 && box.b.x<COLS-2 ){
			box.a.y -= 1;
			box.b.y -= 1;
		}else{
			ySpeed=0;
		}
	}
}

// applica il colore con cui stampare
void entity::setPrintColor(int paint){
	if(lastDamage <= DAMAGE_TIMESPAN){
		attrset(COLOR_PAIR( PAINT_DAMAGE ));
	}else{
		attrset(COLOR_PAIR( paint ));
		attron(A_BOLD);
	}
}

void entity::update(timeSpan deltaTime){
	lastDamage += deltaTime;
	hurt(lvl->getBM()->check(box));
	applyGravity(deltaTime);
}

// ritorna la posizione più centrale alla base dell'entity
point entity::getPos(){
	point pos = box.b;
	pos.x = (box.a.x + box.b.x )/2;
	return pos;
}

// ritorna la hitBox
hitBox entity::getHitBox(){
	return this->box;
}

// ritorna i punti vita
int entity::getHealth(){
	return this->health;
}

// danneggia entity e ritorna 'se è morto'
bool entity::hurt(int value){
	if( value>0 ) lastDamage = 0;
	health -= value;

	if(health <= 0){
		health = 0;
		return true;
	}else{
		return false;
	}
}

entity::~entity(){
	// genera un esplosione
	for(int i=0; i<10; i++){
		lvl->getBM()->add(this->getPos(), randVector(), true, 0, ':');
	}
}