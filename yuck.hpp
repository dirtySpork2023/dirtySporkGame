#ifndef YUCK_HPP
#define YUCK_HPP

#include <ncurses.h>
#include "bulletManager.hpp"
#include "shooter.hpp"
class level;

#define CHARGE_TIME 3

class yuck: public shooter{
protected:
	bool awake;
	timeSpan laserTime;
	timeSpan lastCharge;
public:
	yuck(int x, int y, level* lvl, int h, double fr, int dm);
	yuck(int x, int y, level* lvl);
	void update(point target, timeSpan deltaTime);
	void print(timeSpan deltaTime);
	void shoot();
	void wakeUp();
};

#endif //YUCK_HPP
