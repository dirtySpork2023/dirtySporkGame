#include <ncurses.h>

#include "lib.hpp"
#include "bulletManager.hpp"
using namespace std;

bulletManager::bulletManager(){
	// la lista inizialmente è vuota
	head = NULL;
	tail = NULL;
	num = 0;
}

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

	if( num > MAX_BULLETS ){ // se la lista è troppo lunga
		removeOldest();		 // rimuovo il proiettile più vecchio
	}
}

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

node* bulletManager::removeNode(hitBox target, node* p, int &damage ){
	if( p==NULL ) return NULL;
	else if( collisionHV(target, p->pos) ){ // se il proiettile in testa colpisce target
		damage += p->damage;

		// cleanup
		mvprintw((int)p->pos.y, (int)p->pos.x, " "); // TODO questo serve a qualcosa?

		num--; // TODO move down

		// se la testa della lista in esame è anche la testa della lista totale, devo aggiornarla
		if( p==head ){
			head = head->next;
			if( head==NULL ) // TODO questo non serve
				tail = NULL; // TODO questo non serve
		}

		// elimino la testa e proseguo perchè potrebbero esserci altri proiettili che collidono
		node* tmp = p->next;
		delete p;
		return removeNode(target, tmp, damage);
	}else{
		p->next = removeNode(target, p->next, damage);
		if( p->next==NULL && p->next!=tail ) // TODO la seconda parte del AND si può togliere
			tail = p;
		return p;
	}
}

int bulletManager::check(hitBox target){
	int result = 0; // variabile in cui tenere conto dei danni
	head = removeNode(target, head, result);
	return result;
}

void bulletManager::print(){
	node* tmp = head;
	while( tmp!=NULL ){
		if( collisionPP(tmp->oldPos, snap(tmp->pos)) ){
			// la posizione non è cambiata
			mvprintw((int)tmp->pos.y, (int)tmp->pos.x, "%c", tmp->texture ); // TODO serve ristampare? non credo
		}else{
			// posPrintW(tmp->oldPos, " "); // TODO funziona??
			mvprintw(tmp->oldPos.y, tmp->oldPos.x, " ");
			tmp->oldPos = snap(tmp->pos);
		}


		// cleanup

		tmp = tmp->next;
	}
}

/*
OLD
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
 */
