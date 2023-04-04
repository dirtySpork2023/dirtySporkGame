#ifndef SHOOTER_HPP
#define SHOOTER_HPP

#include "level.hpp"
#include "bulletManager.hpp"
#include "entity.hpp"

// detto TBM per gli amici (tennis ball machine)
class shooter: public entity{
protected:
	double fireRate;
	timeSpan lastShot;
	int damage; // danno di ogni proiettile
	bool facingRight;

public:
	shooter(int x, int y, level* lM, bulletManager* bM, int h, double fireRate, int damage);
	shooter(int x, int y, level* lM, bulletManager* bM);
	void update(point target, timeSpan deltaTime);
	void print(timeSpan deltaTime);
	void shoot(point p);
};

#endif //SHOOTER_HPP