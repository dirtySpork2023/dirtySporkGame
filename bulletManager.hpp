#ifndef BULLET_HPP
#define BULLET_HPP

#include "lib.hpp"

#define BULLET_G 100 // gravità dei proiettili

struct node {
	vector pos; // posizione
	vector speed; // velocità
	bool gravity; // true se il proiettile risente di gravità
	int damage; // danno del proiettile
	char texture; // grafica
	point oldPos; // vecchia posizione
	node* next;
};

class bulletManager {
private:
	node* head; // lista in cui ogni nodo è un proiettile
	node* tail; //proiettile più recente
	int num; //numero di proiettili in lista
	void removeOldest(); // rimozione in testa alla lista
	node* removeNode(hitBox target, node* p, int &damage); // rimuove ricorsivamente tutti i proiettili che colpiscono 'target'
														   // scrive anche in 'damage' la somma di tutti i danni
public:
	bulletManager();
	void add(point p, vector speed, bool gravity, int damage, char texture); // aggiunta in coda alla lista
	void update(double deltaTime);
	int check(hitBox box); // elimina i proiettili che collidono con 'box' e ritorna il danno complessivo
	void print(); // stampa tutti i proiettili nella lista
	int getNum();
};

#endif //BULLET_HP