#ifndef BULLET_CPP
#define BULLET_CPP

#include <ncurses.h>
#include "lib.hpp"
#include "lib.cpp" //senza di questo non compila per qualche motivo
#include "bullet.hpp"
using namespace std;

#define MAX_BULLETS 50

bulletManager::bulletManager(){
	this->head = NULL;
	this->tail = NULL;
	this->num = 0;
}

void bulletManager::add(point p, double speed, int damage, char texture){
	//postCondition: aggiunge un elemento in coda
	node* tmp = new node;
	tmp->next = NULL;
	if( this->tail!=NULL )this->tail->next = tmp;
	this->tail = tmp;
	if( this->head==NULL ) this->head = tmp;
	vector v;
 	v.x = (double)p.x;
 	v.y = (double)p.y;
 	tmp->pos = v;
	tmp->speed = speed;
	tmp->damage = damage;
	tmp->texture = texture;
	this->num++;

	if( this->num > MAX_BULLETS ){ //TODO verificare se i proiettili sono fuori dallo schermo
		remove();
	}
}

void bulletManager::remove(){
	//preCondition: num > 2  <=>  head!=NULL && head->next!=NULL
	//postCondition: rimuove l'elemento in testa
	node* tmp = this->head->next;
	delete this->head;
	this->head = tmp;
	this->num--;
}

void bulletManager::update(long int deltaTime){
	node* tmp = this->head;
	while( tmp!=NULL ) {
		tmp->pos.x += tmp->speed / deltaTime;
		// TODO controlla collisioni con nemici
		tmp = tmp->next;
	}
}

int bulletManager::check(hitBox box){
	//postCondition: ritorna -1 se non ci sono collisioni, altrimenti ritorna il danno del proiettile
	node* tmp = this->head;
	int result = -1;
	while( tmp!=NULL ){
		if( collisionHV(box, tmp->pos) ){
			result = tmp->damage;
			//TODO REMOVE BULLET BECAUSE IT HIT SMTH
		}
		tmp = tmp->next;
	}
	return result;
}

void bulletManager::print(){
	node* tmp = this->head;
	while( tmp!=NULL ){
		mvprintw((int)tmp->pos.y, (int)tmp->pos.x, "%c", tmp->texture );
		// cleanup
		if( tmp->speed>0 ){
			mvprintw((int)tmp->pos.y, (int)tmp->pos.x-1, " ");
		}else{
			mvprintw((int)tmp->pos.y, (int)tmp->pos.x+1, " ");
		}
		tmp = tmp->next;
	}
}

#endif //BULLET_CPP