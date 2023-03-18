#ifndef SHOOTER_HPP
#define SHOOTER_HPP

#include "entity.hpp"
#include "player.hpp"

class shooter: public entity{
protected:
	double fireRate;
	int dmg; // danno di ogni proiettile
public:
	shooter(int x, int y, int h, bulletManager* b, double fireRate, int damage);
	void update(player* target, timeSpan deltaTime);
	void print(timeSpan deltaTime);
	void shoot();
};

#endif //SHOOTER_HPP