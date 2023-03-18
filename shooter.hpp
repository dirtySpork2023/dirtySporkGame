#ifndef SHOOTER_HPP
#define SHOOTER_HPP

#include "entity.hpp"
#include "player.hpp"

// detto TBM per gli amici (tennis ball machine)
class shooter: public entity{
protected:
	double fireRate;
	timeSpan lastShot;
	int dmg; // danno di ogni proiettile
public:
	shooter(int x, int y, int h, bulletManager* b, double fireRate, int damage);
	void update(player* target, timeSpan deltaTime);
	void print(timeSpan deltaTime);
	void shoot(point p);
};

#endif //SHOOTER_HPP