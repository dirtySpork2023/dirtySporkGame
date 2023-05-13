#ifndef YUCK_HPP
#define YUCK_HPP

#include "shooter.hpp"

class yuck: public shooter{
protected:
	bool awake;
	timeSpan chargeTime; // si può fare const?
	timeSpan laserTime; // si può fare const?
	timeSpan t; // conta il tempo
	bool shooting;
public:
	yuck(int x, int y, level* lM, bulletManager* bM, int h, double fr, int dm);
	yuck(int x, int y, level* lM, bulletManager* bM);
	void update(point target, timeSpan deltaTime);
	void print(timeSpan deltaTime);
	void shoot();
	void wakeUp();
};

#endif //YUCK_HPP