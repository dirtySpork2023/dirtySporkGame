#ifndef	KUBA_HPP
#define KUBA_HPP

#include <ncurses.h>
#include "lib.hpp"
#include "bulletManager.hpp"
#include "entity.hpp"
#include "player.hpp"

#define SPEED 0.05 // tempo in secondi dopo il quale si muove. più piccolo == più veloce

class level;

class kuba: public entity {
protected:
	bool movingRight;
	int damage;
	timeSpan lastMove; // tempo in secondi passato dall'ultimo movimento
	char direction();
	void move();
public:
	kuba(int x, int y, level* lvl, int h, int damage);
	kuba(int x, int y, level* lvl);
	void update(player* target, timeSpan deltaTime);
	void print(timeSpan deltaTime);
};

#endif //KUBA_HPP