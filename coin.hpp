#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "lib.hpp"

class coin{
protected:
	hitBox box;
	int value; // value of the coin
	timeSpan t; // animation time
public:
	coin(int x, int y, int value);
	int check(hitBox p);
	void print(timeSpan deltaTime);
	~coin();
};

#endif //POWERUP_HPP
