#ifndef YUCK_HPP
#define YUCK_HPP

#include "shooter.hpp"

class yuck: public shooter{
protected:
	bool awake;
public:
	yuck(int x, int y, level* lM, bulletManager* bM, int h, double fr, int dm);
	yuck(int x, int y, level* lM, bulletManager* bM);
	void update(point target, timeSpan deltaTime)
	void print(timeSpan deltaTime);
	void shoot(point p);
};

#endif //YUCK_HPP