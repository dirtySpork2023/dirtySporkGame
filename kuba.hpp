#ifndef	KUBA_HPP
#define KUBA_HPP

#include "lib.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "bulletManager.hpp"

class kuba: public entity {
protected:
	double xSpeed; // tempo in secondi dopo il quale si muove. più piccolo = più veloce
	int damage;
	timeSpan lastMove;
public:
	kuba(int x, int y, bulletManager* b, int h, double moveSpeed, int damage);
	kuba(int x, int y, bulletManager* b, int level);
	void update(player* target, timeSpan deltaTime);
	void print(timeSpan deltaTime);
};

#endif //KUBA_HPP