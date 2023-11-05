#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "lib.hpp"

class coin{
protected:
	hitBox box;
	int value; // valore della moneta
	timeSpan t; // tempo dell'animazione
public:
	coin(int x, int y, int value);
	int check(hitBox p);
	void print(timeSpan deltaTime);
	~coin();
};

#endif //POWERUP_HPP
