#ifndef SHOOTER_HPP
#define SHOOTER_HPP

#include <ncurses.h>
#include "lib.hpp"
#include "bulletManager.hpp"
#include "entity.hpp"

class level;

class shooter: public entity{
protected:
	bool facingRight;
	double fireRate;
	int damage; // danno di ogni proiettile
	char texture;
	timeSpan lastShot;

public:
	shooter(int x, int y, level* lvl, int h, double fireRate, int damage, char bullet);
	shooter(int x, int y, level* lvl);
	void update(point target, timeSpan deltaTime);
	void print(timeSpan deltaTime);
	void shoot(point p);
};

#endif //SHOOTER_HPP
