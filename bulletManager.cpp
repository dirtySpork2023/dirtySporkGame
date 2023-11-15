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

// applica gravità e aggiorna la posizione di tutti i proiettili
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

// rimuove ricorsivamente tutti i proiettili che colpiscono 'target'
// scrive anche in 'damage' la somma di tutti i danni
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
		posPrintW(p->oldPos, " ");

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

// ritorna true se la posizione è fuori dallo schermo
bool bulletManager::outOfBounds(vector pos){
	return ( pos.x < 0 || COLS < pos.x || pos.y < -20 || LINES-9 < pos.y );
}

// elimina i proiettili che collidono con 'box' e ritorna il danno complessivo
int bulletManager::check(hitBox target){
	int result = 0;
	head = removeNode(target, head, result);
	return result;
}

// stampa tutti i proiettili nella lista
void bulletManager::print(){
	node* tmp = head;
	// cancello solo i proiettili che hanno cambiato posizione
	while( tmp!=NULL ){
		if( !collisionPP(tmp->oldPos, snap(tmp->pos)) ){
			posPrintW(tmp->oldPos, " ");
			tmp->oldPos = snap(tmp->pos);
		}
		tmp = tmp->next;
	}
	tmp = head;
	while( tmp!=NULL ){
		posPrintW(snap(tmp->pos), tmp->texture);
		tmp = tmp->next;
	}
}