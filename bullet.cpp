#include <ncurses.h>

#include "bullet.hpp"


bullet::bullet(){
	this->head = NULL ;
}

void bullet::add(double x, double y, double speed ){
}

void bullet::remove(){
}


void bullet::update(long int deltaTime){
	list* tmp = this->head ;
	while( tmp!=NULL ) {
		tmp->x += tmp->speed / deltaTime ;
		tmp = tmp->next ;
	}
}