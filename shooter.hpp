#ifndef SHOOTER_HPP
#define SHOOTER_HPP

#include "entity.hpp"

// detto TBM per gli amici (tennis ball machine)
class shooter: public entity{
protected:
	double fireRate;
	timeSpan lastShot;
	int dmg; // danno di ogni proiettile
	bool facingRight;

public:
	shooter(int x, int y, bulletManager* b, int h, double fireRate, int damage);
	void update(point target, timeSpan deltaTime);
	void print(timeSpan deltaTime);
	void shoot(point p);
};

#endif //SHOOTER_HPP