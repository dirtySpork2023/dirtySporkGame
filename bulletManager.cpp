#include <ncurses.h>
#include "lib.hpp"
#include "bulletManager.hpp"
using namespace std;

#define MAX_BULLETS 50

bulletManager::bulletManager(){
	this->head = NULL;
	this->tail = NULL;
	this->num = 0;
}

// aggiunge un elemento in coda
void bulletManager::add(point p, vector speed, bool gravity, int damage, char texture){
	node* tmp = new node;
	tmp->next = NULL;
	if( this->tail!=NULL )
		this->tail->next = tmp;
	this->tail = tmp;
	if( this->head==NULL )
		this->head = tmp;

	vector v;
 	v.x = (double)p.x;
 	v.y = (double)p.y;
 	tmp->pos = v;
	tmp->speed.x = speed.x;
	tmp->speed.y = speed.y/1.5;
	tmp->gravity = gravity;
	tmp->damage = damage;
	tmp->texture = texture;
	this->num++;

	if( this->num > MAX_BULLETS ){ //TODO verificare se i proiettili sono fuori dallo schermo
		this->removeOldest();
	}
}

// rimuove l'elemento in testa
void bulletManager::removeOldest(){
	if(head!=NULL && head->next!=NULL){
		node* tmp = this->head->next;
		delete this->head;
		this->head = tmp;
		this->num--;
	}
}

void bulletManager::update(double deltaTime){
	node* tmp = this->head;
	while( tmp!=NULL ) {
		if( tmp->gravity ){
			tmp->speed.y += 9.81 * deltaTime * 10; //gravity
		}
		tmp->pos.x += tmp->speed.x * deltaTime;
		tmp->pos.y += tmp->speed.y * deltaTime;
		tmp = tmp->next;
	}
}

// rimuove ricorsivamente tutti i nodi in cui avviene una collisione, sommando i danni dei proiettili nella variabile damage.
node* bulletManager::removeNode(hitBox target, node* p, int &damage ){
	if( p==NULL ) return NULL;
	else if( collisionHV(target, p->pos) ){
		damage += p->damage;

		// cleanup
		mvprintw((int)p->pos.y, (int)p->pos.x, " ");

		this->num--;
		if( p==this->head ){
			this->head = this->head->next;
			if( this->head==NULL )
				this->tail = NULL;
		}

		node* tmp = p->next;
		delete p;
		return this->removeNode(target, tmp, damage);
	}else{
		p->next = this->removeNode(target, p->next, damage);
		if( p->next==NULL && p->next!=this->tail ) this->tail = p;
		return p;
	}
}

// ritorna 0 se non ci sono collisioni, altrimenti ritorna il danno del proiettile (ed elimina il proiettile dalla lista)
int bulletManager::check(hitBox target){
	int result = 0;
	this->head = this->removeNode(target, this->head, result);
	return result;
}

void bulletManager::print(){
	node* tmp = this->head;
	while( tmp!=NULL ){
		mvprintw((int)tmp->pos.y, (int)tmp->pos.x, "%c", tmp->texture );
		// cleanup
		if( tmp->speed.x>0 ){
			mvprintw((int)tmp->pos.y, (int)tmp->pos.x-1, " ");
		}else{
			mvprintw((int)tmp->pos.y, (int)tmp->pos.x+1, " ");
		}
		if( tmp->speed.y>0 ){
			mvprintw((int)tmp->pos.y-1, (int)tmp->pos.x, " ");
		}else{
			mvprintw((int)tmp->pos.y+1, (int)tmp->pos.x, " ");
		}
		tmp = tmp->next;
	}


	//mvprintw(1,0,"num: %d\t", num);
	//mvprintw(2,0,"head: %d\t\t\t", this->head);
	//mvprintw(3,0,"tail: %d\t\t\t", this->tail);
}