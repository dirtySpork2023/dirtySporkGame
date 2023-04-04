#include <ncurses.h>

#include "lib.hpp"
#include "bulletManager.hpp"
using namespace std;

bulletManager::bulletManager(){
	head = NULL;
	tail = NULL;
	num = 0;
}

// aggiunge un elemento in coda
void bulletManager::add(point p, vector speed, bool gravity, int damage, char texture){
	node* tmp = new node;
	tmp->next = NULL;
	if( tail!=NULL )
		tail->next = tmp;
	tail = tmp;
	if( head==NULL )
		head = tmp;

	vector v;
 	v.x = (double)p.x;
 	v.y = (double)p.y;
 	tmp->pos = v;
	tmp->oldPos = p;
	tmp->speed.x = speed.x;
	tmp->speed.y = speed.y/1.5;
	tmp->gravity = gravity;
	tmp->damage = damage;
	tmp->texture = texture;
	num++;

	if( num > MAX_BULLETS ){ //TODO verificare se i proiettili sono fuori dallo schermo
		removeOldest();
	}
}

// rimuove l'elemento in testa
void bulletManager::removeOldest(){
	if(head!=NULL && head->next!=NULL){
		node* tmp = head->next;
		delete head;
		head = tmp;
		num--;
	}
}

void bulletManager::update(double deltaTime){
	node* tmp = head;
	while( tmp!=NULL ) {
		if( tmp->gravity ){
			tmp->speed.y += BULLET_G * deltaTime;
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

		num--;
		if( p==head ){
			head = head->next;
			if( head==NULL )
				tail = NULL;
		}

		node* tmp = p->next;
		delete p;
		return removeNode(target, tmp, damage);
	}else{
		p->next = removeNode(target, p->next, damage);
		if( p->next==NULL && p->next!=tail )
			tail = p;
		return p;
	}
}

// ritorna 0 se non ci sono collisioni, altrimenti ritorna il danno del proiettile (ed elimina il proiettile dalla lista)
int bulletManager::check(hitBox target){
	int result = 0;
	head = removeNode(target, head, result);
	return result;
}

void bulletManager::print(){
	node* tmp = head;
	while( tmp!=NULL ){
		mvprintw((int)tmp->pos.y, (int)tmp->pos.x, "%c", tmp->texture );
		// cleanup
		if(tmp->oldPos.x != (int)tmp->pos.x || tmp->oldPos.y != (int)tmp->pos.y){
			mvprintw(tmp->oldPos.y, tmp->oldPos.x, " ");
			tmp->oldPos.x = (int)tmp->pos.x;
			tmp->oldPos.y = (int)tmp->pos.y;
		}
		tmp = tmp->next;
	}
}