#ifndef	KUBA_HPP
#define KUBA_HPP

#include "lib.hpp"
#include "bulletManager.hpp"

#include "entity.hpp"
#include "player.hpp"

class level;

class kuba: public entity {
protected:
	double xSpeed; // tempo in secondi dopo il quale si muove. più piccolo = più veloce
	bool movingRight;
	int damage;
	timeSpan lastMove;
public:
	kuba(int x, int y, level* lvl, int h, double moveSpeed, int damage);
	kuba(int x, int y, level* lvl);
	void update(player* target, timeSpan deltaTime);
	void print(timeSpan deltaTime);
};

#endif //KUBA_HPP
