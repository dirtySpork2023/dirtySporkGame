#ifndef BULLET_HPP
#define BULLET_HPP

#include <ncurses.h>
#include "lib.hpp"

#define BULLET_G 90 // gravità dei proiettili

struct bullet {
	vector pos; // posizione
	vector speed; // velocità
	bool gravity; // true se il proiettile risente di gravità
	int damage; // danno del proiettile<<
	char texture; // grafica
	bullet* next;
};

class bulletManager {
private:
	bullet* head; // lista in cui ogni nodo è un proiettile
	bullet* removeBullet(hitBox target, bullet* p, int &damage);
	bool outOfBounds(vector pos);
public:
	bulletManager();
	void add(point p, vector speed, bool gravity, int damage, char texture);
	void update(double deltaTime);
	int check(hitBox box);
	void print();
};

#endif //BULLET_HP