#ifndef BULLET_HPP
#define BULLET_HPP

#include <ncurses.h>
#include "lib.hpp"

#define BULLET_G 90 // gravità dei proiettili

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
	node* removeNode(hitBox target, node* p, int &damage);
	bool outOfBounds(vector pos);
public:
	bulletManager();
	void add(point p, vector speed, bool gravity, int damage, char texture);
	void update(double deltaTime);
	int check(hitBox box);
	void print();
};

#endif //BULLET_HP