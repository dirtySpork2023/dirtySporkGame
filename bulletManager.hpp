#ifndef BULLET_HPP
#define BULLET_HPP

#include "lib.hpp"

#define MAX_BULLETS 100
#define BULLET_G 100

struct node {
	vector pos;
	vector speed;
	bool gravity;
	int damage;
	char texture;
	point oldPos;
	node* next;
};

class bulletManager {
private:
	node* head; //lista di proiettili
	node* tail; //proiettile più recente
	int num; //numero di proiettili in lista
	void removeOldest();
	node* removeNode(hitBox target, node* p, int &damage);

public:
	bulletManager();
	void add(point p, vector speed, bool gravity, int damage, char texture);
	void update(double deltaTime);
	int check(hitBox box);
	void print();
};

#endif //BULLET_HP