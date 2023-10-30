#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "lib.hpp"

/*	types to do

	set armor
	add health
	change weapon
	add money

*/

class powerup{
protected:
	hitBox box;
public:
	powerup(int x, int y);
	void on();
	void print();
	~powerup();
};

#endif //POWERUP_HPP
