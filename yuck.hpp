#ifndef YUCK_HPP
#define YUCK_HPP

#include "bulletManager.hpp"

#include "shooter.hpp"

class level;

//TODO?
// invece di sparare dalla bocca genera droni che sparano laser all'altezza del player

class yuck: public shooter{
protected:
	bool awake;
	timeSpan chargeTime; //const?
	timeSpan laserTime;
	timeSpan lastCharge;
public:
	yuck(int x, int y, level* lvl, bulletManager* bM, int h, double fr, int dm);
	yuck(int x, int y, level* lvl, bulletManager* bM);
	void update(point target, timeSpan deltaTime);
	void print(timeSpan deltaTime);
	void shoot();
	void wakeUp();
};

#endif //YUCK_HPP
