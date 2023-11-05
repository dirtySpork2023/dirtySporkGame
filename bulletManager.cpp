#include <ncurses.h>

#include "lib.hpp"
#include "bulletManager.hpp"
using namespace std;

bulletManager::bulletManager(){
	head = NULL;
	num = 0;
}

// aggiunta in testa alla lista
void bulletManager::add(point p, vector speed, bool gravity, int damage, char texture){
	node* tmp = new node;
	tmp->next = head;
	head = tmp;

	vector v;
 	v.x = (double)p.x;
 	v.y = (double)p.y;
 	tmp->pos = v;
	tmp->oldPos = p;
	tmp->speed.x = speed.x;
	tmp->speed.y = speed.y;
	tmp->gravity = gravity;
	tmp->damage = damage;
	tmp->texture = texture;
	num++;
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
	
	bool doRemove = false; 
	if( collisionHV(target, p->pos) ){
		doRemove = true;
		damage += p->damage;
	}
	if( outOfBounds(p->pos) ){
		doRemove = true;
	}

	if( doRemove ){
		num--;
		// cleanup
		posPrintW(snap(p->pos), " ");

		// se la testa della lista in esame è anche la testa della lista totale, devo aggiornarla
		if( p==head ){
			head = head->next;
		}

		// elimino la testa e proseguo perchè potrebbero esserci altri proiettili che collidono
		node* tmp = p->next;
		delete p;
		return removeNode(target, tmp, damage);
	}else{
		p->next = removeNode(target, p->next, damage);
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
		//stampo anche se la posizione non è cambiata
		posPrintW(snap(tmp->pos), tmp->texture);

		if( !collisionPP(tmp->oldPos, snap(tmp->pos)) ){
			// cleanup
			posPrintW(tmp->oldPos, " ");
			tmp->oldPos = snap(tmp->pos);
		}

		tmp = tmp->next;
	}
}

int bulletManager::getNum(){
	return num;
}