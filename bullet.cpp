#include <ncurses.h>

#include "bullet.hpp"

#define MAX_BULLETS 50 //temporaneo


bullet::bullet(){
	this->head = NULL ;
	this->tail = NULL ;
	num = 0 ;
	texture = '#' ;
}

void bullet::add(int x, int y, double speed ){
	//postCondition: aggiunge un elemento in coda
	node* tmp = new node ;
	tmp->next = NULL ;
	if( this->tail!=NULL )this->tail->next = tmp ;
	this->tail = tmp ;
	if( this->head==NULL ) this->head = tmp ;
	tmp->x = (double)x ;
	tmp->y = (double)y ;
	tmp->speed = speed ;
	this->num++ ;

	if( this->num > MAX_BULLETS ){ //TODO verificare se i proiettili sono fuori dallo schermo
		remove();
	}
}

void bullet::remove(){
	//preCondition: tmp!=NULL
	//postCondition: rimuove l'elemento in testa
	node* tmp = this->head->next ;
	delete this->head ;
	this->head = tmp ;
	this->num-- ;
}

void bullet::update(long int deltaTime){
	node* tmp = this->head ;
	while( tmp!=NULL ) {
		tmp->x += tmp->speed / deltaTime ;
		// TODO controlla collisioni con nemici
		tmp = tmp->next ;
	}
}

void bullet::print(){
	node* tmp = this->head ;
	mvprintw(1,1, "bullets: %d", num) ;
	while( tmp!=NULL ){
		if( tmp->speed>0 ){
			mvprintw((int)tmp->y, (int)tmp->x-1, " %c", this->texture ) ;
		}else{
			mvprintw((int)tmp->y, (int)tmp->x, "%c ", this->texture ) ;
		}
		tmp = tmp->next ;
	}
}
