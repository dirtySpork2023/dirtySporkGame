#ifndef SHOOTER_HPP
#define SHOOTER_HPP

#include "entity.hpp"

class shooter: public entity{
protected:
	double fireRate;
	int dmg; // danno di ogni proiettile
public:
	shooter(int x, int y, int h, bulletManager* b, double fireRate, int damage);
	void print();
	void update();
	void shoot();
};

#endif //SHOOTER_HPP