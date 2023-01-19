#ifndef BULLET_HPP
#define BULLET_HPP

#include "lib.hpp"

struct node {
	vector pos;
	double speed;
	int damage;
	node* next;
};

class bullet {
protected:
	node* head; //lista di proiettili
	node* tail; //proiettile più recente
	int num; //numero di proiettili
	void remove();

public:
	char texture;
	bullet();
	void add(point p, double speed, int damage);
	void update(long int deltaTime);
	int check(hitBox box);
	void print();
};

#endif //BULLET_HPP