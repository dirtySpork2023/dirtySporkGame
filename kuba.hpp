#ifndef	KUBA_HPP
#define KUBA_HPP

#include "level.hpp"
#include "bulletManager.hpp"
#include "lib.hpp"
#include "entity.hpp"
#include "player.hpp"

class kuba: public entity {
protected:
	double xSpeed; // tempo in secondi dopo il quale si muove. più piccolo = più veloce
	int damage;
	timeSpan lastMove;
public:
	kuba(int x, int y, level* lM, bulletManager* bM, int h, double moveSpeed, int damage);
	kuba(int x, int y, level* lM, bulletManager* bM);
	void update(player* target, timeSpan deltaTime);
	void print(timeSpan deltaTime);
};

#endif //KUBA_HPP