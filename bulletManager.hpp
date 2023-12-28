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
	node* next;
};

class bulletManager {
private:
	node* head; // lista in cui ogni nodo è un proiettile
	int num; //numero di proiettili in lista
	node* removeNode(hitBox target, node* p, int &damage);
	bool outOfBounds(vector pos);
public:
	bulletManager();
	void add(point p, vector speed, bool gravity, int damage, char texture);
	void update(double deltaTime);
	int check(hitBox box);
	void clear();
	void print();
};

#endif //BULLET_HP